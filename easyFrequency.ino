
// easy Frequency Generator By:
// seyed roohollah Marashi
// vitapour Gmbh, Austria Wien
// srmarashi@yahoo.com  
// http://www.marashi.eu

#include "U8glib.h"
U8GLIB_PCD8544 u8g(3, 4, 6, 5, 7);  // CLK ,DIN ,CE ,DC ,RST    //pinout for Nokia LCD

int sumin, tumin, mumin, sum;
int rounding = 0;

void setup(void) {
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(A0, INPUT_PULLUP); // increase
  pinMode(A1, INPUT_PULLUP); // decrease
  digitalWrite(13, LOW);
  rounding  = 0; //this variable for Slow or Fast up/down change frequency when press two button same time
  sum = 0; //this variable is for voltage out
}


void loop(void) {
  u8g.firstPage(); do {
    Serial.print("---");
    u8g.setFont(u8g_font_6x10);
    u8g.setPrintPos( 0, 7);
    u8g.print("Easy Frequency ");
    u8g.setPrintPos( 0, 17);
    u8g.print("   Generator");
    u8g.setPrintPos( 0, 27);
    u8g.print("1HZ ~ 40Khz");
    u8g.setPrintPos( 0, 35);
    u8g.print("BY:srmarashi");
    u8g.setPrintPos( 0, 45);
    sumin = analogRead(A0);
    mumin = analogRead(A1);

    // this section is tuning Low Speed or High Speed frequency increase Decrease
    if ((sumin < 200) and (tumin < 200))
     {
       if (rounding = 0) rounding = 1;

     }

    // this step for add frequency 
    if (sumin < 200)
    {
      if (rounding = 0) sum = sum + 1;
      if (rounding = 1) sum = sum + 20;
      if (sum > 40000)
        sum = 40000;
    }

    // this step for reduce added frequency
    if (mumin < 200)
    {
      if (rounding = 0) sum = sum - 1;
      if (rounding = 1) sum = sum - 20;
      if (sum < 2)
        sum = 1;
    }


    u8g.print(sum);
    tone(A5, sum);
    u8g.print("HZ");

 
    if (rounding = 0) u8g.print("    S");
    if (rounding = 1) u8g.print("    F");

    //This Section will print into Serial to know variables summery
    Serial.print(sumin);
    Serial.print("/");
    Serial.print(mumin);
    Serial.print("/");
    Serial.print(sum);
    Serial.print("/");
    Serial.print(rounding);
    Serial.println();

  }
  while ( u8g.nextPage() );
}


