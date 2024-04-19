#include <SoftwareSerial.h>

#define RX_PIN 8  // Chọn chân cho RX của Arduino
#define TX_PIN 9  // Chọn chân cho TX của Arduino

SoftwareSerial MySerial(RX_PIN, TX_PIN); // Khai báo UART trên Arduino

String substring_data_recieved(String data){
  if ((data.charAt(0) != ' ') && (data.charAt(data.length() - 1)!=' ')) {
    data = data.substring(1, data.length() - 1); 
  }
  return data;   
}

bool check_data_recieve_error(String data,char fchar=' ',char echar=' '){
  bool check = false ;
  if ((data.charAt(0) == fchar) && (data.charAt(data.length() - 1) == echar) && (data.length()> 0)){
    for(int i = 0; i< data.length(); i++){
      char c = data.charAt(i);
      if (!isPrintable(c)){
        check = true;
        break;
      }
    }
  }
  else check = true;
  return check;   
}
void setup() {
  Serial.begin(9600); // Khởi động giao tiếp Serial với máy tính
  MySerial.begin(9600); // Khởi động giao tiếp với ESP8266
}

void loop() {
  if (MySerial.available()) { // Kiểm tra xem có dữ liệu từ ESP8266 không
    String receivedData = MySerial.readStringUntil('\n'); // Đọc dữ liệu từ ESP8266 cho đến khi gặp ký tự xuống dòng
    Serial.print("Received: ");
    Serial.println(receivedData); // Hiển thị dữ liệu nhận được trên Serial Monitor
    Serial.print("Length Recevied: ");
    Serial.println(receivedData.length()); //Hiển thị độ dài dữ liệu nhận được trên Serial Monitor

    bool check_data = check_data_recieve_error(receivedData);  //kiểm tra chuỗi lỗi, 0-> chuỗi không lỗi, ngược lại.

    if (!check_data){
        
         receivedData = substring_data_recieved(receivedData);
    }
    else Serial.println("Chuỗi lỗi!!!!");
    
   MySerial.println(check_data); //gửi trạng thái chuỗi về app
  }

  //thử nghiệm gửi dữ liệu từ Serial Montitor
  if(Serial.available() > 0 ){
        MySerial.write(Serial.read());
   }

   
}

