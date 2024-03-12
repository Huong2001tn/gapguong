const int buttonMoGuong = A0;     // Chân nút ấn được nối với chân A0
const int buttonGapGuong = A1;
const int buttonChonGuong = A2;   // Chân analog để đọc giá trị chế độ
//const int MIRE = A3;              //chan MIRE
const int buttonDieuHuong = A3;         // Chân analog để đọc giá trị nút điều chỉnh gương

int buttonState1=0;
int buttonState2=0;
boolean guongState=0;
int ChonGuong=0;
int dieuHuong=0;
boolean  guongTrai = 0;
boolean  guongPhai = 0;
boolean  lenState = 0;
boolean  phaiState = 0;
boolean  xuongState = 0;
boolean  traiState = 0;
const int IN1=2; //gap mo trai 1
const int IN2=3; 
const int IN3=4;  //gap mo phai 1
const int IN4=5;  

const int IN5=6; //len xuong trai 1
const int IN6=7; //len xuong trai 2
const int IN7=8;  //trai phai trai 1
const int IN8=9;  //trai phai trai 2

const int IN9=10;  //len xuong phai 1
const int IN10=11; //len xuong phai 2
const int IN11=12; //trai phai phai 1
const int IN12=13; //trai phai phai 2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonMoGuong, INPUT_PULLUP); // Đặt chân nút là đầu vào
  pinMode(buttonGapGuong, INPUT_PULLUP);
  // Set DDRD register for pins 2 to 7 to output
  DDRD |= B11111100; // Pins 2-7
  // Set DDRB register for pins 8 to 13 to output
  DDRB |= B00111111; // Pins 8-13

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState1 = digitalRead(buttonMoGuong); // Đọc trạng thái của nút
  buttonState2 = digitalRead(buttonGapGuong);
  ChonGuong = analogRead(buttonChonGuong);
  dieuHuong = analogRead(buttonDieuHuong);
    Serial.print(" A0: ");
    Serial.print(buttonState1);
    Serial.print(" A1: ");
    Serial.print(buttonState2);
    Serial.print(" guongState: ");
    Serial.print(guongState);
    Serial.print("  A2: ");
    Serial.print(ChonGuong);
    Serial.print(" A3: ");
    Serial.print(dieuHuong); 
    Serial.print(" guongT: ");
    Serial.print(guongTrai); 
    Serial.print(" guongP: ");
    Serial.print(guongPhai);
    Serial.print(" Len: ");
    Serial.print(lenState); 
    Serial.print(" Phai: ");
    Serial.print(phaiState);
    Serial.print(" Xuong: ");
    Serial.print(xuongState); 
    Serial.print(" Trai: ");
    Serial.print(traiState);
    Serial.print(" IN9,10,11,12: ");
    Serial.print(IN8);
    Serial.print(" ");
    Serial.print(IN9);
    Serial.print(" ");
    Serial.print(IN10);
    Serial.print(" ");
    Serial.print(IN11);
    Serial.print(" ");
    Serial.println(IN12);
    delay(500);
/////////////////////////////////////////////
  if(buttonState1 == HIGH && buttonState2 == LOW){
    MOGUONG(255);
    guongState = 1;
  } else {
     if(buttonState1 == LOW && buttonState2 == HIGH){
     GAPGUONG(255); 
     guongState = 0;    
     }
  } 
     //////////////////////////////////////
      if (ChonGuong > 900){
        guongPhai = 1;
        guongTrai = 0;
      } else {
        if (ChonGuong > 100){
          guongTrai = 1;
          guongPhai = 0;
          
        } else {
          if(ChonGuong >= 0){
            guongTrai = 0;
            guongPhai = 0;
          }
        }
      }
      if(guongTrai == 1 && dieuHuong > 950){
        lenState = 1;
        phaiState = 0;
        xuongState = 0;
        traiState = 0;
        UL(255);
      } else {
        if(guongTrai == 1 && dieuHuong > 60){
        lenState = 0;
        phaiState = 1;
        xuongState = 0;
        traiState = 0;
        RL(200);
        } else {
          if(guongTrai == 1 && dieuHuong > 30){
            lenState = 0;
            phaiState = 0;
            xuongState = 1;
            traiState = 0;
            DL(255);
          } else {
            if (guongTrai == 1 && dieuHuong > 5){
            lenState = 0;
            phaiState = 0;
            xuongState = 0;
            traiState = 1;
            LL(200);
            } else {
              if (guongTrai == 1 && dieuHuong <=5 ){
                lenState = 0;
                phaiState = 0;
                xuongState = 0;
                traiState = 0;
                OFFM();
              } else {
                if(guongPhai == 1 && dieuHuong > 950){ //chinh long guong phai
                  lenState = 1;
                  phaiState = 0;
                  xuongState = 0;
                  traiState = 0;
                  UR(255);
                } else {
                  if(guongPhai == 1 && dieuHuong > 60){
                    lenState = 0;
                    phaiState = 1;
                    xuongState = 0;
                    traiState = 0;
                    RR(200);
                  } else {
                    if(guongPhai == 1 && dieuHuong > 30){
                      lenState = 0;
                      phaiState = 0;
                      xuongState = 1;
                      traiState = 0;
                      DR(255);                      
                    } else {
                      if (guongPhai == 1 && dieuHuong > 5){
                      lenState = 0;
                      phaiState = 0;
                      xuongState = 0;
                      traiState = 1;
                      LR(200);
                      } else {
                        if (guongPhai == 1 && dieuHuong <=5 ){
                          lenState = 0;
                          phaiState = 0;
                          xuongState = 0;
                          traiState = 0;
                          OFFM();
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }



}
//////////////////////////////
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
///////////////////////////////////////
void UL (int Speed){
  analogWrite(IN5,Speed);
  analogWrite(IN6,0);
  analogWrite(IN7,0);
  analogWrite(IN8,0);
}
void DL (int Speed){
  analogWrite(IN5,0);
  analogWrite(IN6,Speed);
  analogWrite(IN7,Speed);
  analogWrite(IN8,Speed); 
}
void LL (int Speed){
  analogWrite(IN5,0);
  analogWrite(IN6,0);
  analogWrite(IN7,Speed);
  analogWrite(IN8,0);
}
void RL (int Speed){
  analogWrite(IN5,0);
  analogWrite(IN6,Speed);
  analogWrite(IN7,Speed);
  analogWrite(IN8,Speed); 
}
//////////////////////////////////////////////////
void UR (int Speed){
  analogWrite(IN9,Speed);
  analogWrite(IN10,0);
  analogWrite(IN11,0);
  analogWrite(IN12,0);
}
void DR (int Speed){
  analogWrite(IN9,0);
  analogWrite(IN10,Speed);
  analogWrite(IN11,Speed);
  analogWrite(IN12,Speed); 
}
void LR (int Speed){
  analogWrite(IN9,0);
  analogWrite(IN10,0);
  analogWrite(IN11,Speed);
  analogWrite(IN12,0);
}
void RR (int Speed){
  analogWrite(IN9,Speed);
  analogWrite(IN10,Speed);
  analogWrite(IN11,0);
  analogWrite(IN12,Speed); 
}
/////////////////////////////////////////////
void OFFM (){
  analogWrite(IN5,0);
  analogWrite(IN6,0);
  analogWrite(IN7,0);
  analogWrite(IN8,0);  
  analogWrite(IN9,0);
  analogWrite(IN10,0);
  analogWrite(IN11,0);
  analogWrite(IN12,0);   
}