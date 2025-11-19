# 🚗 Smart Vehicle Access Control System

### **Hệ thống Nhận diện Biển số Xe Tự động & Điều khiển Cổng Ra vào Thông minh**

Hệ thống bao gồm:

- **Frontend (Next.js)** – Giao diện nhận hình ảnh/video và hiển thị kết quả.
- **Backend (FastAPI)** – Xử lý nhận diện biển số (ALPR), phân tích blacklist/whitelist, gửi lệnh tới Arduino.
- **Arduino + Servo + LCD** – Nhận lệnh qua Serial, điều khiển barrier mở/đóng, hiển thị thông báo.
- **XAMPP + MySQL** – Lưu trữ biển số xe, lịch sử vào/ra.
- **Proteus** – Mô phỏng phần cứng (servo, Arduino, LCD I2C).

---
<img width="1896" height="906" alt="image" src="https://github.com/user-attachments/assets/27be09a3-277d-4a8f-a98b-c6189e80ce8d" />

## 📋 Mục lục

1. 📦 Cài đặt pnpm trên Windows
2. 🚀 Chạy dự án
3. 🗄️ Cài đặt Database (XAMPP)
4. ⚙️ Thay đổi Port cho API
5. 🔌 Nạp code Arduino
6. 🎛️ Mô phỏng Proteus
7. 🌐 Link GitHub

---

# 📦 Cài đặt pnpm trên Windows

### ⚠️ Cảnh báo:

Windows Defender đôi khi có thể chặn file thực thi `.ps1`.  
👉 Khuyên dùng cài đặt bằng **npm** hoặc **Corepack**.

### ✨ Cài đặt pnpm bằng PowerShell:

```powershell
Invoke-WebRequest https://get.pnpm.io/install.ps1 -UseBasicParsing | Invoke-Expression
```

---

# 🚀 Chạy dự án

### 1️⃣ Mở Terminal tại thư mục dự án

Sau đó cài đặt các gói phụ thuộc:

```bash
pnpm install
```

### 2️⃣ Khởi động backend + frontend + database:

```bash
pnpm dev
```

- Frontend chạy tại: `http://localhost:3000`
- Backend FastAPI chạy tại: `http://localhost:8000`
- Arduino kết nối qua Python (serial)

---

# 🗄️ Cài đặt Database (XAMPP)

### 1️⃣ Khởi động **Apache** + **MySQL**

Trong XAMPP Control Panel → Start cả 2 dịch vụ.

### 2️⃣ Mở phpMyAdmin

Truy cập:

```
http://localhost/phpmyadmin
```

### 3️⃣ Import database

Vào **Import → Chọn file**:

```
vehicle_detection.sql
```

### ✔ Database sẽ tạo bảng tự động:

- vehicles
- blacklist
- history
- detected_plates

---

# ⚙️ Thay đổi Port cho API

### Mở file:

```
api/conn.py
```

### Tìm dòng:

```python
PORT = 12345
```

Nếu muốn đổi:

```python
PORT = 3306
```

### Lưu và khởi động lại:

```bash
pnpm dev
```

⚠️ _Đảm bảo port mới chưa bị ứng dụng nào chiếm!_

---

# 🔌 Nạp code Arduino

Trong thư mục:

```
Smart_Vehicle_Access_Control_System.ino
```

### Các chức năng:

- Nhận chuỗi từ Python qua Serial (biển số hoặc `"NONE"`)
- Điều khiển 2 servo
- Hiển thị trạng thái lên LCD 16x2 I2C
- Có xử lý:
  - Biển số đúng
  - Không nhận diện được biển số
  - Cảnh báo

### Upload:

1. Mở Arduino IDE
2. Chọn board: **Arduino Nano**
3. Chọn đúng cổng COM
4. Upload code

---

# 🎛️ Mô phỏng Proteus

Trong thư mục:

```
Smart_Vehicle_Access_Control_System.pdsprj
```

Mô phỏng đầy đủ:

- Arduino Nano
- LCD I2C (0x27)
- 2 Servo barrier
- Nguồn và dây nối đúng thứ tự

🎯 Có thể kiểm thử trước khi triển khai phần cứng thật.

---

# 🌐 Link GitHub

```
https://github.com/1dathuynh/IoTProject
```

---
