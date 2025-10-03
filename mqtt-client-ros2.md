# Trước hết hãy cài ROS2 trên Raspberry Pi 4
# Các thao tác triển khai mqtt_client trên ROS2
- Tải gói mqtt_client
```
mkdir -p mqtt_ws/src && cd ~/mqtt_ws/src
git clone https://github.com/ika-rwth-aachen/mqtt_client.git
```
- Cài đặt môi trường python2 và xây dựng packages
```
sudo apt-get install python3-pip
sudo apt install python3-colcon-common-extensions

cd ~/mqtt_ws
colcon build --packages-up-to mqtt_client --cmake-args -DCMAKE_BUILD_TYPE=Release
```
- Chuẩn bị MQTT Broker
```
sudo apt update
sudo apt install -y mosquitto mosquitto-clients
```
- Một số lệnh sử dụng cho MQTT Broker
```
sudo systemctl start mosquitto
sudo systemctl stop mosquitto
sudo systemctl enable mosquitto
sudo systemctl disable mosquitto
sudo systemctl status mosquitto
```
- Mở ba tab terminal, chạy các lệnh tương ứng với các tab
```
tab1:
mosquitto_sub -h localhost -p 1883 -t pingpong/ros
tab2:
ros2 launch mqtt_client standalone.launch.ros2.xml
tab3 (tab này nên chạy cuối cùng):
ros2 topic pub /ping/ros std_msgs/msg/String "{data: 'Hello MQTT'}"
```
# Tài liệu tham khảo thêm
- https://zenn.dev/tasada038/articles/f011ca5d5a2f3f
- https://docs.ros.org/en/noetic/api/mqtt_client/html/index.html
