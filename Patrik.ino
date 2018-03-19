//включаем библиотеки
#include <Ultrasonic.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <EEPROM.h>


class Patrik {

  public:

    void init1(int l5 = 13, int l4 = 12, int l3 = 11, int l2 = 10, int l1 = 9, int neck = 8 , int head = 7, int r1 = 6, int r2 = 5, int r3 = 4, int r4 = 3, int r5 = 2,
               int led_pin = 45, int pump_pin = 48, int all = 43, int volume = 30, int sensor = A0);


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
    void SaveDrink();
    void SaveSelfPour();
    void SaveWag();
    void SavePour();
    void SaveNice();

    Patrik(int rx = 44, int tx = 46 , int trig = 30, int echo = 31): mySerial(rx, tx), ultrasonic(trig, echo) {}


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






void Patrik::init1(int l5, int l4, int l3, int l2, int l1, int neck , int head, int r1, int r2, int r3, int r4, int r5,
                   int led_pin, int pump_pin, int all, int volume, int sensor ) {

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
  mp3_set_volume (5);  //громкость плеера
  mp3_set_EQ (5);
  delay(200);
  Say (10, 11);






  if (EEPROM.read(0) > 180) {
    for (int i = 0; i <= 11; i++) {
      EEPROM.write(i, 90);
    }
    for (int i = 12; i<=205; i++){
      EEPROM.write(i, 0);
    }
  }

  


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
Serial.println(" Start self pour");
  for (int i = selfPour_s_1; i <= selfPour_e_1; i++) {
    selfPour[0][i-12*4]= EEPROM.read(i);
     delay(2);
    Serial.print(selfPour[0][i-12*4]);
    Serial.print(" ");
    delay(2);
  }
Serial.println(" ");
  for (int i = selfPour_s_2; i <= selfPour_e_2; i++) {
    selfPour[1][i-12*5]= EEPROM.read(i);
     delay(2);
    Serial.print(selfPour[1][i-12*5]);
    Serial.print(" ");
    delay(2);
  }

Serial.println(" ");
  for (int i = selfPour_s_3; i <= selfPour_e_3; i++) {
    selfPour[2][i-12*6]= EEPROM.read(i);
     delay(2);
    Serial.print(selfPour[2][i-12*6]);
    Serial.print(" ");
    delay(2);
  }
Serial.println("end self pour ");
////
Serial.println("start wag ");
  for (int i = wag_s_1; i <= wag_e_1; i++) {
    wag[0][i-12*7]= EEPROM.read(i);
    delay(2);
    Serial.print(wag[0][i-12*7]);
    Serial.print(" ");
    delay(2);
  }
  Serial.println(" ");
  for (int i = wag_s_2; i <= wag_e_2; i++) {
    wag[1][i-12*8]= EEPROM.read(i);
    delay(2);
    Serial.print(wag[1][i-12*8]);
    Serial.print(" ");
    
  }

  Serial.println(" ");
  for (int i = wag_s_3; i <= wag_e_3; i++) {
    wag[2][i-12*9]= EEPROM.read(i);
    delay(2);
    Serial.print(wag[2][i-12*9]);
    Serial.print(" ");
    
  }
  Serial.println(" ");
  for (int i = wag_s_4; i <= wag_e_4; i++) {
    wag[3][i-12*10]= EEPROM.read(i);
    delay(2);
    Serial.print(wag[3][i-12*10]);
    Serial.print(" ");
    
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

  Hello();
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
  delay(2000);
  long current_time = millis();
  Serial.println("start scan");

  while (1) {
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
    if (distance < min_distance) {
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
      Serial.println("exit move");
      break;
    }
  }


}


void Patrik::Run(long time_b) {

  Scan(time_b);
  if (dist_bool) {
    ResetBools();
    Pour();
  }

  if (sense_bool) {
    ResetBools();
    Drink();
    Nice();
  }

  if (time_bool) {
    ResetBools();
    SelfPour();
    Nice();
  }
}

void Patrik::Say(int from, int to) {
  int rand_val = random(from, to);
  mp3_play (rand_val);
}


void Patrik::Hello() {

  delay(3000);
  Say(1, 2);
  Wag();
}


void Patrik::Drink() {
  //3vars
  //5 lines

  Say(4, 7);

  Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11]);
  
  Move(drink[0][0], drink[0][1], drink[0][2], drink[0][3], drink[0][4], drink[0][5], drink[0][6], drink[0][7], drink[0][8], drink[0][9], drink[0][10], drink[0][11],      50);
  Move(drink[1][0], drink[1][1], drink[1][2], drink[1][3], drink[1][4], drink[1][5], drink[1][6], drink[1][7], drink[1][8], drink[1][9], drink[1][10], drink[1][11],      90);
  delay(3000);
  Move(drink[2][0], drink[2][1], drink[2][2], drink[2][3], drink[2][4], drink[2][5], drink[2][6], drink[2][7], drink[2][8], drink[2][9], drink[2][10], drink[2][11]);
  
  Move(start_pos[0], start_pos[1], start_pos[2], start_pos[3], start_pos[4], start_pos[5],      start_pos[6],      start_pos[7],      start_pos[8], start_pos[9], start_pos[10], start_pos[11]);


}

void Patrik::SelfPour(int del) {
  //7 vars
  //5 lines
  Say(9, 10);
  Move(start_pos[0],        start_pos[1],      start_pos[2], start_pos[3],      start_pos[4],      start_pos[5], start_pos[6], start_pos[7],      start_pos[8], start_pos[9],      start_pos[10], start_pos[11]);
  
  Move(selfPour[0][0], selfPour[0][1], selfPour[0][2], selfPour[0][3], selfPour[0][4], selfPour[0][5], selfPour[0][6], selfPour[0][7], selfPour[0][8], selfPour[0][9], selfPour[0][10], selfPour[0][11]);
  Move(selfPour[1][0], selfPour[1][1], selfPour[1][2], selfPour[1][3], selfPour[1][4], selfPour[1][5], selfPour[1][6], selfPour[1][7], selfPour[1][8], selfPour[1][9], selfPour[1][10], selfPour[1][11]);
  Pump(1);
  delay (del);
  Pump(0);
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
  Say(2, 3);
  Move(wag[3][0], wag[3][1], wag[3][2], wag[3][3], wag[3][4], wag[3][5], wag[3][6], wag[3][7], wag[3][8], wag[3][9], wag[3][10], wag[3][11]);



  Move(start_pos[0] - 30, start_pos[1],      start_pos[2], start_pos[3], start_pos[4],        start_pos[5],      start_pos[6],      start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);
  Led(0);
  Say(3, 4);

}


void Patrik::Pour(int del) {
  //5 lines
  //2vars
  Say(8, 9);
  Move(start_pos[0],       start_pos[1], start_pos[2], start_pos[3], start_pos[4],      start_pos[5], start_pos[6], start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);
  Move(pour[0][0], pour[0][1], pour[0][2], pour[0][3], pour[0][4], pour[0][5], pour[0][6], pour[0][7], pour[0][8], pour[0][9], pour[0][10], pour[0][11]);
  Move(pour[1][0], pour[1][1], pour[1][2], pour[1][3], pour[1][4], pour[1][5], pour[1][6], pour[1][7], pour[1][8], pour[1][9], pour[1][10], pour[1][11]);
  Pump(1);
  delay (del);
  Pump(0);
  Move(pour[2][0], pour[2][1], pour[2][2], pour[2][3], pour[2][4], pour[2][5], pour[2][6], pour[2][7], pour[2][8], pour[2][9], pour[2][10], pour[2][11]);

  Move(start_pos[0],       start_pos[1], start_pos[2], start_pos[3], start_pos[4],      start_pos[5], start_pos[6], start_pos[7], start_pos[8], start_pos[9], start_pos[10], start_pos[11]);


}




void Patrik::Nice(int del) {
  //2 vars
  //5 lines
  Say(7, 8);
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











Patrik patrik;
//0 0 0 0 0 -35 -40 +55 0 0 0 0
//0 0 0 0 0 -35 -40 +55 0 0 0 -50
//0 0 0 0 0 -35 -40 +55 0 0 0 0

//-30 20 0 -20 -80 0 0 -40 0 0 0 -10
// 100 0 0 -20 -80 0 0 -40 0 20 0 -10
//0 0 0 -20 -80 0 0 -40 0 20 0 -10


//-30 0 0 0 -80 0 0 0 0 0 0 0
//-30 -30 0 0 -80 30 -40 0 0 0 0 0
//-30 0 0 0 -80 0 0 0 0 0 0 0
//-30 -30 0 0 -80 -30 -40 0 0 0 0 0


//0 0 0 0 -70 0 0 0 0 0 0 0
//130 0 0 0 -70 0 0 0 0 0 0 0
//0 0 0 0 -70 0 0 0 0 0 0 0

//0 0 0 0 0 30 -30 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 -30 -30 0 0 0 0 0


//int drink[3][12] = { { 30, 90, 60, 60, 120, 70-35, 80-40,125+55, 120, 120, 60, 90 },               { 30, 90,    60, 60, 120,      70-35, 80-40, 125+55, 120, 120, 60, 90-50 }, { 30, 90, 60,   60, 120, 70 -35, 80-40,125+55,120, 120, 60, 90 } } ;
int selfPour[3][12] = { { 30-30, 90+20, 60, 60-20, 120-80, 70, 80, 125-40, 120, 120, 60, 90-10  }, { 30+100, 90,60,60 -20,120 -80, 70, 80, 125-40, 120, 120+20,60, 90-10 },       { 30, 90, 60, 60-20, 120-80, 70, 80, 125 -40, 120, 120+20, 60, 90-10 } };
//int wag[4][12] = { { 30-30, 90, 60, 60, 120-80, 70, 80,125, 120, 120, 60, 90 }, { 30-30, 90-30, 60, 60, 120-80, 70+30, 80-40,125, 120, 120, 60, 90  }, { 30-30, 90, 60, 60, 120-80,70, 80,125, 120, 120, 60, 90 }, { 30-30, 90-30, 60, 60, 120-80, 70-30, 80-40,125, 120, 120, 60, 90  } };
//int pour[3][12] = { { 30, 90, 60, 60, 120-70, 70, 80, 125, 120, 120, 60, 90}, { 30+130, 90, 60, 60, 120-70, 70, 80, 125, 120, 120, 60, 90 }, { 30, 90, 60, 60, 120-70, 70, 80,125, 120, 120, 60, 90 } };
//int nice[3][12] = { { 30, 90, 60, 60, 120,70+ 30, 80-30, 125, 120, 120, 60, 90 }, {  30, 90, 60, 60, 120,70, 80, 125, 120, 120, 60, 90 }, { 30, 90, 60, 60, 120, 70-30, 80-30, 125, 120, 120, 60, 90} };
//
//int drink_s_1 = 12;
//int drink_e_1 = 23;
//
//int drink_s_2 = 24;
//int drink_e_2 = 35;
//
//int drink_s_3 = 36;
//int drink_e_3 = 47;
//
//
//int selfPour_s_1 = 48;
//int selfPour_e_1 = 59;
//
int selfPour_s_2 = 60;
int selfPour_e_2 = 71;
//
//int selfPour_s_3 = 72;
//int selfPour_e_3 = 83;
//
//

int wag_s_1 = 84;
int wag_e_1 = 95;

int wag_s_2 = 96;
int wag_e_2 = 107;

int wag_s_3 = 108;
int wag_e_3 = 119;

int wag_s_4 = 120;
int wag_e_4 = 131;

//
//
//int pour_s_1 = 132;
//int pour_e_1 = 143;
//
//int pour_s_2 = 144;
//int pour_e_2 = 155;
//
//int pour_s_3 = 156;
//int pour_e_3 = 167;
//
//
//
//int nice_s_1 = 168;
//int nice_e_1 = 179;
//
//int nice_s_2 = 180;
//int nice_e_2 = 191;
//
//int nice_s_3 = 192;
//int nice_e_3 = 203;






void setup() {
 
    patrik.init1();
//Serial.begin(9600);
//Serial.println("start");
//for (int i = wag_s_1;i<=wag_e_1; i++){
//  Serial.print(EEPROM.read(i));
//  Serial.print(" ");
//}
//
//Serial.println(" ");
//for (int i = wag_s_2;i<=wag_e_2; i++){
//  Serial.print(EEPROM.read(i));
//  Serial.print(" ");
//}
//
//Serial.println(" ");
//for (int i = wag_s_3;i<=wag_e_3; i++){
//  Serial.print(EEPROM.read(i));
//  Serial.print(" ");
//}
//
//Serial.println(" ");
//for (int i = wag_s_4;i<=wag_e_4; i++){
//  Serial.print(EEPROM.read(i));
//  Serial.print(" ");
//}
//
//Serial.println(" ");


//for (int i = selfPour_s_2; i <= selfPour_e_2; i++) {
//    EEPROM.write(i, selfPour[1][i-12*5]);
//  }

  

}

void loop() {

    patrik.Run(60000);
//Serial.println("asdad ");
}
