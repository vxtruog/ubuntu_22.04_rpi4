# Các bước cài đặt Ubuntu Server 22.04 LTS trên Raspberry Pi 4
- __Bước 1__: Vào phần mềm Raspberry Pi Imager, tải Ubuntu Server 22.04.5 LTS (64-bit). Không cần cấu hình gì thêm, chỉ cài đặt thôi.
- __Bước 2__: Chỉnh sửa tệp config, tại đây chỉ thêm cấu hình cho hiển thị màn hình HDMI.
```
[all]
kernel=vmlinuz
cmdline=cmdline.txt
initramfs initrd.img followkernel

[pi4]
max_framebuffers=2
arm_boost=1

[all]
# Enable the audio output, I2C and SPI interfaces on the GPIO header. As these
# parameters related to the base device-tree they must appear *before* any
# other dtoverlay= specification
dtparam=audio=on
dtparam=i2c_arm=on
dtparam=spi=on

# Comment out the following line if the edges of the desktop appear outside
# the edges of your display
disable_overscan=1

# If you have issues with audio, you may try uncommenting the following line
# which forces the HDMI output into HDMI mode instead of DVI (which doesn't
# support audio output)
#hdmi_drive=2

# Enable the serial pins
enable_uart=1

# Autoload overlays for any recognized cameras or displays that are attached
# to the CSI/DSI ports. Please note this is for libcamera support, *not* for
# the legacy camera stack
camera_auto_detect=1
display_auto_detect=1

# Config settings specific to arm64
arm_64bit=1
dtoverlay=dwc2

# Config HDMI
hdmi_group=2
hdmi_mode=87
hdmi_cvt 800 480 60 6 0 0 0

[cm4]
# Enable the USB2 outputs on the IO board (assuming your CM4 is plugged into
# such a board)
dtoverlay=dwc2,dr_mode=host

[all]
```
- __Bước 3__: Chỉnh sửa tệp cmdline, nhớ để các cấu hình trên cùng một dòng, thêm `cloud-init=disabled` vì ban đầu khi khởi động chỉ giao tiếp UART, chưa có Wifi, nếu không chặn cloud-init thì trong lúc khởi động sẽ bị treo ở quá trình Rapsberry Pi lấy dữ liệu ở cloud-init.
```
console=serial0,115200 multipath=off dwc_otg.lpm_enable=0 console=tty1 root=LABEL=writable rootfstype=ext4 rootwait fixrtc cloud-init=disabled
```
- __Bước 4__: Bắt đầu mount thẻ SD để thêm tài khoản người dùng và kết nối mật khẩu.
```
- Tạo tệp để mount
sudo mkdir /mnt/pi-root
sudo mount /dev/sdb2 /mnt/pi-root

- Tạo chuỗi băm cho mật khẩu
openssl passwd -6 "truong123"
>> $6$...........

- Thêm user vào /etc/passwd
sudo nano /mnt/pi-root/etc/passwd
>> thêm dòng
ubuntu:x:1001:1001:Ubuntu:/home/ubuntu:/bin/bash

- Thêm password vào /etc/shadow
sudo nano /mnt/pi-root/etc/shadow
>> thêm dòng
ubuntu:$6$<điền đầy đủ>:19777:0:99999:7:::

- Thêm group cho user tại /etc/group
sudo nano /mnt/pi-root/etc/group
>> thêm dòng
ubuntu:x:1001:
sudo:x:27:ubuntu
adm:x:4:ubuntu

- Tạo thư mục home cho user
sudo mkdir /mnt/pi-root/home/ubuntu
sudo chown 1001:1001 /mnt/pi-root/home/ubuntu

- Unmount
cd ~
sudo umount /mnt/pi-root

- Lúc này khi khởi động Raspberry Pi 4 sẽ đăng nhập với user là ubuntu, password là truong123.
```
- __Bước 5__: Truy cập SSH vào Raspberry Pi 4 từ Laptop bằng public key
```
- Tạo SSH key trên laptop
ssh-keygen -t ed25519 -C "pi@laptop"

- Từ truy cập UART với Raspberry Pi, tạo thư mục và dán public key vào Raspberry Pi
mkdir -p ~/.ssh
nano ~/.ssh/authorized_keys
>> dán nội dung trong tệp id_ed25519.pub từ laptop vào đây

- Thay đổi quyền cho thư mục SSH
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys

- Thêm kết nối WiFi cho Raspberry Pi 4
sudo nano /etc/netplan/50-cloud-init.yaml
>> thêm đoạn
network:
  ethernets:
    eth0:
      dhcp4: true
      optional: true
  wifis:
    wlan0:
      optional: true
      access-points:
        "Ngoc Thuy":
          password: "trongnam812"
      dhcp4: true
>> sau đó sửa quyền của tệp và chạy cấu hình
sudo chmod 600 /etc/netplan/50-cloud-init.yaml
sudo netplan apply
>> tìm địa chỉ IP của Raspberry Pi 4
ip addr show wlan0

- Khởi động SSH trên Raspberry Pi
sudo systemctl enable ssh
sudo systemctl start ssh
sudo systemctl status ssh

- Truy cập SSH từ laptop đã tạo public key
ssh ubuntu@192.168.2.x
```

# Cài đặt ROS2 Humble trên Raspberry Pi 4
- Cài đặt ROS2:
https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html
- Lựa chọn phiên bản ros-humble-ros-base để chạy không cần GUI cho nhẹ chương trình.
- Tìm hiểu thêm về rclcpp:
https://docs.ros2.org/foxy/api/rclcpp/namespacerclcpp.html
