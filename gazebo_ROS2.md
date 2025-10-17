# Trước hết hãy cài đặt ROS2 Humble trên Raspberry Pi
# Cài đặt môi trường
```
source /opt/ros/humble/setup.bash
sudo apt update
sudo apt upgrade -y
sudo apt install ros-humble-joint-state-publisher
sudo apt install ros-humble-joint-state-publisher-gui
sudo apt install ros-humble-xacro

sudo apt-get install ros-humble-ros-gz
sudo apt install ros-humble-gazebo-ros-pkgs
sudo apt install ros-humble-ros-core

sudo apt install ros-humble-geometry2
sudo apt-get install ros-humble-gazebo-msgs
sudo apt-get install ros-humble-gazebo-plugins

sudo apt-get install ros-humble-ros-ign-bridge
sudo apt-get install ros-humble-teleop-twist-keyboard
```

# Thiết lập workspace
```
- Tạo workspace, tạo thư mục /src trong workspace và chạy lệnh
colcon build
- Truy cập tệp /src trong workspace
ros2 pkg create --build-type ament_cmake mobile_dd_robot
- Truy cập tệp mobile_dd_robot tạo tệp
  + launch: chứa tệp launch python để chạy mô hình trong gazebo
  + model: chứa tệp mã Xacro (định nghĩa một số biến) và URDF (chỉ định hình học của robot) của mô hình
- Truy cập thư mục model, tạo robot.xacro và robot.gazebo
- Truy cập thư mục launch, tạo tệp gazebo_model.launch.py
```

```
- Thêm phụ thuộc và tệp package.xml
<exec_depend>joint_state_publisher</exec_depend>
<exec_depend>robot_state_publisher</exec_depend>
<exec_depend>gazebo_ros</exec_depend>
<exec_depend>xacro</exec_depend>
<exec_depend>ros_gz_bridge</exec_depend>
- Điều chỉnh tệp CMakelists.txt
install(
  DIRECTORY launch model
  DESTINATION share/${PROJECT_NAME}
)
```
