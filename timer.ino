#include <DS3231.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
DS3231 rtc(SDA,SCL);

Time t;
Time tr;

int val=0;
int state=0;
int setbtn=0;
int valchangest=0;
char st[3]={"hms"};

int controlrt;
int run1time =0;

int valset[30];

int day[5];

int hour;
int min;
int sec;

void setup() {
  lcd.begin(16, 2);
  rtc.begin();
  Serial.begin(9600);

  lcd.setCursor(3, 0);
  lcd.print("WELCOME !!!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("MADE BY");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KAVINDA LAKSHAN");
  lcd.setCursor(3, 1);
  lcd.print("JAYARATHNA");
  delay(1000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("loarding");
  lcd.setCursor(1, 1);
  lcd.print("configuration");
  delay(1000);

  for (int i = 0; i < 30; i++){           // read EEPROM data to
    valset[i] = EEPROM.read(i);
  }

  if ( valset[0] > valset[3]){      // to check on/off times in same day or not
    day[0] = 1 ;
  }else{
    day[0] = 0 ;
  }
  if ( valset[6] > valset[9]){
    day[1] = 1 ;
  }else{
    day[1] = 0 ;
  }
  if ( valset[12] > valset[15]){
    day[2] = 1 ;
  }else{
    day[2] = 0 ;
  }
  if ( valset[18] > valset[21]){
    day[3] = 1 ;
  }else{
    day[3] = 0 ;
  }
  if ( valset[24] > valset[27]){
    day[4] = 1 ;
  }else{
    day[4] = 0 ;
  }
  

  pinMode(2, INPUT_PULLUP);   // + button
  pinMode(3, INPUT_PULLUP);   // - button
  pinMode(4, INPUT_PULLUP);   // set buttom
  pinMode(5, INPUT_PULLUP);   // mode button

  pinMode(6, OUTPUT );          //relay
  
  Time ct = rtc.getTime();

  int cth = ct.hour;
  int ctm = ct.min;
  
  if (((cth > valset[0] || (cth == valset[0] && ctm >= valset[1]))                                //check the time it is in relay on time sone then relay on
      && (cth < valset[3] || (cth == valset[3] && ctm < valset[4])))
       || ( (cth > valset[0] || (cth == valset[0] && ctm >= valset[1])) && day[0] == 1 )
        || ( (cth < valset[3] || (cth == valset[3] && ctm < valset[4])) && day[0] == 1 )) {
    Serial.println("relay on");
    digitalWrite (6, HIGH);
  }

  if ((cth > valset[6] || (cth == valset[6] && ctm >= valset[7]))
      && (cth < valset[9] || (cth == valset[9] && ctm < valset[10]))
       || ( (cth > valset[6] || (cth == valset[6] && ctm >= valset[7])) && day[1] == 1 )
        || ( (cth < valset[9] || (cth == valset[9] && ctm < valset[10])) && day[1] == 1 )) {
    Serial.println("relay on");
    digitalWrite (6, HIGH);
  }

  if ((cth > valset[12] || (cth == valset[12] && ctm >= valset[13]))
      && (cth < valset[15] || (cth == valset[15] && ctm < valset[16]))
       || ( (cth > valset[12] || (cth == valset[12] && ctm >= valset[13])) && day[2] == 1 )
        || ( (cth < valset[15] || (cth == valset[15] && ctm < valset[16])) && day[2] == 1 )) {
    Serial.println("relay on");
    digitalWrite (6, HIGH);
  }

  if ((cth > valset[18] || (cth == valset[18] && ctm >= valset[19]))
      && (cth < valset[21] || (cth == valset[21] && ctm < valset[22]))
       || ( (cth > valset[18] || (cth == valset[18] && ctm >= valset[19])) && day[3] == 1 )
        || ( (cth < valset[21] || (cth == valset[21] && ctm < valset[22])) && day[3] == 1 )) {
    Serial.println("relay on");
    digitalWrite (6, HIGH);
  }

  if ((cth > valset[24] || (cth == valset[24] && ctm >= valset[25]))
      && (cth < valset[27] || (cth == valset[27] && ctm < valset[28]))
       || ( (cth > valset[24] || (cth == valset[24] && ctm >= valset[25])) && day[4] == 1 )
        || ( (cth < valset[27] || (cth == valset[27] && ctm < valset[28])) && day[4] == 1 )) {
    Serial.println("relay on");
    digitalWrite (6, HIGH);
  }
  delay(2000);
  lcd.clear();
}


void loop() {
  t = rtc.getTime();

//get hour,min,sec to variables

  int h = t.hour;
  int m = t.min;
  int s = t.sec;

  while( state == 0 ){                // show time in display
    lcd.setCursor(4, 0);
    lcd.print(rtc.getTimeStr());
    delay(1000);
    lcd.clear();

    tr = rtc.getTime();
    int trh = tr.hour;
    int trm = tr.min;
    int trs = tr.sec;

    if ( valset[0] == valset[3] && valset[1] == valset[4] && valset[2] == valset[5] ){        //relay timer 1 on
      //Serial.println("timer 1 off");
    }else if ( valset[0] == trh && valset[1] == trm && valset[2] == trs ){
      Serial.println("relay on");
      digitalWrite (6, HIGH);
    }
    if ( valset[0] == valset[3] && valset[1] == valset[4] && valset[2] == valset[5] ){        //relay timer 1 off
      //Serial.println("timer 1 off");
    }else if ( valset[3] == trh && valset[4] == trm && valset[5] == trs ){
      Serial.println("relay off");
      digitalWrite (6, LOW);
    }

    if ( valset[6] == valset[9] && valset[7] == valset[10] && valset[8] == valset[11] ){        //relay timer 2 on
      //Serial.println("timer 2 off");
    }else if ( valset[6] == trh && valset[7] == trm && valset[8] == trs ){
      Serial.println("relay on");
      digitalWrite (6, HIGH);
    }
    if ( valset[6] == valset[9] && valset[7] == valset[10] && valset[8] == valset[11] ){        //relay timer 2 off
      //Serial.println("timer 2 off");
    }else if ( valset[9] == trh && valset[10] == trm && valset[11] == trs ){
      Serial.println("relay off");
      digitalWrite (6, LOW);
    }

    if ( valset[12] == valset[15] && valset[13] == valset[16] && valset[14] == valset[17] ){        //relay timer 3 on
      //Serial.println("timer 3 off");
    }else if ( valset[12] == trh && valset[13] == trm && valset[14] == trs ){
      Serial.println("relay on");
      digitalWrite (6, HIGH);
    }
    if ( valset[12] == valset[15] && valset[13] == valset[16] && valset[14] == valset[17] ){        //relay timer 3 off
      //Serial.println("timer 3 off");
    }else if ( valset[15] == trh && valset[16] == trm && valset[17] == trs ){
      Serial.println("relay off");
      digitalWrite (6, LOW);
    }

    if ( valset[18] == valset[21] && valset[19] == valset[22] && valset[20] == valset[23] ){        //relay timer 4 on
      //Serial.println("timer 4 off");
    }else if ( valset[18] == trh && valset[19] == trm && valset[20] == trs ){
      Serial.println("relay on");
      digitalWrite (6, HIGH);
    }
    if ( valset[18] == valset[21] && valset[19] == valset[22] && valset[20] == valset[23] ){        //relay timer 4 off
      //Serial.println("timer 4 off");
    }else if ( valset[21] == trh && valset[22] == trm && valset[23] == trs ){
      Serial.println("relay off");
      digitalWrite (6, LOW);
    }

    if ( valset[24] == valset[27] && valset[25] == valset[28] && valset[26] == valset[29] ){        //relay timer 5 on
      //Serial.println("timer 5 off");
    }else if ( valset[24] == trh && valset[25] == trm && valset[26] == trs ){
      Serial.println("relay on");
      digitalWrite (6, HIGH);
    }
    if ( valset[12] == valset[15] && valset[13] == valset[16] && valset[14] == valset[17] ){        //relay timer 5 off
      //Serial.println("timer 5 off");
    }else if ( valset[27] == trh && valset[28] == trm && valset[29] == trs ){
      Serial.println("relay off");
      digitalWrite (6, LOW);
    }
    
    

    if( digitalRead(5)== LOW ){       // select time or timer
      state = 100;
    }
  }


  while ( state == 100 ){
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("change");
    lcd.setCursor(0, 1);
    lcd.print("time + / timer - ");
    if ( digitalRead(2)== LOW ){      // go to change time
      state = 1;
      hour = h;
      min = m;
      sec = s;
    }
    if ( digitalRead(3)== LOW ){    // go to change timer
      state = 2;
      lcd.clear();
    }
    if ( digitalRead(4)== LOW ){     // go back to clock
      lcd.clear();
      state = 0;
    }
  }


  while( state == 1 ){              //change time
    delay(100);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("set time");
    lcd.setCursor(2, 1);
    lcd.print(st[setbtn]);
    lcd.print(" ");
    lcd.print(hour);
    lcd.print(":");
    lcd.print(min);
    lcd.print(":");
    lcd.print(sec);
    
    if ( digitalRead(4)== LOW ){
      delay(100);
      valchangest = valchangest + 1; 
      Serial.print( valchangest );
    }
    if ( valchangest == 1 ){
      changeValues();
    }
    if ( valchangest > 1 ){
      rtc.setTime(hour, min, sec);
      lcd.clear();
      state = 0;
      valchangest = 0;
    }
    
  }

  while( state == 2 ){              //change timer
    
    run1time = run1time +1;
    if (run1time==1){
      lcd.setCursor(3, 0);
      lcd.print("if you set");
      lcd.setCursor(4, 1);
      lcd.print("same time");
      delay(1000);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("to on and off");
      delay(1000);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("it means");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("the timer is off");
      lcd.setCursor(6, 1);
      lcd.print("now");
      delay(1000);
      lcd.clear();
    }

    if ( valchangest > 0 ){
      delay(100);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("set timer");
      lcd.setCursor(2, 1);
      lcd.print(st[setbtn]);
      lcd.print(" ");
      lcd.print(hour);
      lcd.print(":");
      lcd.print(min);
      lcd.print(":");
      lcd.print(sec);
    }
    
    if ( digitalRead(4)== LOW ){
      delay(100);
      valchangest = valchangest + 1; 
      controlrt = 0;
    }

    if ( valchangest == 1 ){
      lcd.setCursor(11, 0);
      lcd.print("1 ON");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[0];
        min =  valset[1];
        sec =  valset[2];
      }
      changeValues();
      valset[0] = hour;      // save change values to array
      valset[1] = min;
      valset[2] = sec;
    }
    if ( valchangest == 2 ){
      lcd.setCursor(11, 0);
      lcd.print("1 OFF");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[3];
        min =  valset[4];
        sec =  valset[5];
      }
      changeValues();
      valset[3] = hour;      // save change values to array
      valset[4] = min;
      valset[5] = sec;
    }

    if ( valchangest == 3 ){
      lcd.setCursor(11, 0);
      lcd.print("2 ON");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[6];
        min =  valset[7];
        sec =  valset[8];
      }
      changeValues();
      valset[6] = hour;      // save change values to array
      valset[7] = min;
      valset[8] = sec;
    }
    if ( valchangest == 4 ){
      lcd.setCursor(11, 0);
      lcd.print("2 OFF");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[9];
        min =  valset[10];
        sec =  valset[11];
      }
      changeValues();
      valset[9] = hour;      // save change values to array
      valset[10] = min;
      valset[11] = sec;
    }

    if ( valchangest == 5 ){
      lcd.setCursor(11, 0);
      lcd.print("3 ON");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[12];
        min =  valset[13];
        sec =  valset[14];
      }
      changeValues();
      valset[12] = hour;      // save change values to array
      valset[13] = min;
      valset[14] = sec;
    }
    if ( valchangest == 6 ){
      lcd.setCursor(11, 0);
      lcd.print("3 OFF");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[15];
        min =  valset[16];
        sec =  valset[17];
      }
      changeValues();
      valset[15] = hour;      // save change values to array
      valset[16] = min;
      valset[17] = sec;
    }

    if ( valchangest == 7 ){
      lcd.setCursor(11, 0);
      lcd.print("4 ON");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[18];
        min =  valset[19];
        sec =  valset[20];
      }
      changeValues();
      valset[18] = hour;      // save change values to array
      valset[19] = min;
      valset[20] = sec;
    }
    if ( valchangest == 8 ){
      lcd.setCursor(11, 0);
      lcd.print("4 OFF");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[21];
        min =  valset[22];
        sec =  valset[23];
      }
      changeValues();
      valset[21] = hour;      // save change values to array
      valset[22] = min;
      valset[23] = sec;
    }

    if ( valchangest == 9 ){
      lcd.setCursor(11, 0);
      lcd.print("5 ON");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[24];
        min =  valset[25];
        sec =  valset[26];
      }
      changeValues();
      valset[24] = hour;      // save change values to array
      valset[25] = min;
      valset[26] = sec;
    }
    if ( valchangest == 10 ){
      lcd.setCursor(11, 0);
      lcd.print("5 OFF");
      controlrt = controlrt + 1;
      if (controlrt == 1){      // to get values from array to display
        hour = valset[27];
        min =  valset[28];
        sec =  valset[29];
      }
      changeValues();
      valset[27] = hour;      // save change values to array
      valset[28] = min;
      valset[29] = sec;
    }



    if ( valchangest > 10 ){       //  data write to the EEPROM
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("saving");
      lcd.setCursor(1, 1);
      lcd.print("configuration");
      for (int i = 0; i < 30; i++){
        EEPROM.write(i, valset[i]);
        delay(100);
      }
      lcd.clear();
      state = 0;
      valchangest = 0;
      run1time = 0;
    }
    
    
  }

}

void changeValues(){
  if ( digitalRead(5)== LOW ){        //change h,m,s state
      delay(100);
      setbtn = setbtn + 1;
    }

    if (digitalRead(2)== LOW && setbtn == 0 ){      //change hour value
      hour = hour + 1;
    }
    if (digitalRead(3)== LOW && setbtn == 0 ){
      hour = hour - 1;
    }
    if (digitalRead(2)== LOW && setbtn == 1 ){      //change min value
      min = min + 1;
    }
    if (digitalRead(3)== LOW && setbtn == 1 ){
      min = min - 1;
    }
    if (digitalRead(2)== LOW && setbtn == 2 ){      //change sec value
      sec = sec + 1;
    }
    if (digitalRead(3)== LOW && setbtn == 2 ){
      sec = sec - 1;
    }


    if ( hour == 24 ){      //reset hour value after get 24
      hour = 0;
    }
    if ( hour == -1 ){      //reset hour value after get -1
      hour = 23;
    }
    if ( min == 60 ){      //reset min value after get 60
      min = 0;
    }
    if ( min == -1 ){      //reset min value after get -1
      min = 59;
    }
    if ( sec == 60 ){      //reset sec value after get 60
      sec = 0;
    }
    if ( sec == -1 ){      //reset sec value after get -1
      sec = 59;
    }


    if ( setbtn == 3 ){     ////reset setbtn value after get 3
      setbtn = 0;
    }
}