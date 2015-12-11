#include <LiquidCrystal.h>

/*******************************************************

(c) Nicolas Grebe
11.12.2015

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
unsigned int msec_1 = 0;
unsigned int msec_2 = 0;
unsigned int sec_1 = 0;
unsigned int sec_2 = 0;
int minu_1 = 0;
int minu_2 = 0;
int Go_1 = 0;
int Go_2 = 0;
unsigned int msec_Start_1 = 0;
unsigned int msec_Start_2 = 0;
unsigned int msec_Stopp_1 = 0;
unsigned int msec_Stopp_2 = 0;
int LCD_Port = 1; //An welchem IO die Taster HÃ¤ngen
int Offset_Timing = 0; //fÃ¼r Zeit um an den Start zu kommen

// FÃ¼r Config
int Seite = 0;
int Offset_Wand_0 = 690;    // Nix aus Messung
int Offset_Wand_1 = 520;   // Start aus Messung
int Offset_Wand_2 = 110;    // Stopp aus Messung
/*Alt:
int Offset_LCD_0 = 1000;    //Aus Original Code NIX
int Offset_LCD_1 = 50;      //Aus Original Code Rechts
int Offset_LCD_2 = 150;     //Aus Original Code Hoch
int Offset_LCD_3 = 350;     //Aus Original Code Runter
int Offset_LCD_4 = 500;     //Aus Original Code Links
int Offset_LCD_5 = 750;     //Aus Original Code OK
 Neue:*/
int Offset_LCD_0 = 1000;    //Aus Original Code NIX
int Offset_LCD_1 = 50;      //Aus Original Code Rechts
int Offset_LCD_2 = 410;     //Aus Original Code Hoch
int Offset_LCD_3 = 590;     //Aus Original Code LINKS
int Offset_LCD_4 = 760;     //Aus Original Code runter
int Offset_LCD_5 = 880;     //Aus Original Code OK

int Beep = 1; // 1 = Beep An
int Var = 0; // Zum Erleichtern der Ã„nderung

//Config
void Config() {
  int key = -1;
  while (Seite != -1) {
    //BlÃ¤tter/Ã„ndern
    key = read_LCD_buttons();
    switch (key) {
      case -1:
        //Nix
        delay(1);
        break;
      case 1://Rechts
        if (Seite >= 11 ) {
          Seite = 1;
        } else {
          Seite++;
        } while (read_LCD_buttons() == 1) {
          delay(10);
        }
        break;
      case 2://Hoch
        Var++;
        delay(1000);
        while (read_LCD_buttons() == 2) {
          delay(10);
          Var++;
          lcd.setCursor(0, 1);
          lcd.print(Var);
        }
        break;
      case 3://Runter
        Var--;
        delay(1000 );
        while (read_LCD_buttons() == 3) {
          delay(10);
          Var--;
          lcd.setCursor(0, 1);
          lcd.print(Var);
        }
        break;

      case 4://Links
        if (Seite <= 1 ) {
          Seite = 11;
        } else {
          Seite--;
        }
        while (read_LCD_buttons() == 4) {
          delay(10);
        }
        break;

      case 5://OK
        if (Seite == 10) { //Summer
          if (Beep == 1) {
            Beep = 0;
          } else {
            Beep = 1;
            digitalWrite(2, HIGH);
            delay(500);
            digitalWrite(2, LOW);
          }
        }
        if (Seite == 11) {//Exit
          Seite = -1;
        }
        while (read_LCD_buttons() != 0) {
          delay(10);
        }
        break;

    }
    //Ausgabe
    switch (Seite) {
      case 1:
        if (Var != Offset_LCD_0) {
          Var = Offset_LCD_0;
        }
        lcd.setCursor(0, 0);
        lcd.print("1 Offset LCD 0  ");
        lcd.setCursor(0, 1);
        lcd.print(read_LCD_buttons());//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_LCD_0);
        lcd.print("-");
        lcd.print(analogRead(LCD_Port));
        Offset_LCD_0 = Var;
        break;
      case 2:
        if (Var != Offset_LCD_1) {
          Var = Offset_LCD_1;
        }
        lcd.setCursor(0, 0);
        lcd.print("2 Offset LCD 1  ");
        lcd.setCursor(0, 1);
        lcd.print(read_LCD_buttons());//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_LCD_1);
        lcd.print("-");
        lcd.print(analogRead(LCD_Port));
        Offset_LCD_1 = Var;
        break;
      case 3:
        if (Var != Offset_LCD_2) {
          Var = Offset_LCD_2;
        }
        lcd.setCursor(0, 0);
        lcd.print("3 Offset LCD 2  ");
        lcd.setCursor(0, 1);
        lcd.print(read_LCD_buttons());//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_LCD_2);
        lcd.print("-");
        lcd.print(analogRead(LCD_Port));
        Offset_LCD_2 = Var;
        break;
      case 4:
        if (Var != Offset_LCD_3) {
          Var = Offset_LCD_3;
        }
        lcd.setCursor(0, 0);
        lcd.print("4 Offset LCD 3  ");
        lcd.setCursor(0, 1);
        lcd.print(read_LCD_buttons());//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_LCD_3);
        lcd.print("-");
        lcd.print(analogRead(LCD_Port));
        Offset_LCD_3 = Var;
        break;
      case 5:
        if (Var != Offset_LCD_4) {
          Var = Offset_LCD_4;
        }
        lcd.setCursor(0, 0);
        lcd.print("5 Offset LCD 4  ");
        lcd.setCursor(0, 1);
        lcd.print(read_LCD_buttons());//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_LCD_4);
        lcd.print("-");
        lcd.print(analogRead(LCD_Port));
        Offset_LCD_4 = Var;
        break;
      case 6:
        if (Var != Offset_LCD_5) {
          Var = Offset_LCD_5;
        }
        lcd.setCursor(0, 0);
        lcd.print("6 Offset LCD 5  ");
        lcd.setCursor(0, 1);
        lcd.print(read_LCD_buttons());//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_LCD_5);
        lcd.print("-");
        lcd.print(analogRead(LCD_Port));
        Offset_LCD_5 = Var;
        break;
      case 7:
        if (Var != Offset_Wand_0) {
          Var = Offset_Wand_0;
        }
        lcd.setCursor(0, 0);
        lcd.print("7 Offset Wand1 0");
        lcd.setCursor(0, 1);
        lcd.print(read_WAND_buttons(1));//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_Wand_0);
        lcd.print("-");
        lcd.print(analogRead(1));
        Offset_Wand_0 = Var;
        break;
      case 8:
        if (Var != Offset_Wand_1) {
          Var = Offset_Wand_1;
        }
        lcd.setCursor(0, 0);
        lcd.print("8 Offset Wand1 1");
        lcd.setCursor(0, 1);
        lcd.print(read_WAND_buttons(1));//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_Wand_1);
        lcd.print("-");
        lcd.print(analogRead(1));
        Offset_Wand_1 = Var;
        break;
      case 9:
        if (Var != Offset_Wand_2) {
          Var = Offset_Wand_2;
        }
        lcd.setCursor(0, 0);
        lcd.print("9 Offset Wand1 2");
        lcd.setCursor(0, 1);
        lcd.print(read_WAND_buttons(1));//W-     SSSS-IIII
        lcd.print("-     ");
        lcd.print(Offset_Wand_2);
        lcd.print("-");
        lcd.print(analogRead(1));
        Offset_Wand_2 = Var;
        break;
      case 10:
        lcd.setCursor(0, 0);
        lcd.print("10 Summer        ");
        lcd.setCursor(0, 1);
        if (Beep == 1) {
          lcd.print("Ist An-Aus Machen");
        } else {
          lcd.print("Ist Aus-An Machen");
        }
        break;
      case 11://Exit Seite
        lcd.setCursor(0, 0);
        lcd.print("------EXIT-------");
        lcd.setCursor(0, 1);
        lcd.print("Mit OK Speichern ");
        break;
    }
  }
}

//Rechnen
void Rechnen()
{
  msec_1 = msec_Stopp_1 - msec_Start_1;
  msec_2 = msec_Stopp_2 - msec_Start_2;
  sec_1 = (msec_Stopp_1 - msec_Start_1) / 1000;
  sec_2 = (msec_Stopp_2 - msec_Start_2) / 1000;
  minu_1 = sec_1 / 60;
  minu_2 = sec_2 / 60;
  msec_1 = msec_1 % 1000;
  msec_2 = msec_2 % 1000;
  sec_1 = sec_1 % 60;
  sec_2 = sec_2 % 60;
  minu_1 = minu_1 % 60;
  minu_2 = minu_2 % 60;

}
//Serial Out
void Out_Serial()
{
  Serial.println("----------------");
  Serial.print("1:     ");
  if (minu_1 < 10) {
    Serial.print("0");
  }
  Serial.print(minu_1);

  Serial.print(":");
  if (sec_1 < 10) {
    Serial.print("0");
  }
  Serial.print(sec_1);
  Serial.print(":");
  if (msec_1 < 10) {
    Serial.print("00");
  } else {
    if (msec_1 < 100) {
      Serial.print("0");
    }
  }
  Serial.println(msec_1);
  //Wert 2
  Serial.print("2:     ");
  if (minu_2 < 10) {
    Serial.print("0");
  }
  Serial.print(minu_2);
  Serial.print(":");
  if (sec_2 < 10) {
    Serial.print("0");
  }
  Serial.print(sec_2);
  Serial.print(":");
  if (msec_2 < 10) {
    Serial.print("00");
  } else {
    if (msec_2 < 100) {
      Serial.print("0");
    }
  }
  Serial.println(msec_2);
  Serial.println("----------------");
}
// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(3);      // read the value from the sensor
  if (Offset_LCD_1 > adc_key_in) {
    return 1;
  } else {
    if (Offset_LCD_2 > adc_key_in) {
      return 2;
    } else {
      if (Offset_LCD_3 > adc_key_in) {
        return 4;
      } else {
        if (Offset_LCD_4 > adc_key_in) {
          return 3;
        } else {
          if (Offset_LCD_5 > adc_key_in) {
            return 5;
          } else {
            if (Offset_LCD_0 < adc_key_in) {
              return 0;
            }
          }
        }
      }
    }
  }
}
// read the buttons
int read_WAND_buttons(int in)
{
  adc_key_in = analogRead(in);      // read the value from the sensor
  if (adc_key_in < Offset_Wand_2)  return 2;//stop
  if (adc_key_in < Offset_Wand_1 && adc_key_in > Offset_Wand_2)  return 1;//Start
  if (adc_key_in < Offset_Wand_0 && adc_key_in > Offset_Wand_1)  return 0;//nix
  return 2;
}

void setup()
{
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  lcd.print("Uhr V 1.4 CND");
  lcd.setCursor(0, 1);
  lcd.print("(c)Nicolas Grebe");
  Serial.begin(9600);            //Serielle Verbindung Starten
  Serial.println("----------------");
  Serial.println("Uhr V 1.4 CND   ");
  Serial.println("(c)Nicolas Grebe");
  Serial.println("----------------");
  Seite = read_LCD_buttons();
  for (int i = 1; i < 100; i++) {
    delay(10);
    if (read_LCD_buttons() != 0) { // Goto Setup Settings
      Seite = read_LCD_buttons();
      lcd.setCursor(0, 0);
      lcd.print("  Enter Setup  ");
      lcd.setCursor(0, 1);
      lcd.print("(c)Nicolas Grebe");
      i = 110;
    }
  }
  if (Seite != 0) {
    Seite = 1;
    while (read_LCD_buttons() != 0) { // Check if Button still is Aktiv
      delay(10);
    }
    Config();
  }
  lcd.setCursor(0, 0);
  lcd.print("1:              ");
  lcd.setCursor(0, 1);
  lcd.print("2:              ");
}

void loop()
{
  if (read_WAND_buttons(2) == 1) {
    Go_2 = 1;
    msec_Start_2 = millis() + Offset_Timing;
    msec_Stopp_2 = millis();
  }
  if (read_WAND_buttons(2) == 2) {
    Go_2 = -1;
    if (Beep == 1) {
      digitalWrite(2, HIGH);
      delay(100);
      digitalWrite(2, LOW);
    }
  }
  if (read_WAND_buttons(1) == 2) {
    Go_1 = -1;
    if (Beep == 1) {
      digitalWrite(2, HIGH);
      delay(100);
      digitalWrite(2, LOW);
    }
  }
  if (read_WAND_buttons(1) == 1) {
    Go_1 = 1;
    msec_Start_1 = millis() + Offset_Timing;
    msec_Stopp_1 = millis();
  }
  if (read_LCD_buttons() == 5) {
    if (Go_1 == 0 && Go_2 == 0) {
      lcd.setCursor(1, 0);
      lcd.print("                ");
      lcd.setCursor(1, 1);
      lcd.print("                ");
      delay(100);
      lcd.setCursor(0, 0);
      lcd.print("    Get Ready ");
      lcd.setCursor(0, 1);
      for (int i = 1; i < 8; i++) {
        lcd.print("##");
        delay(1000 - 125 * i);
        if (Beep == 1) {
          digitalWrite(2, HIGH);
        }
        delay(125 * i);
        digitalWrite(2, LOW);
        if (read_LCD_buttons() == 5) {
          i = 5;
        }
      }
      Offset_Timing = 0;
      msec_Start_1 = millis();
      msec_Start_2 = millis();
      msec_Stopp_1 = millis();
      msec_Stopp_2 = millis();
      Go_1 = 1;
      Go_2 = 1;
    } else {
      Go_1 = 0;
      Go_2 = 0;
      Offset_Timing = 0;
      Out_Serial();
      msec_Start_1 = millis();
      msec_Start_2 = millis();
      msec_Stopp_1 = millis();
      msec_Stopp_2 = millis();
      digitalWrite(2, HIGH);
      while (read_LCD_buttons() != 0) {
        delay(10);
      }
      digitalWrite(2, LOW);
    }
  }

  if (read_LCD_buttons() == 0)// No Button
  {
    //Nix GedrÃ¼ckt
  }
  if (read_LCD_buttons() == 1)//Right Button
  { //Reset Ch 1
    msec_Start_1 = millis();
    msec_Stopp_1 = millis();
    Go_1 = 0;
    Offset_Timing = 0;
  }
  if (read_LCD_buttons() == 2)// Up Button
  {
    while (read_LCD_buttons() == 2) {
      delay(10);
    }
    Offset_Timing++;
    lcd.setCursor(0, 0);
    lcd.print("Start Delay");
    lcd.setCursor(0, 1);
    lcd.print(Offset_Timing);
    lcd.print(" sec");
    delay(1000);
  }
  if (read_LCD_buttons() == 3)// Left Button
  {
    //Reset Ch 2
    msec_Start_2 = millis();
    msec_Stopp_2 = millis();
    Go_2 = 0;
    Offset_Timing = 0;
  }
  if (read_LCD_buttons() == 4)// Down Button
  {
    while (read_LCD_buttons() == 4) {
      delay(10);
    }
    if (Offset_Timing > 1) {
      Offset_Timing--;
    }
    lcd.setCursor(0, 0);
    lcd.print("Start Delay");
    lcd.setCursor(0, 1);
    lcd.print(Offset_Timing);
    lcd.print(" sec");
    delay(1000);
  }
  //Uhr Hochrechnen
  if (Go_1 == 1) {
    msec_Stopp_1 = millis();
  }
  if (Go_2 == 1) {
    msec_Stopp_2 = millis();
  }
  //Rechnen
  Rechnen();
  //OUTPUT LCD
  lcd.setCursor(3, 0);
  if (Go_1 == 1) { // Clock 1 Runig
    lcd.print("RUN");
  } else {
    lcd.print("   ");
  }
  lcd.setCursor(3, 1);
  if (Go_2 == 1) { // Clock 2 Runing
    lcd.print("RUN");
  } else {
    lcd.print("   ");
  }
  if (Go_1 == -1 && Go_2 == -1 && msec_Stopp_1 != msec_Start_1 && msec_Stopp_2 != msec_Start_2) {
    if ((msec_Stopp_1 - msec_Start_1) > (msec_Stopp_2 - msec_Start_2)) {
      lcd.setCursor(3, 1);
      lcd.print("WIN"); // Ch 2 Wins
    } else {
      lcd.setCursor(3, 0);
      lcd.print("WIN"); // Ch 1 Wins
    }
    Go_1 = -1;
    Go_2 = -1;
  }
  lcd.setCursor(7, 0);           // move cursor to second line "0" and 7 spaces over
  if (minu_1 < 10) {
    lcd.print("0");
  }
  lcd.print(minu_1);
  lcd.print(":");
  if (sec_1 < 10) {
    lcd.print("0");
  }
  lcd.print(sec_1);
  lcd.print(":");
  if (msec_1 < 10) {
    lcd.print("00");
  }
  if (msec_1 < 100 && msec_1 > 10) {
    lcd.print("0");
  }
  lcd.print(msec_1);
  lcd.setCursor(7, 1);           // move cursor to second line "1" and 7 spaces over
  if (minu_2 < 10) {
    lcd.print("0");
  }
  lcd.print(minu_2);
  lcd.print(":");
  if (sec_2 < 10) {
    lcd.print("0");
  }
  lcd.print(sec_2);
  lcd.print(":");
  if (msec_2 < 10) {
    lcd.print("00");
  }
  if (msec_2 < 100 && msec_2 > 10) {
    lcd.print("0");
  }
  lcd.print(msec_2);
  lcd.setCursor(0, 0);
  lcd.print("1: ");
  lcd.setCursor(0, 1);
  lcd.print("2: ");
  lcd.setCursor(6, 0);
  lcd.print(" ");
  lcd.setCursor(6, 1);
  lcd.print(" ");
}
