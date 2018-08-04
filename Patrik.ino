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


    void Move(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5, int del = 20);
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
    void SetArms( int ( *pose )[12], size_t n , int lev, int n_p);
    void ReadMemory();

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

    ///////////////////////////////////////////EEPROM MEMORY FROM _TO

    int start_s = 0;
    int start_e = 11;


    int drink_s_1 = 12;
    int drink_e_1 = 23;

    int drink_s_2 = 24;
    int drink_e_2 = 35;

    int drink_s_3 = 36;
    int drink_e_3 = 47;


    int selfPour_s_1 = 48;
    int selfPour_e_1 = 59;

    int selfPour_s_2 = 60;
    int selfPour_e_2 = 71;

    int selfPour_s_3 = 72;
    int selfPour_e_3 = 83;



    int wag_s_1 = 84;
    int wag_e_1 = 95;

    int wag_s_2 = 96;
    int wag_e_2 = 107;

    int wag_s_3 = 108;
    int wag_e_3 = 119;

    int wag_s_4 = 120;
    int wag_e_4 = 131;



    int pour_s_1 = 132;
    int pour_e_1 = 143;

    int pour_s_2 = 144;
    int pour_e_2 = 155;

    int pour_s_3 = 156;
    int pour_e_3 = 167;



    int nice_s_1 = 168;
    int nice_e_1 = 179;

    int nice_s_2 = 180;
    int nice_e_2 = 191;

    int nice_s_3 = 192;
    int nice_e_3 = 203;

};

void Patrik::Debug(String str) {
  if (debug) {
    Serial.print(str);
  }
}

void Patrik::Pump(bool state) {
  if (state) {
    digitalWrite(pump, HIGH);
  }
  else {
    digitalWrite(pump, LOW);
  }

}

void Patrik::ReadMemory(){
  Serial.println("Reading memory...");
  for (int i = 0; i <= 11; i++) {
    servo_positions[i] =  EEPROM.read(i);
    start_pos[i] = EEPROM.read(i);
  }



///READ DRINK POS
  for (int i = drink_s_1; i <= drink_e_1; i++) {
   drink[0][i-12]= EEPROM.read(i);
  }

  for (int i = drink_s_2; i <= drink_e_2; i++) {
    drink[1][i-12*2]= EEPROM.read(i);
  }


  for (int i = drink_s_3; i <= drink_e_3; i++) {
    drink[2][i-12*3]= EEPROM.read(i);
  }

/////
  for (int i = selfPour_s_1; i <= selfPour_e_1; i++) {
    selfPour[0][i-12*4]= EEPROM.read(i);
  }
  for (int i = selfPour_s_2; i <= selfPour_e_2; i++) {
    selfPour[1][i-12*5]= EEPROM.read(i);
  }

  for (int i = selfPour_s_3; i <= selfPour_e_3; i++) {
    selfPour[2][i-12*6]= EEPROM.read(i);
  }





  
  for (int i = wag_s_1; i <= wag_e_1; i++) {
    wag[0][i-12*7]= EEPROM.read(i);
  }
  for (int i = wag_s_2; i <= wag_e_2; i++) {
    wag[1][i-12*8]= EEPROM.read(i);
    
  }

  for (int i = wag_s_3; i <= wag_e_3; i++) {
    wag[2][i-12*9]= EEPROM.read(i);
    delay(2);
    
  }
  for (int i = wag_s_4; i <= wag_e_4; i++) {
    wag[3][i-12*10]= EEPROM.read(i);
    delay(2);

    
  }

Serial.println("end wag ");
////

 for (int i = pour_s_1; i <= pour_e_1; i++) {
    pour[0][i-12*11] = EEPROM.read(i);
  }

  for (int i = pour_s_2; i <= pour_e_2; i++) {
    pour[1][i-12*12] = EEPROM.read(i);
  }


  for (int i = pour_s_3; i <= pour_e_3; i++) {
    pour[2][i-12*13] = EEPROM.read(i);
  }

//////



 for (int i = nice_s_1; i <= nice_e_1; i++) {
   nice[0][i-12*14] = EEPROM.read(i);
  }

  for (int i = nice_s_2; i <= nice_e_2; i++) {
    nice[1][i-12*15] = EEPROM.read(i);
  }


  for (int i = nice_s_3; i <= nice_e_3; i++) {
    nice[2][i-12*16] = EEPROM.read(i);
  }
  Serial.println("Reading memory done");
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
  
  Serial.println(all);
  delay(1000);


  mp3_set_serial (mySerial);
  delay(1);   //set softwareSerial for DFPlayer-mini mp3 module
  mp3_set_volume (volume);  //громкость плеера
  mp3_set_EQ (5);
  delay(200);
//  Say (10, 11);






  if (EEPROM.read(0) > 180) {
    for (int i = 0; i <= 205; i++) {
      EEPROM.write(i, 90);
    }
    
  }

  


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
    distance = (ultrasonic.distanceRead()+ultrasonic.distanceRead()+ultrasonic.distanceRead()+ultrasonic.distanceRead())/4;
    sense_val = analogRead(sen);
    if(debug){
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
  if (state)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }

}

void Patrik::Move(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5, int del) {
  int new_pos[12];
  new_pos[0] = l5;
  new_pos[1] = l4;
  new_pos[2] = l3;
  new_pos[3] = l2;
  new_pos[4] = l1;
  new_pos[5] = neck;
  new_pos[6] = head;
  new_pos[7] = r1;
  new_pos[8] = r2;
  new_pos[9] = r3;
  new_pos[10] = r4;
  new_pos[11] = r5;

  int old_pos[12];
  for (int i = 0; i <= 11; i++) {
    old_pos[i] = servo[i].read();
    //        Serial.print("old_pos[");
    //        Serial.print(i);
    //        Serial.print("] = ");
    //        Serial.println(old_pos[i]);
  }
  while (1) {
    for (int i = 0; i <= 11; i++) {

      if (new_pos[i] < old_pos[i]) {
        old_pos[i]--;
        servo_positions[i] = old_pos[i];
        //        Serial.print("old_pos[");
        //        Serial.print(i);
        //        Serial.print("] = ");
        //        Serial.println(old_pos[i]);
      }
      if (new_pos[i] > old_pos[i]) {
        old_pos[i]++;
        servo_positions[i] = old_pos[i];
        //        Serial.print("old_pos[");
        //        Serial.print(i);
        //        Serial.print("] = ");
        //        Serial.println(old_pos[i]);
      }
      servo[i].write(servo_positions[i]);

    }

    delay(del);
    //    Serial.println("move...");
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
//      Serial.println("exit move");
      break;
    }
  }


}


void Patrik::Run(long time_b) {
  Hello();
  while(1){

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
  ///privet
  Say(1, 4);
  Wag();
}


void Patrik::Drink() {
  //3vars
  //5 lines

  Say(8, 11);

  Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11]);
  
  Move(drink[0][0], drink[0][1], drink[0][2], drink[0][3], drink[0][4], drink[0][5], drink[0][6], drink[0][7], drink[0][8], drink[0][9], drink[0][10], drink[0][11],      50);
  Move(drink[1][0], drink[1][1], drink[1][2], drink[1][3], drink[1][4], drink[1][5], drink[1][6], drink[1][7], drink[1][8], drink[1][9], drink[1][10], drink[1][11],      90);
  delay(3000);
  Move(drink[2][0], drink[2][1], drink[2][2], drink[2][3], drink[2][4], drink[2][5], drink[2][6], drink[2][7], drink[2][8], drink[2][9], drink[2][10], drink[2][11], 50);
  
  Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11]);


}

void Patrik::SelfPour(int del) {
  //7 vars
  //5 lines
  Say(14, 17);
  Move(start_pos[0],        start_pos[1],      start_pos[2], start_pos[3],      start_pos[4],      start_pos[5], start_pos[6], start_pos[7],      start_pos[8], start_pos[9],      start_pos[10], start_pos[11]);
  
  Move(selfPour[0][0], selfPour[0][1], selfPour[0][2], selfPour[0][3], selfPour[0][4], selfPour[0][5], selfPour[0][6], selfPour[0][7], selfPour[0][8], selfPour[0][9], selfPour[0][10], selfPour[0][11]);
  Move(selfPour[1][0], selfPour[1][1], selfPour[1][2], selfPour[1][3], selfPour[1][4], selfPour[1][5], selfPour[1][6], selfPour[1][7], selfPour[1][8], selfPour[1][9], selfPour[1][10], selfPour[1][11]);
  Pump(1);
  delay (del);
  Pump(0);
  delay (2000);
  Move(selfPour[2][0], selfPour[2][1], selfPour[2][2], selfPour[2][3], selfPour[2][4], selfPour[2][5], selfPour[2][6], selfPour[2][7], selfPour[2][8], selfPour[2][9], selfPour[2][10], selfPour[2][11]);

  Move(start_pos[0],        start_pos[1],      start_pos[2], start_pos[3],      start_pos[4],      start_pos[5], start_pos[6], start_pos[7],      start_pos[8], start_pos[9],      start_pos[10], start_pos[11]);
  Drink();
}


void Patrik::Wag() {
  //5vars
  // 6 lines
  Move(start_pos[0] - 30, start_pos[1],   start_pos[2], start_pos[3], start_pos[4],      start_pos[5],    start_pos[6],    start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);

  Led(1);
  Move(wag[0][0], wag[0][1], wag[0][2], wag[0][3], wag[0][4], wag[0][5], wag[0][6], wag[0][7], wag[0][8], wag[0][9], wag[0][10], wag[0][11]);
  Move(wag[1][0], wag[1][1], wag[1][2], wag[1][3], wag[1][4], wag[1][5], wag[1][6], wag[1][7], wag[1][8], wag[1][9], wag[1][10], wag[1][11]);
  Move(wag[2][0], wag[2][1], wag[2][2], wag[2][3], wag[2][4], wag[2][5], wag[2][6], wag[2][7], wag[2][8], wag[2][9], wag[2][10], wag[2][11]);
  Say(4, 7);
  delay(1500);
  Move(wag[3][0], wag[3][1], wag[3][2], wag[3][3], wag[3][4], wag[3][5], wag[3][6], wag[3][7], wag[3][8], wag[3][9], wag[3][10], wag[3][11]);



  Move(start_pos[0] - 30, start_pos[1],      start_pos[2], start_pos[3], start_pos[4],        start_pos[5],      start_pos[6],      start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);
  Led(0);
  Say(7, 8);

}


void Patrik::Pour(int del) {
  //5 lines
  //2vars
  Say(17, 20);
  Move(start_pos[0],       start_pos[1], start_pos[2], start_pos[3], start_pos[4],      start_pos[5], start_pos[6], start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);
  Move(pour[0][0], pour[0][1], pour[0][2], pour[0][3], pour[0][4], pour[0][5], pour[0][6], pour[0][7], pour[0][8], pour[0][9], pour[0][10], pour[0][11]);
  Move(pour[1][0], pour[1][1], pour[1][2], pour[1][3], pour[1][4], pour[1][5], pour[1][6], pour[1][7], pour[1][8], pour[1][9], pour[1][10], pour[1][11]);
  Pump(1);
  delay (del);
  Pump(0);
  delay(1000);
  Move(pour[2][0], pour[2][1], pour[2][2], pour[2][3], pour[2][4], pour[2][5], pour[2][6], pour[2][7], pour[2][8], pour[2][9], pour[2][10], pour[2][11]);

  Move(start_pos[0],       start_pos[1], start_pos[2], start_pos[3], start_pos[4],      start_pos[5], start_pos[6], start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);


}




void Patrik::Nice(int del) {
  //2 vars
  //5 lines
  Say(11, 14);
  Led(1);
  Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);
  
  Move(nice[0][0], nice[0][1], nice[0][2], nice[0][3], nice[0][4], nice[0][5], nice[0][6], nice[0][7], nice[0][8], nice[0][9], nice[0][10], nice[0][11]);
  Move(nice[1][0], nice[1][1], nice[1][2], nice[1][3], nice[1][4], nice[1][5], nice[1][6], nice[1][7], nice[1][8], nice[1][9], nice[1][10], nice[1][11]);
  Move(nice[2][0], nice[2][1], nice[2][2], nice[2][3], nice[2][4], nice[2][5], nice[2][6], nice[2][7], nice[2][8], nice[2][9], nice[2][10], nice[2][11]);
  
  Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);
  Led(0);
}

//16 lines

void Patrik::Save() {
  if (debug) {
    Serial.println("Save");
  }
  for (int i = 0; i <= 11; i++) {
    if (debug) {
      Serial.print("servo_positions[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.println(servo_positions[i]);
    }
    EEPROM.write(i, servo_positions[i]);
  }
}



void Patrik::SaveDrink() {
  if (debug) {
    Serial.println("Save");
  }
  for (int i = drink_s_1; i <= drink_e_1; i++) {
    EEPROM.write(i, drink[0][i-12]);
  }

  for (int i = drink_s_2; i <= drink_e_2; i++) {
    EEPROM.write(i, drink[1][i-12*2]);
  }


  for (int i = drink_s_3; i <= drink_e_3; i++) {
    EEPROM.write(i, drink[2][i-12*3]);
  }

}



void Patrik::SaveSelfPour() {
  if (debug) {
    Serial.println("Save");
  }
  for (int i = selfPour_s_1; i <= selfPour_e_1; i++) {
    EEPROM.write(i, selfPour[0][i-12*4]);
  }

  for (int i = selfPour_s_2; i <= selfPour_e_2; i++) {
    EEPROM.write(i, selfPour[1][i-12*5]);
  }


  for (int i = selfPour_s_3; i <= selfPour_e_3; i++) {
    EEPROM.write(i, selfPour[2][i-12*6]);
  }



}




void Patrik::SaveWag() {
  for (int i = wag_s_1; i <= wag_e_1; i++) {
    EEPROM.write(i, wag[0][i-12*7]);
  }

  for (int i = wag_s_2; i <= wag_e_2; i++) {
    EEPROM.write(i, wag[1][i-12*8]);
  }


  for (int i = wag_s_3; i <= wag_e_3; i++) {
    EEPROM.write(i, wag[2][i-12*9]);
  }

  for (int i = wag_s_4; i <= wag_e_4; i++) {
    EEPROM.write(i, wag[3][i-12*10]);
  }

}



void Patrik::SavePour() {
  if (debug) {
    Serial.println("Save");
  }
  for (int i = pour_s_1; i <= pour_e_1; i++) {
    EEPROM.write(i, pour[0][i-12*11]);
  }

  for (int i = pour_s_2; i <= pour_e_2; i++) {
    EEPROM.write(i, pour[1][i-12*12]);
  }


  for (int i = pour_s_3; i <= pour_e_3; i++) {
    EEPROM.write(i, pour[2][i-12*13]);
  }
}



void Patrik::SaveNice() {
  if (debug) {
    Serial.println("Save");
  }
  for (int i = nice_s_1; i <= nice_e_1; i++) {
    EEPROM.write(i, nice[0][i-12*14]);
  }

  for (int i = nice_s_2; i <= nice_e_2; i++) {
    EEPROM.write(i, nice[1][i-12*15]);
  }


  for (int i = nice_s_3; i <= nice_e_3; i++) {
    EEPROM.write(i, nice[2][i-12*16]);
  }
}

void Patrik::Calib(){
   if (Serial3.available()>0){
    
    String command = Serial3.readString();
    String calib = "calibration\n";       
    if (command == calib){
      AttachAll();
    Serial.println("Calibration mode");
    Serial.println("Enter command:");
    Serial.println("1 - Drink calibration:");
    Serial.println("2 - SelfPour calibration:");
    Serial.println("3 - Wag calibration:");
    Serial.println("4 - Pour calibration:");
    Serial.println("5 - Nice calibration:");
    Serial.println("6 - Start calibration:");
    while(1){
      if (Serial3.available()>0){
//        String com  = Serial.readString();
        char com  = Serial3.read();
        if (com == '1'){
          Serial.println("Drink calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(drink[0][0], drink[0][1], drink[0][2], drink[0][3], drink[0][4], drink[0][5], drink[0][6], drink[0][7], drink[0][8], drink[0][9], drink[0][10], drink[0][11],      50);
         
          

            SetArms(drink,3,1,0);
            Move(drink[1][0], drink[1][1], drink[1][2], drink[1][3], drink[1][4], drink[1][5], drink[1][6], drink[1][7], drink[1][8], drink[1][9], drink[1][10], drink[1][11],      50);
            SetArms(drink,3,2,1);
            Move(drink[2][0], drink[2][1], drink[2][2], drink[2][3], drink[2][4], drink[2][5], drink[2][6], drink[2][7], drink[2][8], drink[2][9], drink[2][10], drink[2][11],50);
            SetArms(drink,3,3,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("Drink calibration DONE");
            ReadMemory();
            break;
            
          
        }
         if (com == '2'){
          Serial.println("SelfPour calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(selfPour[0][0], selfPour[0][1], selfPour[0][2], selfPour[0][3], selfPour[0][4], selfPour[0][5], selfPour[0][6], selfPour[0][7], selfPour[0][8], selfPour[0][9], selfPour[0][10], selfPour[0][11],      50);
          
          

            SetArms(selfPour,3,4,0);
            Move(selfPour[1][0], selfPour[1][1], selfPour[1][2], selfPour[1][3], selfPour[1][4], selfPour[1][5], selfPour[1][6], selfPour[1][7], selfPour[1][8], selfPour[1][9], selfPour[1][10], selfPour[1][11],      50);
            SetArms(selfPour,3,5,1);
            Move(selfPour[2][0], selfPour[2][1], selfPour[2][2], selfPour[2][3], selfPour[2][4], selfPour[2][5], selfPour[2][6], selfPour[2][7], selfPour[2][8], selfPour[2][9], selfPour[2][10], selfPour[2][11],50);
            SetArms(selfPour,3,6,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("SelfPour calibration DONE");
            ReadMemory();
            break;

        
      }

      if (com == '3'){
          Serial.println("Wag calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(wag[0][0], wag[0][1], wag[0][2], wag[0][3], wag[0][4], wag[0][5], wag[0][6], wag[0][7], wag[0][8], wag[0][9], wag[0][10], wag[0][11],      50);
          
          

            SetArms(wag,4,7,0);
            Move(wag[1][0], wag[1][1], wag[1][2], wag[1][3], wag[1][4], wag[1][5], wag[1][6], wag[1][7], wag[1][8], wag[1][9], wag[1][10], wag[1][11],      50);
            SetArms(wag,4,8,1);
            Move(wag[2][0], wag[2][1], wag[2][2], wag[2][3], wag[2][4], wag[2][5], wag[2][6], wag[2][7], wag[2][8], wag[2][9], wag[2][10], wag[2][11],50);
            SetArms(wag,4,9,2);
            Move(wag[3][0], wag[3][1], wag[3][2], wag[3][3], wag[3][4], wag[3][5], wag[3][6], wag[3][7], wag[3][8], wag[3][9], wag[3][10], wag[3][11],50);
            SetArms(wag,4,10,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("Wag calibration DONE");
            ReadMemory();
            break;

        
      }

      if (com == '4'){
          Serial.println("Pour calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(pour[0][0], pour[0][1], pour[0][2], pour[0][3], pour[0][4], pour[0][5], pour[0][6], pour[0][7], pour[0][8], pour[0][9], pour[0][10], pour[0][11],      50);
          
          

            SetArms(pour,3,11,0);
            Move(pour[1][0], pour[1][1], pour[1][2], pour[1][3], pour[1][4], pour[1][5], pour[1][6], pour[1][7], pour[1][8], pour[1][9], pour[1][10], pour[1][11],      50);
            SetArms(pour,3,12,1);
            Move(pour[2][0], pour[2][1], pour[2][2], pour[2][3], pour[2][4], pour[2][5], pour[2][6], pour[2][7], pour[2][8], pour[2][9], pour[2][10], pour[2][11],50);
            SetArms(pour,3,13,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("Pour calibration DONE");
            ReadMemory();
            break;

        
      }


      if (com == '5'){
          Serial.println("Nice calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(nice[0][0], nice[0][1], nice[0][2], nice[0][3], nice[0][4], nice[0][5], nice[0][6], nice[0][7], nice[0][8], nice[0][9], nice[0][10], nice[0][11],      50);
          
          

            SetArms(nice,3,14,0);
            Move(nice[1][0], nice[1][1], nice[1][2], nice[1][3], nice[1][4], nice[1][5], nice[1][6], nice[1][7], nice[1][8], nice[1][9], nice[1][10], nice[1][11],      50);
            SetArms(nice,3,15,1);
            Move(nice[2][0], nice[2][1], nice[2][2], nice[2][3], nice[2][4], nice[2][5], nice[2][6], nice[2][7], nice[2][8], nice[2][9], nice[2][10], nice[2][11],50);
            SetArms(nice,3,16,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("Nice calibration DONE");
            ReadMemory();
            break;

        
      }



      if (com == '6'){
          Serial.println("Start calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          int s_pos[1][12];
          for(int i = 0; i>=11; i++){
            s_pos[0][i] = start_pos[i];
          }
        
          

            SetArms(s_pos,1,0,0);
            
            Serial.println("Start calibration DONE");
            ReadMemory();
            break;

        
      }
      
    }
    
  }
  }
}





if (Serial.available()>0){
    
    String command = Serial.readString();
    String calib = "calibration\n";       
    if (command == calib){
      AttachAll();
    Serial.println("Calibration mode");
    Serial.println("Enter command:");
    Serial.println("1 - Drink calibration:");
    Serial.println("2 - SelfPour calibration:");
    Serial.println("3 - Wag calibration:");
    Serial.println("4 - Pour calibration:");
    Serial.println("5 - Nice calibration:");
    Serial.println("6 - Start calibration:");
    while(1){
      if (Serial.available()>0){
//        String com  = Serial.readString();
        char com  = Serial.read();
        if (com == '1'){
          Serial.println("Drink calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(drink[0][0], drink[0][1], drink[0][2], drink[0][3], drink[0][4], drink[0][5], drink[0][6], drink[0][7], drink[0][8], drink[0][9], drink[0][10], drink[0][11],      50);
         
          

            SetArms(drink,3,1,0);
            Move(drink[1][0], drink[1][1], drink[1][2], drink[1][3], drink[1][4], drink[1][5], drink[1][6], drink[1][7], drink[1][8], drink[1][9], drink[1][10], drink[1][11],      50);
            SetArms(drink,3,2,1);
            Move(drink[2][0], drink[2][1], drink[2][2], drink[2][3], drink[2][4], drink[2][5], drink[2][6], drink[2][7], drink[2][8], drink[2][9], drink[2][10], drink[2][11],50);
            SetArms(drink,3,3,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("Drink calibration DONE");
            ReadMemory();
            break;
            
          
        }
         if (com == '2'){
          Serial.println("SelfPour calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(selfPour[0][0], selfPour[0][1], selfPour[0][2], selfPour[0][3], selfPour[0][4], selfPour[0][5], selfPour[0][6], selfPour[0][7], selfPour[0][8], selfPour[0][9], selfPour[0][10], selfPour[0][11],      50);
          
          

            SetArms(selfPour,3,4,0);
            Move(selfPour[1][0], selfPour[1][1], selfPour[1][2], selfPour[1][3], selfPour[1][4], selfPour[1][5], selfPour[1][6], selfPour[1][7], selfPour[1][8], selfPour[1][9], selfPour[1][10], selfPour[1][11],      50);
            SetArms(selfPour,3,5,1);
            Move(selfPour[2][0], selfPour[2][1], selfPour[2][2], selfPour[2][3], selfPour[2][4], selfPour[2][5], selfPour[2][6], selfPour[2][7], selfPour[2][8], selfPour[2][9], selfPour[2][10], selfPour[2][11],50);
            SetArms(selfPour,3,6,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("SelfPour calibration DONE");
            ReadMemory();
            break;

        
      }

      if (com == '3'){
          Serial.println("Wag calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(wag[0][0], wag[0][1], wag[0][2], wag[0][3], wag[0][4], wag[0][5], wag[0][6], wag[0][7], wag[0][8], wag[0][9], wag[0][10], wag[0][11],      50);
          
          

            SetArms(wag,4,7,0);
            Move(wag[1][0], wag[1][1], wag[1][2], wag[1][3], wag[1][4], wag[1][5], wag[1][6], wag[1][7], wag[1][8], wag[1][9], wag[1][10], wag[1][11],      50);
            SetArms(wag,4,8,1);
            Move(wag[2][0], wag[2][1], wag[2][2], wag[2][3], wag[2][4], wag[2][5], wag[2][6], wag[2][7], wag[2][8], wag[2][9], wag[2][10], wag[2][11],50);
            SetArms(wag,4,9,2);
            Move(wag[3][0], wag[3][1], wag[3][2], wag[3][3], wag[3][4], wag[3][5], wag[3][6], wag[3][7], wag[3][8], wag[3][9], wag[3][10], wag[3][11],50);
            SetArms(wag,4,10,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("Wag calibration DONE");
            ReadMemory();
            break;

        
      }

      if (com == '4'){
          Serial.println("Pour calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(pour[0][0], pour[0][1], pour[0][2], pour[0][3], pour[0][4], pour[0][5], pour[0][6], pour[0][7], pour[0][8], pour[0][9], pour[0][10], pour[0][11],      50);
          
          

            SetArms(pour,3,11,0);
            Move(pour[1][0], pour[1][1], pour[1][2], pour[1][3], pour[1][4], pour[1][5], pour[1][6], pour[1][7], pour[1][8], pour[1][9], pour[1][10], pour[1][11],      50);
            SetArms(pour,3,12,1);
            Move(pour[2][0], pour[2][1], pour[2][2], pour[2][3], pour[2][4], pour[2][5], pour[2][6], pour[2][7], pour[2][8], pour[2][9], pour[2][10], pour[2][11],50);
            SetArms(pour,3,13,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("Pour calibration DONE");
            ReadMemory();
            break;

        
      }


      if (com == '5'){
          Serial.println("Nice calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          Move(nice[0][0], nice[0][1], nice[0][2], nice[0][3], nice[0][4], nice[0][5], nice[0][6], nice[0][7], nice[0][8], nice[0][9], nice[0][10], nice[0][11],      50);
          
          

            SetArms(nice,3,14,0);
            Move(nice[1][0], nice[1][1], nice[1][2], nice[1][3], nice[1][4], nice[1][5], nice[1][6], nice[1][7], nice[1][8], nice[1][9], nice[1][10], nice[1][11],      50);
            SetArms(nice,3,15,1);
            Move(nice[2][0], nice[2][1], nice[2][2], nice[2][3], nice[2][4], nice[2][5], nice[2][6], nice[2][7], nice[2][8], nice[2][9], nice[2][10], nice[2][11],50);
            SetArms(nice,3,16,2);
            Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
            Serial.println("Nice calibration DONE");
            ReadMemory();
            break;

        
      }



      if (com == '6'){
          Serial.println("Start calibration");
          Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11], 50);
          int s_pos[1][12];
          for(int i = 0; i>=11; i++){
            s_pos[0][i] = start_pos[i];
          }
        
          

            SetArms(s_pos,1,0,0);
            
            Serial.println("Start calibration DONE");
            ReadMemory();
            break;

        
      }
      
    }
    
  }
  }
}
}






void Patrik::SetArms( int ( *pose )[12], size_t n , int lev, int n_p){
 int p[12];

 

 for(int i = 0; i<=11; i++){
  p[i] = EEPROM.read(i+12*lev);
 
 }

  while(1){

    /////from bluetooth
  if (Serial3.available()>0){
    
//    Serial.println("l_HAND-qw, l_ARM-er, l_SHOLDER-1-ty, l_SHOLDER-2-ui, l_ROLL-op,  1-detach all, 2 - attach all, 3 -detach hands ");
//    Serial.println("NECK-as, HEAD-df");
//    Serial.println("r_ROLL-gh, rSHOLDER-2-jk, r_SHOLDER-1-zx, r_ARM-cv, r_HAND-bn, save-m, next-,");

               
   for(int i = 0; i<=11; i++){
 
//  Serial.print(p[i]);
//  Serial.print(" ");
 }

              char com_dc  = Serial3.read();
//              Serial.println(com_dc);
              if (com_dc == 'q'){
                p[0]--;
                if(p[0]<0)p[0]=0;
              }
              if (com_dc == 'w'){
               p[0]++;
               if(p[0]>180)p[0]=180;

              }

              if (com_dc == 'e'){
                p[1]--;
                if(p[1]<0)p[1]=0;
              }
              if (com_dc == 'r'){
                p[1]++;
                if(p[1]>180)p[1]=180;
              }


              if (com_dc == 't'){
               p[2]--;
               if(p[2]<0)p[2]=0;
              }
              if (com_dc == 'y'){
               p[2]++;
               if(p[2]>180)p[2]=180;
              }

              if (com_dc == 'u'){
                p[3]--;
                if(p[3]<0)p[3]=0;
              }
              if (com_dc == 'i'){
                p[3]++;
                if(p[3]>180)p[3]=180;
              }


              if (com_dc == 'o'){
                p[4]--;
                if(p[4]<0)p[4]=0;
              }
              if (com_dc == 'p'){
                p[4]++;
                if(p[4]>180)p[4]=180;
              }

              if (com_dc == 'a'){
                p[5]--;
                if(p[5]<0)p[5]=0;
              }
              if (com_dc == 's'){
                p[5]++;
                if(p[5]>180)p[5]=180;
              }

              if (com_dc == 'd'){
                p[6]--;
                if(p[6]<0)p[6]=0;
              }
              if (com_dc == 'f'){
                p[6]++;
                if(p[6]>180)p[6]=180;
              }


              if (com_dc == 'g'){
                p[7]--;
                if(p[7]<0)p[7]=0;
              }
              if (com_dc == 'h'){
                p[7]++;
                if(p[7]>180)p[7]=180;
              }

              if (com_dc == 'j'){
                p[8]--;
                if(p[8]<0)p[8]=0;
              }
              if (com_dc == 'k'){
                p[8]++;
                if(p[8]>180)p[8]=180;
              }

              if (com_dc == 'z'){
                p[9]--;
                if(p[9]<0)p[9]=0;
              }
              if (com_dc == 'x'){
                p[9]++;
                if(p[9]>180)p[9]=180;
              }

              if (com_dc == 'c'){
                p[10]--;
                if(p[10]<0)p[10]=0;
              }
              if (com_dc == 'v'){
                p[10]++;
                if(p[10]>180)p[10]=180;
              }

              if (com_dc == 'b'){
                p[11]--;
                if(p[11]<0)p[11]=0;
              }
              if (com_dc == 'n'){
                p[11]++;
                if(p[11]>180)p[11]=180;
              }
              if (com_dc == ','){
                break;
              }
              if (com_dc == '1'){
                Serial.println("detached all");
                DetachAll();
              }

              if (com_dc == '3'){
                DetachHands();
                 Serial.println("detached hands");
              }
              if (com_dc == '2'){
                 Serial.println("attach all");
                AttachAll();
              }

              
              if(com_dc == 'm'){
                for (int i = 0; i<=11; i++){
                  Serial.println("Saving position");
                EEPROM.write(i+12*lev, p[i]);
                Serial.println(p[i]);
                }
                Serial.println("new positions");
                for (int i = 0; i<=11; i++){
                  Serial.println(EEPROM.read(i+12*lev));
                }
                Serial.println("addres");
                for (int i = 0; i<=11; i++){
                  Serial.println((i+12*5));
                }
                
                break;
                }
              }





///////////from usb

              if (Serial.available()>0){
    
    Serial.println("l_HAND-qw, l_ARM-er, l_SHOLDER-1-ty, l_SHOLDER-2-ui, l_ROLL-op,  1-detach all, 2 - attach all, 3 -detach hands ");
    Serial.println("NECK-as, HEAD-df");
    Serial.println("r_ROLL-gh, rSHOLDER-2-jk, r_SHOLDER-1-zx, r_ARM-cv, r_HAND-bn, save-m, next-,");

               
   for(int i = 0; i<=11; i++){
 
  Serial.print(p[i]);
  Serial.print(" ");
 }

              char com_dc  = Serial.read();
              Serial.println(com_dc);
              if (com_dc == 'q'){
                p[0]--;
                if(p[0]<0)p[0]=0;
              }
              if (com_dc == 'w'){
               p[0]++;
               if(p[0]>180)p[0]=180;

              }

              if (com_dc == 'e'){
                p[1]--;
                if(p[1]<0)p[1]=0;
              }
              if (com_dc == 'r'){
                p[1]++;
                if(p[1]>180)p[1]=180;
              }


              if (com_dc == 't'){
               p[2]--;
               if(p[2]<0)p[2]=0;
              }
              if (com_dc == 'y'){
               p[2]++;
               if(p[2]>180)p[2]=180;
              }

              if (com_dc == 'u'){
                p[3]--;
                if(p[3]<0)p[3]=0;
              }
              if (com_dc == 'i'){
                p[3]++;
                if(p[3]>180)p[3]=180;
              }


              if (com_dc == 'o'){
                p[4]--;
                if(p[4]<0)p[4]=0;
              }
              if (com_dc == 'p'){
                p[4]++;
                if(p[4]>180)p[4]=180;
              }

              if (com_dc == 'a'){
                p[5]--;
                if(p[5]<0)p[5]=0;
              }
              if (com_dc == 's'){
                p[5]++;
                if(p[5]>180)p[5]=180;
              }

              if (com_dc == 'd'){
                p[6]--;
                if(p[6]<0)p[6]=0;
              }
              if (com_dc == 'f'){
                p[6]++;
                if(p[6]>180)p[6]=180;
              }


              if (com_dc == 'g'){
                p[7]--;
                if(p[7]<0)p[7]=0;
              }
              if (com_dc == 'h'){
                p[7]++;
                if(p[7]>180)p[7]=180;
              }

              if (com_dc == 'j'){
                p[8]--;
                if(p[8]<0)p[8]=0;
              }
              if (com_dc == 'k'){
                p[8]++;
                if(p[8]>180)p[8]=180;
              }

              if (com_dc == 'z'){
                p[9]--;
                if(p[9]<0)p[9]=0;
              }
              if (com_dc == 'x'){
                p[9]++;
                if(p[9]>180)p[9]=180;
              }

              if (com_dc == 'c'){
                p[10]--;
                if(p[10]<0)p[10]=0;
              }
              if (com_dc == 'v'){
                p[10]++;
                if(p[10]>180)p[10]=180;
              }

              if (com_dc == 'b'){
                p[11]--;
                if(p[11]<0)p[11]=0;
              }
              if (com_dc == 'n'){
                p[11]++;
                if(p[11]>180)p[11]=180;
              }
              if (com_dc == ','){
                break;
              }
              if (com_dc == '1'){
                Serial.println("detached all");
                DetachAll();
              }

              if (com_dc == '3'){
                DetachHands();
                 Serial.println("detached hands");
              }
              if (com_dc == '2'){
                 Serial.println("attach all");
                AttachAll();
              }

              
              if(com_dc == 'm'){
                for (int i = 0; i<=11; i++){
                  Serial.println("Saving position");
                EEPROM.write(i+12*lev, p[i]);
                Serial.println(p[i]);
                }
                Serial.println("new positions");
                for (int i = 0; i<=11; i++){
                  Serial.println(EEPROM.read(i+12*lev));
                }
                Serial.println("addres");
                for (int i = 0; i<=11; i++){
                  Serial.println((i+12*5));
                }
                
                break;
                }
              }

              

              Move(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11],1);
            }
  }




Patrik patrik;


void setup() { 
//  Fill();
    patrik.init1();
//      Fill();
//patrik.DetachAll();
//patrik.Pump(3000);
//
}

void loop() {
 
//patrik.Scan(60000);
//digitalWrite(37, HIGH);
//patrik.Pump(1);
    patrik.Run(180000);

}
