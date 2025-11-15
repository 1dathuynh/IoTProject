import serial
import time

# Cấu hình cổng Serial (Phải đúng với cổng Arduino Nano đang kết nối)
# LƯU Ý: Phải đặt trong dấu ngoặc kép!
SERIAL_PORT = "COM2" 
BAUD = 9600

def send_to_arduino(command: str):
    """Gửi một lệnh (biển số xe) đến Arduino qua Serial và chờ phản hồi đầy đủ.
    
    Phản hồi được ghi vào 'full_response' bằng cách đọc từng dòng cho đến khi hết dữ liệu.
    """
    
    # Biến lưu trữ toàn bộ phản hồi
    full_response = ""
    
    try:
        # Mở cổng Serial
        # Timeout TĂNG lên 4 giây (lớn hơn 3 giây delay của Servo)
        with serial.Serial(SERIAL_PORT, BAUD, timeout=4) as ser:
            # Rất quan trọng: Xóa bộ đệm đầu vào để loại bỏ các thông báo cũ còn sót lại
            ser.reset_input_buffer() 
            
            # 1. Gửi lệnh. Thêm ký tự xuống dòng (\n) để Arduino biết chuỗi kết thúc.
            msg = command.strip() + "\n" 
            ser.write(msg.encode('utf-8'))
            
            print(f"[Serial] Sent to Arduino: {command}")
            
            # Cần một chút thời gian để Arduino xử lý và bắt đầu gửi phản hồi
            time.sleep(0.1) 
            
            # 2. Đọc các dòng phản hồi từ Arduino cho đến khi timeout
            while ser.in_waiting > 0:
                # Đọc một dòng (chờ đến khi thấy ký tự '\n' hoặc timeout)
                line = ser.readline()
                if line:
                    # Giải mã và loại bỏ khoảng trắng/xuống dòng, thêm dấu phân cách '|'
                    full_response += line.decode(errors="ignore").strip() + " | "
                else:
                    break # Hết dữ liệu
            
            # In phản hồi sau khi đã đọc hết tất cả các dòng
            if full_response.strip():
                # Loại bỏ dấu '|' cuối cùng
                print(f"[Arduino response]: {full_response.strip().rstrip('|').strip()}")
            else:
                print("[Arduino response]: No response received within timeout.")

    except serial.SerialException as se:
        # Bắt lỗi cụ thể khi không mở được cổng COM
        print(f"--- [Serial Error] ---")
        print(f"Không thể mở cổng {SERIAL_PORT}. Vui lòng kiểm tra:")
        print(f"1. Arduino đã kết nối và driver đã cài đặt.")
        print(f"2. Cổng {SERIAL_PORT} có đúng không (Thường là COM3, COM4, v.v.).")
        print(f"3. Không có chương trình nào khác đang chiếm cổng Serial này (ví dụ: Serial Monitor).")
        print(f"Lỗi chi tiết: {se}")
    except Exception as e:
        print(f"[Unknown Error]: {e}")