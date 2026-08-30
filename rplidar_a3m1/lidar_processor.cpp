#include <memory>
#include <vector>
#include <cmath>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

struct Point2D
{
    float x;
    float y;
    bool valid;
};

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

            std::vector<Point2D> points(msg->ranges.size());
            
            for(size_t i = 0; i < msg->ranges.size(); i++)
            {
                float r = msg->ranges[i];
                
                if(!std::isfinite(r) || r < msg->range_min || r > msg->range_max)
                {
                    points[i].valid = false;
                    continue;
                }

                float theta = msg->angle_min + i * msg->angle_increment;

                points[i].x = r * std::cos(theta);
                points[i].y = r * std::sin(theta);
                points[i].valid = true;
            }

            size_t half_window = 5;
            for(size_t i = half_window; i < msg->ranges.size() - half_window; i++)
            {
                float curvature = calculate_curvature(points, i, half_window);
            }
        }

        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LidarProcessor>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}