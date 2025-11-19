#include <Servo.h>
#include <LiquidCrystal_I2C.h>

const int LCD_ADDRESS = 0x27; 
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS); 

Servo servo1; 
Servo servo2; 

const int SERVO_PIN_1 = 9; 
const int SERVO_PIN_2 = 10; 

const int ANGLE_CLOSED = 0; 
const int ANGLE_OPEN = 90; 
const int DELAY_TIME = 3000; 
// --- KẾT THÚC CẤU HÌNH SERVO ---

// Hàm setup
void setup() {
  Serial.begin(9600); 


  lcd.init();     
  lcd.backlight(); 
  

  lcd.setCursor(0, 0); 
  lcd.print("System Ready!"); 
  

  lcd.setCursor(0, 1);
  lcd.print("Waiting...");


  // --- SETUP SERVO ---
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2); 
  
  servo1.write(ANGLE_CLOSED); 
  servo2.write(ANGLE_CLOSED); 
  // --- KẾT THÚC SETUP SERVO ---
  
  Serial.println("Arduino Ready with LCD (I2C) and two Servos"); 
}


void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n'); 
    receivedData.trim(); 

    Serial.print("Received RAW: ");
    Serial.println(receivedData);

   if (receivedData == "NONE") {

      Serial.println("STATUS: NO_PLATE_DETECTED");

      lcd.setCursor(0, 0);
      lcd.print("BIEN SO XE");

      lcd.setCursor(0, 1);
      lcd.print("CHUA DANG KY !!!");

      // Không kích hoạt servo
      servo1.write(ANGLE_CLOSED);
      servo2.write(ANGLE_CLOSED);

      delay(2000);

      lcd.clear();
      lcd.print("Waiting...");
      lcd.setCursor(0, 1);
      lcd.print("...");

      return;
    }
    if (receivedData.length() > 0) {
      

      lcd.clear(); 
      lcd.print("XE DA DANG KY:");
      

      lcd.setCursor(0, 1); 

      if (receivedData.length() > 16) { 
        lcd.print(receivedData.substring(0, 16));
      } else {
        lcd.print(receivedData);
      }



      Serial.print("STATUS: BLACKLISTED_PLATE (");
      Serial.print(receivedData);
      Serial.println(") - Executing BLOCK Action.");


      servo1.write(ANGLE_OPEN); 
      Serial.println("ACTION: SERVO_1_OPENED (90)"); 
      
      servo2.write(ANGLE_OPEN); 
      Serial.println("ACTION: SERVO_2_ACTIVATED (90)");


      lcd.setCursor(14, 0); 
      lcd.print("OP"); 


      delay(DELAY_TIME); 
      
    
      servo1.write(ANGLE_CLOSED);
      Serial.println("ACTION: SERVO_1_CLOSED (0)"); 
      
      servo2.write(ANGLE_CLOSED);
      Serial.println("ACTION: SERVO_2_DEACTIVATED (0)"); 

      // Hiển thị trạng thái hoàn tất
      lcd.setCursor(14, 0); 
      lcd.print("CL"); // CLOSED
      
      // --- KẾT THÚC KHÓA ---
      

      delay(1000); 
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Action Complete."); 
      lcd.setCursor(0, 1);
      lcd.print("Waiting...");


    } else {
      Serial.println("STATUS: RECEIVED_EMPTY_COMMAND");
      
      // Hiển thị thông báo lỗi lên LCD
      lcd.clear();
      lcd.print("ERROR: EMPTY DATA");
      lcd.setCursor(0, 1);
      lcd.print("Waiting...");
    }
  }
}