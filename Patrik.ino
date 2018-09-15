//включаем библиотеки
#include <Ultrasonic.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <EEPROM.h>


class Patrik {

  public:

    void init1(int l5 = 13, int l4 = 12, int l3 = 11, int l2 = 10, int l1 = 9, int neck = 8 , int head = 7, int r1 = 6, int r2 = 5, int r3 = 4, int r4 = 3, int r5 = 2,
               int led_pin = 45, int pump_pin = 48, int all = 43, int volume = 30, int sensor = A1);


    void Move(int new_pos[12], int del = 20);
    void Drink();
    void Say(int from, int to);
    void Scan(long period);
    void DetachHands();
    void DetachAll();
    void AttachAll();
    void Hello();
    void Pour(int del = 3000);
    void SelfPour(int del = 2500);
    void ResetBools();
    void Run(long time_b);
    void Wag();
    void Save();
    void Led(bool state);
    void Pump(bool state);
    void Debug(String str);
    void Nice(int del = 20);
    void SaveDrink();
    void SaveSelfPour();
    void SaveWag();
    void SavePour();
    void SaveNice();
    void Calib();
    void SetArms(  int lev, int n_p);
    void ReadMemory();
    void fillMem();
    bool Calib_proc(char com);
    void Calib_help();
    void CharServo(int &pos, char com, char neg, char positive);
    bool MemoryTools(char com, char next, char detachAll, char attachAll, char detachHands, char memory, int p[], int lev);
    bool calibComs(char com, int lev, int p[]);
    void ReadPosition(int pos[], int level);
    void ReadFullPosition(int* arr[12], int pos_num, int level);

    Patrik(int rx = 44, int tx = 46 , int trig = 30, int echo = 31): mySerial(rx, tx), ultrasonic(trig, echo) {}// (46 через резистор, на плеере rx)// (46 через резистор, на плеере rx)


  private:
    SoftwareSerial mySerial;
    Ultrasonic ultrasonic;

    int servo_pins[12];
    int servo_positions[12];
    int start_pos[12];
    int drink[3][12];
    int selfPour[3][12];
    int wag[4][12];
    int pour[3][12];
    int nice[3][12];

    Servo servo[12];
    int distance;
    int min_sense_val = 900;
    int min_distance = 5;
    bool dist_bool = false;
    bool sense_bool = false;
    bool time_bool = false;
    int led;
    int pump;
    int sen;

    int sense_val;
    int sensor;
    bool debug = true;



};

void Patrik::Debug(String str) {
  if (debug) {
    Serial.print(str);
  }
}

void Patrik::Pump(bool state) {
  digitalWrite(pump, state);
}




void Patrik::ReadFullPosition(int* arr[12], int pos_num, int level) {
  for (int i = 0; i < pos_num; i++) {
    ReadPosition(arr[i], level++);
  }
}

void Patrik::ReadPosition(int pos[], int level) {
  for (int i = 0; i < 12; i++) {
    pos[i] = EEPROM.read(i + 12 * level);
  }
}


void Patrik::ReadMemory() {
  Serial.println("Reading memory...");

  ReadPosition(servo_positions, 0);
  ReadPosition(servo_positions, 0);


  ReadPosition(drink[0], 1);
  ReadPosition(drink[1], 2);
  ReadPosition(drink[2], 3);

  ReadPosition(selfPour[0], 4);
  ReadPosition(selfPour[1], 5);
  ReadPosition(selfPour[2], 6);

  ReadPosition(wag[0], 7);
  ReadPosition(wag[1], 8);
  ReadPosition(wag[2], 9);
  ReadPosition(wag[3], 10);

  ReadPosition(pour[0], 11);
  ReadPosition(pour[1], 12);
  ReadPosition(pour[2], 13);


  ReadPosition(nice[0], 14);
  ReadPosition(nice[1], 15);
  ReadPosition(nice[2], 16);

  Serial.println("Reading memory done");
}


void Patrik::fillMem() {
  if (EEPROM.read(0) > 180) {
    for (int i = 0; i <= 205; i++) {
      EEPROM.write(i, 90);
    }
  }
}

void Patrik::init1(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5,
                   int led_pin, int pump_pin, int all, int volume, int sensor ) {

  Serial.begin(9600); //открываем последовательное соединение с компом
  Serial3.begin(9600);
  mySerial.begin (9600);
  led = led_pin;
  pump = pump_pin;
  sen = sensor;
  randomSeed(analogRead(A6));
  pinMode(led, OUTPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  delay(1000);


  mp3_set_serial (mySerial);
  delay(1);   //set softwareSerial for DFPlayer-mini mp3 module
  mp3_set_volume (volume);  //громкость плеера
  mp3_set_EQ (5);
  delay(200);

  fillMem();
  ReadMemory();

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

  for (int i = 0; i <= 11; i++) {
    servo[i].write(servo_positions[i]);
  }
  delay(2000);
  pinMode(all, OUTPUT);
  digitalWrite(all, LOW);
  Serial.println("end init");
}

void Patrik::AttachAll() {
  for (int i = 0; i <= 11; i++) {
    servo[i].attach(servo_pins[i]);
  }
}

void Patrik::DetachAll() {
  for (int i = 0; i <= 11; i++) {
    servo[i].detach();
  }
}

void Patrik::DetachHands() {
  servo[0].detach();
  servo[1].detach();
  servo[2].detach();
  servo[3].detach();
  servo[8].detach();
  servo[9].detach();
  servo[10].detach();
  servo[11].detach();
}

void Patrik::ResetBools() {
  sense_bool = false;
  dist_bool = false;
  time_bool = false;
}

void Patrik::Scan(long period) {
  delay(1000);
  long current_time = millis();
  Serial.println("start scan");
  distance = 100;
  while (1) {
    Calib();
    delay(100);
    DetachHands();
    distance = (ultrasonic.distanceRead() + ultrasonic.distanceRead() + ultrasonic.distanceRead() + ultrasonic.distanceRead()) / 4;
    sense_val = analogRead(sen);
    if (debug) {
      Serial.print(" distance: ");
      Serial.println(distance);
      Serial.print("sense_val ");
      Serial.println(sense_val);
      Serial.print(" millis: ");
      Serial.println(millis());
      Serial.print("current_time ");
      Serial.println(current_time);
      Serial.print("period ");
      Serial.println(period);
    }
    if ((millis() - current_time) > period) {
      time_bool = true;
      AttachAll();
      Serial.println("time bool");
      break;
    }

    if (sense_val < min_sense_val) {
      AttachAll();
      Serial.println("sense bool");
      sense_bool = true;
      break;
    }
    if (distance < min_distance && distance > 0 ) {
      AttachAll();
      Serial.println("dist bool");
      dist_bool = true;
      break;
    }

  }
}

void Patrik::Led(bool state) {
  digitalWrite(led, state);
}

void Patrik::Move(int new_pos[12], int del) {
  int old_pos[12];
  for (int i = 0; i <= 11; i++) {
    old_pos[i] = servo[i].read();
  }
  while (1) {
    for (int i = 0; i <= 11; i++) {

      if (new_pos[i] < old_pos[i]) {
        old_pos[i]--;
        servo_positions[i] = old_pos[i];
      }
      if (new_pos[i] > old_pos[i]) {
        old_pos[i]++;
        servo_positions[i] = old_pos[i];
      }
      servo[i].write(servo_positions[i]);
    }
    delay(del);
    if (new_pos[0] == old_pos[0] &&
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
        new_pos[11] == old_pos[11]) {
      break;
    }
  }
}


void Patrik::Run(long time_b) {
  Hello();
  while (1) {

    Scan(time_b);
    if (dist_bool) {
      ResetBools();
      Pour(3000);
    }

    if (sense_bool) {
      ResetBools();
      delay(3000);
      Drink();
      Nice();
    }

    if (time_bool) {
      ResetBools();
      SelfPour(2400);
      Nice();
    }
  }
}

void Patrik::Say(int from, int to) {
  int rand_val = random(from, to);
  mp3_play (rand_val);
}


void Patrik::Hello() {
  delay(3000);
  Say(1, 4);
  Wag();
}


void Patrik::Drink() {
  Say(8, 11);
  Move(start_pos);
  Move(drink[0],      50);
  Move(drink[1],      90);
  delay(3000);
  Move(drink[2], 50);
  Move(start_pos);
}

void Patrik::SelfPour(int del) {
  Say(14, 17);
  Move(start_pos);
  Move(selfPour[0]);
  Move(selfPour[1]);
  Pump(1);
  delay (del);
  Pump(0);
  delay (2000);
  Move(selfPour[2]);
  Move(start_pos);
  Drink();
}


void Patrik::Wag() {
  Move(start_pos);
  Led(1);
  Move(wag[0]);
  Move(wag[1]);
  Move(wag[2]);
  Say(4, 7);
  delay(1500);
  Move(wag[3]);
  Move(start_pos);
  Led(0);
  Say(7, 8);
}


void Patrik::Pour(int del) {
  Say(17, 20);
  Move(start_pos);
  Move(pour[0]);
  Move(pour[1]);
  Pump(1);
  delay (del);
  Pump(0);
  delay(1000);
  Move(pour[2]);
  Move(start_pos);
}


void Patrik::Nice(int del) {
  Say(11, 14);
  Led(1);
  Move(start_pos);
  Move(nice[0]);
  Move(nice[1]);
  Move(nice[2]);
  Move(start_pos);
  Led(0);
}


bool Patrik::Calib_proc(char com) {
  if (com == '1') {
    Serial.println("Drink calibration");
    Move(start_pos, 50);
    Move(drink[0],      50);
    SetArms(  1, 0);
    Move(drink[1],      50);
    SetArms( 2, 1);
    Move(drink[2], 50);
    SetArms(  3, 2);
    Move(start_pos, 50);
    Serial.println("Drink calibration DONE");
    ReadMemory();
    return true;
  }
  if (com == '2') {
    Serial.println("SelfPour calibration");
    Move(start_pos, 50);
    Move(selfPour[0],      50);
    SetArms(  4, 0);
    Move(selfPour[1], 50);
    SetArms(  5, 1);
    Move(selfPour[2], 50);
    SetArms(  6, 2);
    Move(start_pos, 50);
    Serial.println("SelfPour calibration DONE");
    ReadMemory();
    return true;
  }
  if (com == '3') {
    Serial.println("Wag calibration");
    Move(start_pos, 50);
    Move(wag[0], 50);
    SetArms(  7, 0);
    Move(wag[1], 50);
    SetArms(  8, 1);
    Move(wag[2], 50);
    SetArms(  9, 2);
    Move(wag[3], 50);
    SetArms(  10, 2);
    Move(start_pos, 50);
    Serial.println("Wag calibration DONE");
    ReadMemory();
    return true;
  }
  if (com == '4') {
    Serial.println("Pour calibration");
    Move(start_pos, 50);
    Move(pour[0],     50);
    SetArms(  11, 0);
    Move(pour[1],  50);
    SetArms(  12, 1);
    Move(pour[2], 50);
    SetArms(  13, 2);
    Move(start_pos, 50);
    Serial.println("Pour calibration DONE");
    ReadMemory();
    return true;
  }
  if (com == '5') {
    Serial.println("Nice calibration");
    Move(start_pos, 50);
    Move(nice[0] ,     50);
    SetArms( 14, 0);
    Move(nice[1] ,     50);
    SetArms(15, 1);
    Move(nice[2], 50);
    SetArms(16, 2);
    Move(start_pos, 50);
    Serial.println("Nice calibration DONE");
    ReadMemory();
    return true;
  }
  if (com == '6') {
    Serial.println("Start calibration");
    Move(start_pos, 50);
    int s_pos[1][12];
    for (int i = 0; i >= 11; i++) {
      s_pos[0][i] = start_pos[i];
    }
    SetArms(0, 0);
    Serial.println("Start calibration DONE");
    ReadMemory();
    return true;
  }
  return false;
}


void Patrik::Calib_help() {
  Serial.println("Calibration mode");
  Serial.println("Enter command:");
  Serial.println("1 - Drink calibration:");
  Serial.println("2 - SelfPour calibration:");
  Serial.println("3 - Wag calibration:");
  Serial.println("4 - Pour calibration:");
  Serial.println("5 - Nice calibration:");
  Serial.println("6 - Start calibration:");
}

void Patrik::Calib() {
  if (Serial3.available() > 0) {

    String command = Serial3.readString();
    String calib = "calibration\n";
    if (command == calib) {
      AttachAll();
      Calib_help();
      while (1) {
        if (Serial3.available() > 0) {
          char com  = Serial3.read();
          if (Calib_proc(com))break;
        }
      }
    }
  }

  if (Serial.available() > 0) {

    String command = Serial.readString();
    String calib = "calibration\n";
    if (command == calib) {
      AttachAll();
      Calib_help();
      while (1) {
        if (Serial3.available() > 0) {
          char com  = Serial3.read();
          if (Calib_proc(com))break;
        }
      }
    }
  }
}


void Patrik::CharServo(int &pos, char com, char neg, char positive) {
  if (com == neg) {
    pos--;
    if (pos < 0)pos = 0;
  }
  if (com == positive) {
    pos++;
    if (pos > 180)pos = 180;

  }

}


bool Patrik::MemoryTools(char com, char next, char detachAll, char attachAll, char detachHands, char memory, int p[], int lev) {
  if (com == next) {
    return true;
  }
  if (com == detachAll) {
    DetachAll();
  }
  if (com == detachHands) {
    DetachHands();
  }
  if (com == attachAll) {
    AttachAll();
  }
  if (com == memory) {
    for (int i = 0; i <= 11; i++) {
      EEPROM.write(i + 12 * lev, p[i]);
    }
    return true;
  }
  return false;
}



bool Patrik::calibComs(char com, int lev, int p[]) {
  CharServo(p[0], com, 'q', 'w');
  CharServo(p[1], com, 'e', 'r');
  CharServo(p[2], com, 't', 'y');
  CharServo(p[3], com, 'u', 'i');
  CharServo(p[4], com, 'o', 'p');
  CharServo(p[5], com, 'a', 's');
  CharServo(p[6], com, 'd', 'f');
  CharServo(p[7], com, 'g', 'h');
  CharServo(p[8], com, 'j', 'k');
  CharServo(p[9], com, 'z', 'x');
  CharServo(p[10], com, 'c', 'v');
  CharServo(p[11], com, 'b', 'n');
  if (MemoryTools(com, ',', '1', '2', '3', 'm', p, lev))return true;
  return false;
}


void Patrik::SetArms( int lev, int n_p) {
  int p[12];
  for (int i = 0; i <= 11; i++) {
    p[i] = EEPROM.read(i + 12 * lev);
  }
  while (1) {
    /////from bluetooth
    if (Serial3.available() > 0) {
      char com_dc  = Serial3.read();
      if (calibComs(com_dc, lev, p))break;
    }
    /////from usb
    if (Serial.available() > 0) {
      char com_dc  = Serial3.read();
      if (calibComs(com_dc, lev, p))break;
    }
    Move(p, 1);
  }
}




Patrik patrik;
void setup() {
  patrik.init1();
}

void loop() {
  patrik.Run(180000);
}
