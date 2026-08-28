#include <memory>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

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
                "frame_id: %s, range_min: %.2f m, range_max: %.2f m, angle_min: %.4f rad, angle_max: %.4f rad",
                msg->header.frame_id.c_str(),
                msg->range_min,
                msg->range_max,
                msg->angle_min,
                msg->angle_max
            );
            
            size_t valid_count = 0;
            size_t invalid_count = 0;
            size_t out_of_range_count = 0;
            
            for(size_t i = 0; i < msg->ranges.size(); i++)
            {
                float distance = msg->ranges[i];
                
                if(!std::isfinite(distance))
                {
                    invalid_count++;
                    continue;
                }

                if(distance < msg->range_min || distance > msg->range_max)
                {
                    out_of_range_count++;
                    continue;
                }
                
                valid_count++;
            }

            RCLCPP_INFO(
                this->get_logger(),
                "total_points: %zu, valid_points: %zu, invalid_points: %zu, out_of_range: %zu\n",
                msg->ranges.size(),
                valid_count,
                invalid_count,
                out_of_range_count
            );
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