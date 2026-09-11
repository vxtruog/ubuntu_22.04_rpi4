# 1. Chạy bản có sẵn của SLAMTEC
- Kết nối lidar A3M1 vào cổng USB3.0 của raspberry pi 4, sau đó chạy lệnh
```
ls -l /dev/ttyUSB*  => user cần quyền dialout để truy cập
sudo usermod -aG dialout $USER
sudo reboot
```

- Chạy lidar
```
~/ros2/src
git clone https://github.com/Slamtec/sllidar_ros2.git
cd ~
source /opt/ros/humble/setup.bash
source ~/install/setup.bash
ros2 launch sllidar_ros2 sllidar_a3_launch.py
```

- Đọc dữ liệu lidar, mở terminal thứ hai và ssh tiếp vào raspberry pi 4
```
source /opt/ros/humble/setup.bash
source ~/install/setup.bash
ros2 topic list
ros2 run lidar_processor lidar_processor_node
```

- Sau khi dữ liệu xử lý lidar được publish lên PointCloud2 thì truy cập ROS2 trên laptop, bật rviz và cấu hình.
