
#include <Servo.h>

// Định nghĩa chân Servo và các biến khác
Servo servo;
const int SERVO_PIN = 9; // Giả sử Servo nối vào D9
const int ANGLE_CLOSED = 0; // Góc đóng
const int ANGLE_OPEN = 90; // Góc mở (Hoặc góc cần thiết để mở/mô phỏng mở)
const int DELAY_TIME = 3000; // Thời gian giữ khóa mở (3 giây)

// Hàm setup
void setup() {
  // Bắt đầu giao tiếp Serial với Baudrate 9600
  Serial.begin(9600); 
  
  // Đính kèm Servo vào chân đã định nghĩa
  servo.attach(SERVO_PIN);
  
  // Đặt Servo về trạng thái đóng ban đầu
  servo.write(ANGLE_CLOSED); 
  
  // Gửi thông báo sẵn sàng
  Serial.println("Arduino Ready"); 
}

// Hàm loop
void loop() {
  // Kiểm tra nếu có dữ liệu từ cổng Serial
  if (Serial.available() > 0) {
    // Đọc chuỗi cho đến ký tự xuống dòng ('\n') mà Python gửi
    String receivedData = Serial.readStringUntil('\n'); 
    
    // Rất quan trọng: Loại bỏ các ký tự trắng/xuống dòng thừa để so sánh chính xác
    receivedData.trim(); 

    // --- BƯỚC DEBUG: IN DỮ LIỆU NHẬN ĐƯỢC ---
    Serial.print("Received RAW: ");
    Serial.println(receivedData);
    // --- KẾT THÚC DEBUG ---

    // LOGIC MỚI: Nếu nhận được bất kỳ dữ liệu nào (biển số), 
    // thì coi đó là lệnh BLOCK (vì Python đã lọc Blacklist)
    if (receivedData.length() > 0) {
      
      // --- BƯỚC XÁC NHẬN VÀ THỰC HIỆN KHÓA/BLOCK ---
      Serial.print("STATUS: BLACKLISTED_PLATE (");
      Serial.print(receivedData);
      Serial.println(") - Executing BLOCK Action.");

      // 1. Mở khóa Servo (Hành động ban đầu của bạn: mở ra một chút)
      servo.write(ANGLE_OPEN); 
      Serial.println("ACTION: SERVO_OPENED (90)"); 
      
      // Giữ mở trong 3 giây
      delay(DELAY_TIME); 
      
      // 2. Đóng khóa Servo lại (Hành động BLOCK: đảm bảo cổng đã đóng)
      servo.write(ANGLE_CLOSED);
      Serial.println("ACTION: SERVO_CLOSED (0)"); 
      
      // Nếu bạn chỉ muốn BLOCK (giữ đóng), bạn chỉ cần dùng lệnh dưới đây:
      // servo.write(ANGLE_CLOSED);
      // Serial.println("ACTION: SERVO_BLOCKED_CLOSED");
      // --- KẾT THÚC KHÓA ---

    } else {
      // Trường hợp hiếm: Python gửi dữ liệu trống
      Serial.println("STATUS: RECEIVED_EMPTY_COMMAND");
    }
  }
}