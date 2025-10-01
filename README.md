# Các bước cài đặt
- Bước 1: Vào phần mềm Raspberry Pi Imager, tải Ubuntu Server 22.04.5 LTS (64-bit). Không cần cấu hình gì thêm, chỉ cài đặt thôi.
- Bước 2: Chỉnh sửa tệp config
```
- Bước 3: Chỉnh sửa tệp cmdline, nhớ để các cấu hình trên cùng một dòng, thêm `cloud-init=disabled` vì ban đầu khi khởi động chỉ giao tiếp UART, chưa có Wifi, nếu không chặn cloud-init thì trong lúc khởi động sẽ bị treo ở quá trình Rapsberry Pi lấy dữ liệu ở cloud-init.
```
console=serial0,115200 multipath=off dwc_otg.lpm_enable=0 console=tty1 root=LABEL=writable rootfstype=ext4 rootwait fixrtc cloud-init=disabled
```

