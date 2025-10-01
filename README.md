# Các bước cài đặt
- Bước 1: Vào phần mềm Raspberry Pi Imager, tải Ubuntu Server 22.04.5 LTS (64-bit). Không cần cấu hình gì thêm, chỉ cài đặt thôi.
- Bước 2: Chỉnh sửa tệp config, tại đây chỉ thêm cấu hình cho hiển thị màn hình HDMI.
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
- Bước 3: Chỉnh sửa tệp cmdline, nhớ để các cấu hình trên cùng một dòng, thêm `cloud-init=disabled` vì ban đầu khi khởi động chỉ giao tiếp UART, chưa có Wifi, nếu không chặn cloud-init thì trong lúc khởi động sẽ bị treo ở quá trình Rapsberry Pi lấy dữ liệu ở cloud-init.
```
console=serial0,115200 multipath=off dwc_otg.lpm_enable=0 console=tty1 root=LABEL=writable rootfstype=ext4 rootwait fixrtc cloud-init=disabled
```

