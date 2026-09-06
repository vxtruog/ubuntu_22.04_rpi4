```
sensor_msgs/msg/LaserScan
├── header : Header
│   ├── stamp : Time
│   │   ├── sec
│   │   └── nanosec
│   └── frame_id : string
├── angle_min : float32 (góc của phép đo đầu tiên [rad])
├── angle_max : float32 (góc của phép đo cuối cùng [rad])
├── angle_increment : float32 (khoảng cách góc giữa 2 phép đo liên tiếp [rad])
├── time_increment : float32 (thời gian giữa 2 phép đo liên tiếp [s])
├── scan_time : float32 (thời gian thực hiện một scan hoàn chỉnh [s]
├── range_min : float32 (khoảng cách nhỏ nhất hợp lệ [m])
├── range_max : float32 (khoảng cách lớn nhất hợp lệ [m])
├── ranges : float32[] (khoảng cách đo được của từng tia [m])
└── intensities : float32[] (cường độ phản xạ tương ứng với từng tia)
```
```
sensor_msgs/msg/PointCloud2
├── header : Header
│   ├── stamp : Time
│   │   ├── sec
│   │   └── nanosec
│   └── frame_id : string
├── height : uint32 (số hàng của point cloud)
├── width : uint32 (số point trong mỗi hàng)
├── fields : PointField[] (mô tả cấu trúc của một point: tên các field trong point, vị trí offset, kiểu dữ liệu và có bao nhiêu phần tử)
│   ├── fields[0] : PointField
│   │   ├── name
│   │   ├── offset
│   │   ├── datatype
│   │   └── count
│   ├── fields[1] : PointField
│   │   ├── name
│   │   ├── offset
│   │   ├── datatype
│   │   └── count
│   └── ...
├── is_bigendian : bool (thứ tự lưu các byte)
├── point_step : uint32 (số byte của một point)
├── row_step : uint32 (số byte của một hàng)
├── data : uint8[] (chứa giá trị thực tế của tất cả các point dưới dạng một mảng byte)
│   ├── Point 0
│   │   ├── giá trị field 0
│   │   ├── giá trị field 1
│   │   └── ...
│   └── ...
└── is_dense : bool (có điểm không hợp lệ không)
