const int buttonMoGuong = A0;     // Chân nút ấn được nối với chân A0
const int buttonGapGuong = A1;
const int buttonChonGuong = A2;   // Chân analog để đọc giá trị chế độ
//const int MIRE = A3;              //chan MIRE
const int buttonDieuHuong = A3;         // Chân analog để đọc giá trị nút điều chỉnh gương

int buttonState1 = 0;         // Trạng thái hiện tại của nút ấn
int lastButtonState1 = 0;     // Trạng thái trước đó của nút ấn
int buttonState2 = 0;
int lastButtonState2 = 0;
int GUONGTRAI = 0;
int GUONGPHAI = 0;

const int IN1=12; //gap mo trai 1
const int IN2=13; //gap mo trai 2
const int IN3=6;  //gap mo phai 1
const int IN4=7;  //gap mo phai 2

const int IN5=10; //len xuong trai 1
const int IN6=11; //len xuong trai 2
const int IN7=8;  //trai phai trai 1
const int IN8=9;  //trai phai trai 2

const int IN9=4;  //len xuong phai 1
const int IN10=5; //len xuong phai 2
const int IN11=2; //trai phai phai 1
const int IN12=3; //trai phai phai 2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(5000);
  pinMode(buttonMoGuong, INPUT_PULLUP); // Đặt chân nút là đầu vào
  pinMode(buttonGapGuong, INPUT_PULLUP);
  //pinMode(MIRE, OUTPUT); //Dat chan MIRE la dau ra
  pinMode(buttonChonGuong, INPUT);
  pinMode(buttonDieuHuong, INPUT);
  analogWrite(IN1,0);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,0);  
  analogWrite(IN5,0);
  analogWrite(IN6,0);
  analogWrite(IN7,0);
  analogWrite(IN8,0);  
  analogWrite(IN9,0);
  analogWrite(IN10,0);
  analogWrite(IN11,0);
  analogWrite(IN12,0);
  //digitalWrite(MIRE, HIGH);
}

void loop() {
//////////////////////////////////////////////////////////////////////  
  buttonState1 = digitalRead(buttonMoGuong); // Đọc trạng thái của nút
  buttonState2 = digitalRead(buttonGapGuong);
  int ChonGuong = analogRead(buttonChonGuong);
  int dieuHuong = analogRead(buttonDieuHuong);
    Serial.print(" A0: ");
    Serial.print(buttonState1);
    Serial.print(" A1: ");
    Serial.print(buttonState2);
    delay(500);
  // Kiểm tra xem nút đã được ấn hay chưa
  if (buttonState1 == LOW || buttonState2 == LOW){
  if ((buttonState1 != lastButtonState1) && (buttonState2 != lastButtonState2)) {
    // Nếu trạng thái của nút thay đổi
    if (buttonState1 == HIGH && buttonState2 == LOW) {
      // Nếu nút được ấn giữ, mo guong
      MOGUONG(255);
      delay(150);
    } else if ( buttonState1 == LOW && buttonState2 == HIGH ){
      // Nếu nút được nhả ra, gap guong
      GAPGUONG(255);
      delay(150);
    }
  }
  // Lưu trạng thái của nút cho lần lặp tiếp theo
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
  }else{
//////////////////////////////////////////////////////////////////////
// Đọc giá trị analog từ chân A1
    Serial.print("  A2: ");
    Serial.print(ChonGuong);
  // Chuyển đổi giá trị analog sang các trạng thái của LED
    if (ChonGuong < 100) {
      KHONGCHINHGUONG();
    } else {
        if (ChonGuong >= 100 && ChonGuong < 600) {
          //dieu chinh long guong trai
          int dieuHuong = analogRead(buttonDieuHuong); //đọc giá trị chân analog A3 để điều hướng
          Serial.print(" A3t: ");
          Serial.println(dieuHuong); 
    // Chuyển đổi giá trị analog 
        } else {
        if (dieuHuong < 256) {
          LENTRAI(255);
        } else if (dieuHuong >= 256 && dieuHuong < 515) {
          PHAITRAI(255);
        } else if (dieuHuong >= 515 && dieuHuong < 768) {
          XUONGTRAI(255);
        } else {
          TRAITRAI(255);
        }
      } else {
    //dieu chinh long guong phai
     //đọc giá trị chân analog A3 để điều hướng
    // Chuyển đổi giá trị analog 
                if (dieuHuong < 256) {
                  LENPHAI(255);
                } else if (dieuHuong >= 256 && dieuHuong < 512) {
                  PHAIPHAI(255);
                } else if (dieuHuong >= 512 && dieuHuong < 768) {
                  XUONGPHAI(255);
                } else {
                  TRAIPHAI(255);
                }
             }
            }
        }
    }
    Serial.print(" A3p: ");
    Serial.println(dieuHuong);
}

void MOGUONG (int Speed){
  analogWrite(IN1,Speed);
  analogWrite(IN2,0);
  analogWrite(IN3,Speed);
  analogWrite(IN4,0);
}
void GAPGUONG (int Speed){
  analogWrite(IN1,0);
  analogWrite(IN2,Speed);
  analogWrite(IN3,0);
  analogWrite(IN4,Speed);
}
void LENTRAI (int Speed){
  analogWrite(IN5,Speed);
  analogWrite(IN6,0);
  analogWrite(IN7,0);
  analogWrite(IN8,0);
}
void XUONGTRAI (int Speed){
  analogWrite(IN5,0);
  analogWrite(IN6,Speed);
  analogWrite(IN7,0);
  analogWrite(IN8,0);  
}
void TRAITRAI (int Speed){
  analogWrite(IN5,0);
  analogWrite(IN6,0);
  analogWrite(IN7,Speed);
  analogWrite(IN8,0);  
}
void PHAITRAI (int Speed){
  analogWrite(IN5,0);
  analogWrite(IN6,0);
  analogWrite(IN7,0);
  analogWrite(IN8,Speed);  
}
void LENPHAI(int Speed){
  analogWrite(IN9,Speed);
  analogWrite(IN10,0);
  analogWrite(IN11,0);
  analogWrite(IN12,0);
}
void XUONGPHAI(int Speed){
  analogWrite(IN9,0);
  analogWrite(IN10,Speed);
  analogWrite(IN11,0);
  analogWrite(IN12,0);  
}
void TRAIPHAI (int Speed){
  analogWrite(IN9,0);
  analogWrite(IN10,0);
  analogWrite(IN11,Speed);
  analogWrite(IN12,0);    
}
void PHAIPHAI (int Speed){
  analogWrite(IN9,0);
  analogWrite(IN10,0);
  analogWrite(IN11,0);
  analogWrite(IN12,Speed);   
}
void KHONGCHINHGUONG (){
  analogWrite(IN5,0);
  analogWrite(IN6,0);
  analogWrite(IN7,0);
  analogWrite(IN8,0);  
  analogWrite(IN9,0);
  analogWrite(IN10,0);
  analogWrite(IN11,0);
  analogWrite(IN12,0);   
}