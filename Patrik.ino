//включаем библиотеки
#include <Ultrasonic.h>
#include <Servo.h> 
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>


class Patrik{

  public:
  
  void init(int l5=13, int l4=12, int l3=11, int l2=10, int l1=9, int neck=8 , int head=7, int r1=6, int r2=5, int r3=4, int r4=3, int r5=2,
            int led=37, int pump = 48, int all= 40, int volume = 30,int sensor = A1);
            
  void Move(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5);
  void Drink();
  void Say(int from, int to);
  void Scan();
  void DetachHands();
  void DetachAll();
  void AttachAll();
  void Hello();
  void Pour();
  void SelfPour();
  void ResetBools();
  void Run();
  void Wag();
 
  private:
  SoftwareSerial mySerial;
  Test(int m): mySerial (44, 46){}
//  Ultrasonic ultrasonic(int tr = 30,  int ec = 31);//trig , echo
//  SoftwareSerial mySerial(int rx = 44, int tx =46);  // (46 через резистор, на плеере rx)
  int servo_pins[12];
  int servo_positions[12];
  Servo servo[12];
  int distance; 
  int min_sense_val = 800;
  int min_distance = 7;
  bool dist_bool = false;
  bool sense_bool = false;
  bool time_bool = false;


};











void Patrik::init(int l5, int l4, int l3, int l2, int l1, int neck=8 , int head=7, int r1=6, int r2=5, int r3=4, int r4=3, int r5=2,
            int led, int pump, int all, int volume,int sensor = A1){
  
  Serial.begin(9600); //открываем последовательное соединение с компом
  randomSeed(analogRead(A6));
  pinMode(led, OUTPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  pinMode(all, OUTPUT);
  digitalWrite(all, LOW);

  mySerial.begin (9600);
  mp3_set_serial (mySerial);//set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (volume);  //громкость плеера
  mp3_set_EQ (5);




  
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


  Hello();
}

void Patrik::AttachAll(){
  for(int i = 0; i <=11; i++{
  servo[i].attach(servo_pins[i]);  
  }
 }

void Patrik::DetachAll(){
  for(int i = 0; i <=11; i++{
  servo[i].attach(servo_pins[i]);  
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
long current_time = millis()

do{
  distance = ultrasonic.distanceRead();
  sense_val = analogRead(sensor);
  if ((millis() - current_time)> period){
    time_bool = true;
    break;
  }

  if (sense_val<min_sense_val) {
    sense_bool = true;
    break;  
  }
  if (distance<min_distance){
    dist_bool = true;
  }
    break;
  }
}


void Patrik::Move(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5){
  int new_pos[12];
  new_pos[0]=l5;
  new_pos[0]=l4;
  new_pos[0]=l3;
  new_pos[0]=l2;
  new_pos[0]=l1;
  new_pos[0]=neck;
  new_pos[0]=head;
  new_pos[0]=r1;
  new_pos[0]=r2;
  new_pos[0]=r3;
  new_pos[0]=r4;
  new_pos[0]=r5;

  int old_pos[12];
  for (int i = 0; i<=11; i++){
    servo[i].read();
  }
  do{
    for(int i = 0; i<=11; i++){
      
      if (new_pos[i]<old_pos[i]{
        servo[i]++;
      }
      if (new_pos[i]>old_pos[i]{
        servo[i]--;
      }
      
    }

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
        break; 
      }
  }
  
  
}


void Patrik::Run(){
  
  Scan();
  if(dist_bool){
     ResetBools();
     Pour();
  }

  if (sense_bool){
    ResetBools();
    Drink();
  }

  if (time_bool){
    SelfPour();
  }
}

void Patrik::Say(int from, int to){
  int rand_val = random(from, to);
  mp3_play (rand_val);  
}


void Patrik::Hello(){
  Say(1,3);
  Wag();
}

void Patrik::Wag(){
  
}

void Patrik::Drink(){
  
}

void Patrik::Pour(){
  
}

void Patrik::SelfPour(){
  
}


























Patrik patrik;


void setup() {
  // put your setup code here, to run once:
  patrik.init();

}

void loop() {
  // put your main code here, to run repeatedly:
  patrik.Run();
}