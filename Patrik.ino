//включаем библиотеки
#include <Ultrasonic.h>
#include <Servo.h> 
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <EEPROM.h>


class Patrik{

  public:
  
  void init1(int l5=13, int l4=12, int l3=11, int l2=10, int l1=9, int neck=8 , int head=7, int r1=6, int r2=5, int r3=4, int r4=3, int r5=2,
            int led_pin=45, int pump_pin = 48, int all = 43, int volume = 30, int sensor = A0);

            
  void Move(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5, int del = 20);
  void Drink();
  void Say(int from, int to);
  void Scan(long period);
  void DetachHands();
  void DetachAll();
  void AttachAll();
  void Hello();
  void Pour(int del = 3000);
  void SelfPour(int del = 3000);
  void ResetBools();
  void Run(long time_b);
  void Wag();
  void Save();
  void Led(bool state);
  void Pump(bool state);
  void Debug(String str);
  void Nice(int del = 20);

  Patrik(int rx = 44,int tx =46 , int trig =30,int echo =31):mySerial(rx,tx),ultrasonic(trig,echo){}
  
 
  private:
  SoftwareSerial mySerial;
  Ultrasonic ultrasonic;

  int servo_pins[12];
  int servo_positions[12];
  Servo servo[12];
  int distance; 
  int min_sense_val = 800;
  int min_distance = 7;
  bool dist_bool = false;
  bool sense_bool = false;
  bool time_bool = false;
  int led;
  int pump;
   
  int sense_val;
  int sensor;
  bool debug = false;

};

void Patrik::Debug(String str){
  if (debug){
    Serial.print(str);
  }
}

void Patrik::Pump(bool state){
  if (state) {
    digitalWrite(pump, HIGH);
  }
  else{
    digitalWrite(pump, LOW);
  }
  
}

void Patrik::Save(){
  Serial.println("Save");
for (int i =0; i<=11; i++){
        Serial.print("servo_positions[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(servo_positions[i]);
    EEPROM.write(i, servo_positions[i]); 
  }
}




void Patrik::init1(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5,
int led_pin, int pump_pin, int all, int volume,int sensor ){
  
  Serial.begin(9600); //открываем последовательное соединение с компом
  mySerial.begin (9600);
  led = led_pin;
  pump = pump_pin;
  randomSeed(analogRead(A6));
  pinMode(led, OUTPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  pinMode(all, OUTPUT);
  digitalWrite(all, LOW);
  Serial.println(all);
  delay(1000);

  
  mp3_set_serial (mySerial);
  delay(1);   //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (volume);  //громкость плеера
  mp3_set_EQ (5);
  delay(200);
  Say (10,11);
//  Move(90,90,90,90,90,90, 90,90,90,90,90,90);




  
  if(EEPROM.read(0)>180){
  for (int i =0; i<=11; i++){
    EEPROM.write(i, 90); 
  }
  }

  
  for (int i =0; i<=11; i++){
    servo_positions[i] =  EEPROM.read(i);
  }

  servo_pins[0] = l5;
  servo_pins[1] = l4;
  servo_pins[2] = l3;
  servo_pins[3] = l2;
  servo_pins[4] = l1;
  servo_pins[5] = neck;
  servo_pins[6] = head;
  servo_pins[7] = r1;
  servo_pins[8] = r2;
  servo_pins[9] = r3;
  servo_pins[10] = r4;
  servo_pins[11] = r5;

  AttachAll();

  
   for (int i =0; i<=11; i++){
    servo[i].write(servo_positions[i]);
  }
  
  Hello();
}

void Patrik::AttachAll(){
  for(int i = 0; i <=11; i++){
  servo[i].attach(servo_pins[i]);  
  }
 }

void Patrik::DetachAll(){
  for(int i = 0; i <=11; i++){
  servo[i].detach();  
  }
 }

void Patrik::DetachHands(){
  servo[0].detach();
  servo[1].detach();
  servo[2].detach();
  servo[3].detach();
  servo[8].detach();
  servo[9].detach();
  servo[10].detach();
  servo[11].detach();
}

void Patrik::ResetBools(){
 sense_bool = false; 
 dist_bool = false;
 time_bool = false;
}

void Patrik::Scan(long period){
long current_time = millis();
Serial.println("start scan");

while(1){
  delay(100);
  DetachHands();
  distance = ultrasonic.distanceRead();
  sense_val = analogRead(sensor);
//  Serial.print(" distance: ");
//  Serial.println(distance);
//  Serial.print("sense_val ");
//  Serial.println(sense_val);

//  Serial.print(" millis: ");
//  Serial.println(millis());
//  Serial.print("current_time ");
//  Serial.println(current_time);
//  Serial.print("period ");
//  Serial.println(period);
  
  if ((millis() - current_time)> period){
    time_bool = true;
    AttachAll();
    Serial.println("time bool");
    break;
  }

  if (sense_val<min_sense_val) {
    AttachAll();
    Serial.println("sense bool");
    sense_bool = true;
    break;  
  }
  if (distance<min_distance){
    AttachAll();
    Serial.println("dist bool");
    dist_bool = true;
    break;
  }
    
  }
}

void Patrik::Led(bool state){
  if (state) 
  {
    digitalWrite(led, HIGH);
    }
  else
  {
    digitalWrite(led, LOW);
  }
  
}

void Patrik::Move(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5, int del){
  int new_pos[12];
  new_pos[0]=l5;
  new_pos[1]=l4;
  new_pos[2]=l3;
  new_pos[3]=l2;
  new_pos[4]=l1;
  new_pos[5]=neck;
  new_pos[6]=head;
  new_pos[7]=r1;
  new_pos[8]=r2;
  new_pos[9]=r3;
  new_pos[10]=r4;
  new_pos[11]=r5;

  int old_pos[12];
  for (int i = 0; i<=11; i++){
   old_pos[i]= servo[i].read();
//   Serial.print("old_pos[");
//        Serial.print(i);
//        Serial.print("] = ");
//   Serial.println(old_pos[i]);
  }
  while(1){
    for(int i = 0; i<=11; i++){
      
      if (new_pos[i]<old_pos[i]){
        old_pos[i]--;
        servo_positions[i]=old_pos[i];
//         Serial.print("old_pos[");
//        Serial.print(i);
//        Serial.print("] = ");
//        Serial.println(old_pos[i]);
      }
      if (new_pos[i]>old_pos[i]){
        old_pos[i]++;
        servo_positions[i]=old_pos[i];
//        Serial.print("old_pos[");
//        Serial.print(i);
//        Serial.print("] = ");
//        Serial.println(old_pos[i]);
      }
      servo[i].write(servo_positions[i]);
      
    }
    
    delay(del);
//    Serial.println("move...");
   if(new_pos[0] == old_pos[0] &&
      new_pos[1] == old_pos[1] &&
      new_pos[2] == old_pos[2] &&
      new_pos[3] == old_pos[3] &&
      new_pos[4] == old_pos[4] &&
      new_pos[5] == old_pos[5] &&
      new_pos[6] == old_pos[6] &&
      new_pos[7] == old_pos[7] &&
      new_pos[8] == old_pos[8] &&
      new_pos[9] == old_pos[9] &&
      new_pos[10] == old_pos[10] &&
      new_pos[11] == old_pos[11]){
        Serial.println("exit move");
        break; 
      }
  }
  
  
}


void Patrik::Run(long time_b){
  
  Scan(time_b);
  if(dist_bool){
     ResetBools();
     Pour();
  }

  if (sense_bool){
    ResetBools();
    Drink();
    Nice();
  }

  if (time_bool){
    ResetBools();
    SelfPour();
    Nice();
  }
}

void Patrik::Say(int from, int to){
  int rand_val = random(from, to);
  mp3_play (rand_val);  
}


void Patrik::Hello(){
 
  delay(3000);
  Say(1,2);
  Wag();
}

void Patrik::Wag(){
  //5vars
  // 6 lines
  Move(30-30,90,   60,60,120,70, 80, 125,120,120,60,90);
  
  Led(1);
  Move(30-30,90,   60,60,120-80,   70,    80,    125,120,120,60,90);
  Move(30-30,90-30,60,60,120-80,   70+30, 80-40, 125,120,120,60,90);
  Move(30-30,90,   60,60,120-80,   70,    80,    125,120,120,60,90);
  Say(2,3);
  Move(30-30,90-30,60,60,40,       70-30, 80-40, 125,120,120,60,90);

  
  Move(30-30,90,   60,60,120,      70,    80,    125,120,120,60,90);
  Led(0);
  Say(3,4);
  
}

void Patrik::Drink(){
  //3vars
  //5 lines
  Say(4,7);
  Move(30,90,60,60,120,70,    80,    125,   120,120,60,90);
  Move(30,90,60,60,120,70-35, 80-40, 125+55,120,120,60,90,      50);
  Move(30,90,60,60,120,70-35, 80-40, 125+55,120,120,60,90-50,   90);
  
  delay(3000);
  Move(30,90,60,60,120,70-35, 80-40, 125+55,120,120,60,90);
  Move(30,90,60,60,120,70,    80,    125,   120,120,60,90);
  
 
}

void Patrik::Pour(int del){
  //5 lines
  //2vars
  Say(8,9);
  Move(30,    90,60,60,120,   70, 80, 125,120,120,60,90);
  Move(30,    90,60,60,120-70,70, 80, 125,120,120,60,90);
  Move(30+130,90,60,60,120-70,70, 80, 125,120,120,60,90);
  Pump(1);
  delay (del);
  Pump(0);
  Move(30,    90,60,60,120-70,70, 80, 125,120,120,60,90);
  Move(30,    90,60,60,120,   70, 80, 125,120,120,60,90);
  
}

void Patrik::SelfPour(int del){
  //7 vars
  //5 lines
  Say(9,10); 
  Move(30,   90,   60,60,   120,   70, 80, 125,   120,120,   60,90);
  Move(30-30,90+20,60,60-20,120-80,70, 80, 125-40,120,120,   60,90-10);
  Move(130,  90,   60,60-20,120-80,70, 80, 125-40,120,120+20,60,90-10);
  Pump(1);
  delay (del);
  Pump(0);
  Move(30,   90,   60,60-20,120-80,70, 80, 125-40,120,120+20,60,90-10);
  Move(30,   90,   60,60,   120,   70, 80, 125,   120,120,   60,90);
  Drink();
}


void Patrik::Nice(int del){
  //2 vars
  //5 lines
  Say(7,8);
  Led(1);
  Move(30,90,60,60,120,70,    80,    125,120,120,60,90);
  Move(30,90,60,60,120,70+30, 80-30, 125,120,120,60,90);
  
  Move(30,90,60,60,120,70,    80,    125,120,120,60,90);
  Move(30,90,60,60,120,70-30, 80-30, 125,120,120,60,90);
  
  Move(30,90,60,60,120,70,    80,    125,120,120,60,90);
  Led(0);
}

//16 lines

















Patrik patrik;


void setup() {

  patrik.init1();
   

}

void loop() {
  
  // put your main code here, to run repeatedly:
  patrik.Run(60000);

}
