void Fill(){

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

    
int drink[3][12] = { { 30, 90, 60, 60, 120, 70-35, 80-40,125+55, 120, 120, 60, 90 },               { 30, 90,    60, 60, 120,      70-35, 80-40, 125+55, 120, 120, 60, 90-50 }, { 30, 90, 60,   60, 120, 70 -35, 80-40,125+55,120, 120, 60, 90 } } ;
int selfPour[3][12] = { { 30-30, 90+20, 60, 60-20, 120-80, 70, 80, 125-40, 120, 120, 60, 90-10  }, { 30+100, 90,60,60 -20,120 -80, 70, 80, 125-40, 120, 120+20,60, 90-10 },       { 30, 90, 60, 60-20, 120-80, 70, 80, 125 -40, 120, 120+20, 60, 90-10 } };
int wag[4][12] = { { 30-30, 90, 60, 60, 120-80, 70, 80,125, 120, 120, 60, 90 }, { 30-30, 90-30, 60, 60, 120-80, 70+30, 80-40,125, 120, 120, 60, 90  }, { 30-30, 90, 60, 60, 120-80,70, 80,125, 120, 120, 60, 90 }, { 30-30, 90-30, 60, 60, 120-80, 70-30, 80-40,125, 120, 120, 60, 90  } };
int pour[3][12] = { { 30, 90, 60, 60, 120-70, 70, 80, 125, 120, 120, 60, 90}, { 30+130, 90, 60, 60, 120-70, 70, 80, 125, 120, 120, 60, 90 }, { 30, 90, 60, 60, 120-70, 70, 80,125, 120, 120, 60, 90 } };
int nice[3][12] = { { 30, 90, 60, 60, 120,70+ 30, 80-30, 125, 120, 120, 60, 90 }, {  30, 90, 60, 60, 120,70, 80, 125, 120, 120, 60, 90 }, { 30, 90, 60, 60, 120, 70-30, 80-30, 125, 120, 120, 60, 90} };


  Serial.println("start eeprom fill");
  delay(5000);

  for (int i = drink_s_1; i <= drink_e_1; i++) {
    EEPROM.write(i, drink[0][i-12]);
  }

  for (int i = drink_s_2; i <= drink_e_2; i++) {
    EEPROM.write(i, drink[1][i-12*2]);
  }


  for (int i = drink_s_3; i <= drink_e_3; i++) {
    EEPROM.write(i, drink[2][i-12*3]);
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


  for (int i = pour_s_1; i <= pour_e_1; i++) {
    EEPROM.write(i, pour[0][i-12*11]);
  }

  for (int i = pour_s_2; i <= pour_e_2; i++) {
    EEPROM.write(i, pour[1][i-12*12]);
  }


  for (int i = pour_s_3; i <= pour_e_3; i++) {
    EEPROM.write(i, pour[2][i-12*13]);
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
delay(5000);
 Serial.println("end eeprom fill");
}
