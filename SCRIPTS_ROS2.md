# 1. Tổng quan cấu trúc trong ROS2
- Package là một thư mục dự án, chứa nhiều executable.
- Executable là một chương trình thực thi trong package, khi chạy có thể sinh ra một hoặc nhiều node.
- Node là một chương trình thực thi độc lập, khi chạy, node sẽ tham gia vào mạng ROS2 và có thể giao tiếp với các node khác.
- Một node có thể dùng 4 cơ chế chính để giao tiếp:
  + Topics (publish - subscribe), giao tiếp một chiều giữa các node từ publisher đến subscriber, dùng khi muốn publisher gửi dữ liệu liên tục, dữ liệu truyền trong topic được mô tả bằng một message_type.
  + Services (client - server), giao tiếp hai chiều đồng bộ giữa các node, dùng khi cần thực hiện một hành động cụ thể và chờ kết quả (client gửi "request" đợi server trả về "response").
  + Actions: (client - server), client yêu cầu thực hiện hành động mục tiêu, server nhận hành động sau đó gửi lại phản hồi liên tục và trả kết quả khi xong (client có thể gửi nhiều hành động mục tiêu hoặc tiếp tục xử lý khi server đang thực hiện).
  + Parameters: các giá trị cấu hình bên trong một node, giúp thay đổi hành vi của node mà không phải build lại.

# 2. Packages và Executables
- Tạo package, `cd ~/../src`, `ros2 pkg create <pkg_name> --build-type ament_cmake --dependencies rclcpp`
- `cd ~/../` -> `colcon build`, build tất cả package sau mỗi lần thay đổi.
- `colcon build --packages-select <package_name>`, build package chỉ định.
- `ros2 pkg list`: liệt kê tất cả các package có sẵn.
- `ros2 pkg executables <pkg_name>`: liệt kê tất cả các chương trình thực thi của một package nào đó.
- `ros2 run <pkg_name> <executable_name>`: chạy chương trình thực thi của một package.
  
# 3. Nodes
- `ros2 node list`: liệt kê tất cả các node đang chạy.
- `ros2 node info <node_name>`: xem thông tin của một node.

# 4. Topics
- `ros2 topic list`: liệt kê tất cả các topic đang chạy.
- `ros2 topic type <topic_name>`: xem message_type của topic (một topic chỉ sử dụng một message_type).
- `ros2 topic find <message_type>`: tìm các topic đang sử dụng message_type.
- `ros2 interface show <message_type>`: xem chi tiết cấu trúc của một message_type.
- `ros2 topic info <topic_name>`: xem thông tin của một topic.
- `ros2 topic pub --once <topic_name> <message_type> "<args>"`: publish dữ liệu đến topic chỉ một lần.
- `ros2 topic pub --rate x <topic_name> <message_type> "<args>"`: publish dữ liệu đến topic liên tục với tần số `x` Hz.
- `ros2 topic echo <topic_name>`: xem output của một topic.
- `ros2 bag record -o <bag_name> <topic_name>`: bắt đầu lưu trữ lại thông tin của một topic.
- `ros2 bag info <bag_name>`: xem thông tin của một bag đã ghi.
- `ros2 bag play <bag_name>`: để robot hành động lại những gì đã ghi trong bag.

# 5. Services
- `ros2 service list`: liệt kê tất cả các service đang chạy.
- `ros2 service type <service_name>`: xem service_type của service (một service chỉ sử dụng một service_type).
- `ros2 service find <service_type>`: tìm các service đang sử dụng service_type.
- `ros2 interface show <service_type>`: xem chi tiết cấu trúc của một service_type, gồm các tham số request và các tham số response.
- `ros2 service info <service_name>`: xem thông tin của một service.
- `ros2 service call <service_name> <service_type> "<request_data>"`: gửi một "request" tới service trong ROS2.

# 6. Actions
- `ros2 action list`: liệt kê tất cả các action đang chạy.
- `ros2 action type <action_name>`: xem action_type của action (một action chỉ sử dụng một action_type).
- `ros2 action info <action_name>`: xem thông tin của một action.
- `ros2 interface show <action_type>`: xem chi tiết cấu trúc của một action_type.
- `ros2 action send_goal <action_name> <action_type> <goal>`: gửi một hành động mục tiêu từ client đến server.

# 7. Parameters
- `ros2 param list`: liệt kê tất cả các tham số.
- `ros2 param get <node_name> <parameter_name>`: lấy giá trị của tham số.
- `ros2 param set <node_name> <parameter_name> <value>`: đặt giá trị cho tham số.
- `ros2 param dump <node_name>`: liệt kê tham số của một node.
- `ros2 param dump <node_name> > <node_name>.yaml`: lưu trữ tham số vào tệp .yaml.
- `ros2 param load <node_name> <node_name>.yaml`: tải tham số từ tệp .yaml.
- `ros2 run <package_name> <executable_name> --ros-args --params-file <executable_name>.yaml`: đặt tham số từ tệp .yaml ngay khi chạy package.
- `ros2 param delete <node_name> <parameter_name>`: xoá tham số, giữ nguyên giá trị tham số đang dùng tại thời điểm xoá và không thay đổi được tham số đó nữa.
