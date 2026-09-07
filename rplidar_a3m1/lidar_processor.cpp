#include <memory>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"

struct Point2D
{
    float x;
    float y;
    bool valid;
};

struct CurvaturePoint
{
    float value;
    size_t index;
};

bool valid_window(const std::vector<Point2D>& points, size_t index, size_t half_window)
{
    for (size_t i = (index - half_window); i <= (index + half_window); i++)
    {
        if (!points[i].valid)
            return false;
    }
    return true;
}

float calculate_curvature(const std::vector<Point2D>& points, size_t index, size_t half_window)
{
    float diff_x = 0.0f;
    float diff_y = 0.0f;

    for(size_t i = 1; i <= half_window; i++)
    {
        diff_x += points[index + i].x - points[index].x;
        diff_x += points[index - i].x - points[index].x;

        diff_y += points[index + i].y - points[index].y;
        diff_y += points[index - i].y - points[index].y;
    }

    return diff_x * diff_x + diff_y * diff_y;
}

class LidarProcessor : public rclcpp::Node
{
    public:
        LidarProcessor()
            : Node("lidar_processor")
        {
            subscription_ =
                this->create_subscription<sensor_msgs::msg::LaserScan>(
                    "/scan",
                    10,
                    std::bind(&LidarProcessor::scan_callback, this, std::placeholders::_1)
                );       
                
            publisher_ =
                this->create_publisher<sensor_msgs::msg::PointCloud2>(
                    "/point_cloud",
                    10
                );
        }
    
    private:
        void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
        {
            RCLCPP_INFO(
                this->get_logger(),
                "frame_id: %s, r_min: %.2f m, r_max: %.2f m, theta_min: %.4f rad, theta_max: %.4f rad",
                msg->header.frame_id.c_str(),
                msg->range_min,
                msg->range_max,
                msg->angle_min,
                msg->angle_max
            );

            // ==========================================
            // 1. Chuyển LaserScan → Point2D
            // ==========================================
            std::vector<Point2D> points(msg->ranges.size());
            
            for(size_t i = 0; i < msg->ranges.size(); i++)
            {
                float r = msg->ranges[i];
                
                // Kiểm tra tính hợp lệ của khoảng cách
                if(!std::isfinite(r) || r < msg->range_min || r > msg->range_max)
                {
                    points[i].valid = false;
                    continue;
                }

                // Chuyển đổi dữ liệu tọa độ quét thành dạng Đề-các
                float theta = msg->angle_min + i * msg->angle_increment;
                points[i].x = r * std::cos(theta);
                points[i].y = r * std::sin(theta);
                points[i].valid = true;
            }

            // ==========================================
            // 2. Publish PointCloud2
            // ==========================================
            sensor_msgs::msg::PointCloud2 cloud;
            cloud.header = msg->header;
            cloud.height = 1;

            sensor_msgs::PointCloud2Modifier modifier(cloud);
            modifier.setPointCloud2FieldsByString(1, "xyz");

            size_t valid_count =
                std::count_if(
                    points.begin(),
                    points.end(),
                    [](const Point2D& p)
                    {
                        return p.valid;
                    }
                );

            modifier.resize(valid_count);

            sensor_msgs::PointCloud2Iterator<float> iter_x(cloud, "x");
            sensor_msgs::PointCloud2Iterator<float> iter_y(cloud, "y");
            sensor_msgs::PointCloud2Iterator<float> iter_z(cloud, "z");

            for (const auto& point : points)
            {
                if (!point.valid)
                    continue;

                *iter_x = point.x;
                *iter_y = point.y;
                *iter_z = 0.0f;

                ++iter_x;
                ++iter_y;
                ++iter_z;
            }

            publisher_->publish(cloud);

            size_t half_window = 5;
            std::vector<CurvaturePoint> curvature_points;

            for(size_t i = half_window; i < msg->ranges.size() - half_window; i++)
            {
                if (!valid_window(points, i, half_window))
                {
                    continue;
                }

                float curvature = calculate_curvature(points, i, half_window);
                curvature_points.push_back({curvature, i});

                if (i % 100 == 0)
                {
                    RCLCPP_INFO(
                        this->get_logger(),
                        "index=%zu curvature=%.6f",
                        i,
                        curvature
                    );
                }
            }
        }

        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LidarProcessor>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}