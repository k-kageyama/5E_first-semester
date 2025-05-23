#include <SPI.h>
int value; // MAX6675からのデータ格納変数
int outputPin = 4;
//on_time off_time ヒータ稼働時間設定変数
//on_time 0~1000 
double on_time;
double off_time;

//PID制御　パラメータ
//Kp,Ki,Kd ゲイン
int Kp = 1;
int Ki = 0;
int Kd = 0;
double P;
double I;
double D;
double target = 60.0; //目標温度
double temp; //センサーが読み取る温度
double mv; //操作量
void setup() {
  
  //SPI通信の初期設定
  SPI.setBitOrder(MSBFIRST);           // 上位ビットから送信
  SPI.setClockDivider(SPI_CLOCK_DIV4); // 分周期1/4指定 16MHz/4=4MHz(MAX6675仕様：Max 4.3MHz)
  SPI.setDataMode(SPI_MODE0);          // アイドル時Low、立上がりエッジでデータ取得
  SPI.begin();                         // SPI通信の初期化、有効化
  Serial.begin(9600);                  // シリアル通信のデータ転送レートを9600bpsで指定

  //仮の5V出力
  pinMode(outputPin, OUTPUT); 
  
}

void loop() { 
  
  //温度データ読み出し
  //ここの500ms分をonofftime 1000msで補う
  //delay(500);                       // MAX6675仕様(Conversion Time > 220ms)
  
  digitalWrite(SS, LOW);            // 制御デバイス選択(Enable)
  value = SPI.transfer(0x00) << 8;  // 上位ビット8bit読み出し後8bit左にシフト
  value |= SPI.transfer(0x00);      // 下位ビット8bit読み出し後上位ビットとOR
  digitalWrite(SS, HIGH);           // 制御デバイス選択(Disable)

  //熱電対のopen check(bit<2> = 1ならopen)
  if ((value & 0x0004) != 0){
    Serial.println("Open Error");
    
  //読み出した温度の表示 bit<14:3>が温度数値格納bit bit<15>=0(dummy bit)
  } else {
    //Serial.print((value >> 3), BIN); //bit<15:3>のみ2進表示
    //Serial.print(", ");
    //温度データを出力
    Serial.print((value >> 3) * 0.25); //bit<15:3>のみ表示、MAX6675仕様(分解能 0.25℃)
    //温度を取得
    temp = ((value >> 3) * 0.25);
    //Serial.println(" degC");
  } 


  //制御量の計算
  P = *************
  //I = *************
  //D = *************
 
  //操作量の計算
  mv = Kp * P;

  if(*************){
    on_time = 1000.0;
    off_time= 0;
  }
  else{
    on_time = *************
    off_time = 1000.0 - on_time;
  }


  digitalWrite(outputPin, HIGH);
  delay((int)on_time);
  digitalWrite(outputPin, LOW);
  delay((int)off_time);

  Serial.print(Kp);
  Serial.print(", ");
  Serial.print(mv);
  Serial.print(", ");
  Serial.print((int)on_time);
  Serial.print(", ");
  Serial.print((int)off_time);
  Serial.println("");
}
