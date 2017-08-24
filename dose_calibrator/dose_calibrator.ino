#include <LiquidCrystal.h>
#include <EEPROM.h>

#define start digitalRead(A5)
#define stops digitalRead(6) // unfixed
#define up digitalRead(A3)
#define down digitalRead(A2)
#define set digitalRead(A4)
#define Cal digitalRead(A1)
#define lampu A0
#define adio 0
#define adtc 1
#define admo 2
#define adga 3
#define adxe 4
#define addi 5
#define adx 6

LiquidCrystal lcd(2, 3, 4, 8, 9, 10, 11);

unsigned int io; //EEPROM 0
unsigned int tc; //EEPROM 1
unsigned int mo; //EEPROM 2
unsigned int ga; //EEPROM 3
unsigned int xe; //EEPROM 4
unsigned int di; //EEPROM 5
unsigned int  x = 1; // EEPROM 6

volatile unsigned char looping = 0;
volatile int t;
char buff[103];
char bd[20];
unsigned int a;
volatile unsigned int b;
unsigned int e;
float c;
float d;

void setup() {

  a = 0;
  b = 0;
  c = 0;
  d = 0;

  io = EEPROM.read(adio);
  tc = EEPROM.read(adtc);
  mo = EEPROM.read(admo);
  ga = EEPROM.read(adga);
  xe = EEPROM.read(adxe);
  di = EEPROM.read(addi);
  x = EEPROM.read(adx);

  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);

  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);

  //Initialize Timer, Interrupt Overflow Active
  TIMSK2 |= (1 << TOIE2);
  TIMSK1 |= (1 << TOIE1);
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCCR2B = 0x00;
  TCNT1 = 0;

  //Initialize LCD Graphics 16x2
  lcd.begin(16, 2);

}

void tampil()
{
  a = TCNT1;
  c = (b * 65536) + a;
  d = c / 400;
  if (d <= 999.999) {
    sprintf(buff, "    ""t=%2ds", e);
    lcd.setCursor(7, 0);
    lcd.print(buff);
    dtostrf(d, -1, 3, bd);
    sprintf(buff, "%s mCi", bd);
    lcd.setCursor(0, 1);
    lcd.print(buff);

    sprintf(buff, "%2d", t);
    lcd.setCursor(13, 1);
    lcd.print(buff);
  }
}

void setting() {
  switch (x)
  {
    case 1:
      if ((!up) & (!Cal))
      {
        delay(250);
        io++;
        EEPROM.write(adio, io);
        if (io >= 61) {
          io = 1;
          EEPROM.write(adio, io);
        }
      };

      if ((!down) & (!Cal))
      {
        delay(250);
        io--;
        EEPROM.write(adio, io);
        if (io <= 0) {
          io = 60;
          EEPROM.write(adio, io);
        }
      };
      e = io;
      lcd.setCursor(0, 0);
      lcd.print("I-131 ");
      tampil(); break;

    case 2:
      if ((!up) & (!Cal))
      {
        delay(250);
        tc++;
        EEPROM.write(adtc, tc);
        if (tc >= 61) {
          tc = 1;
          EEPROM.write(adtc, tc);
        }
      };

      if ((!down) & (!Cal))
      {
        delay(250);
        tc--;
        EEPROM.write(adtc, tc);
        if (tc <= 0) {
          tc = 60;
          EEPROM.write(adtc, tc);
        }
      };
      e = tc;
      lcd.setCursor(0, 0);
      lcd.print("Tc-99 ");
      tampil(); break;

    case 3:
      if ((!up) & (!Cal))
      {
        delay(250);
        mo++;
        EEPROM.write(admo, mo);
        if (mo >= 61) {
          mo = 1;
          EEPROM.write(admo, mo);
        }
      };

      if ((!down) & (!Cal))
      {
        delay(250);
        mo--;
        EEPROM.write(admo, mo);
        if (mo <= 0) {
          mo = 60;
          EEPROM.write(admo, mo);
        }
      };
      e = mo;
      lcd.setCursor(0, 0);
      lcd.print("Mo-99 ");
      tampil(); break;

    case 4:
      if ((!up) & (!Cal))
      {
        delay(250);
        ga++;
        EEPROM.write(adga, ga);
        if (ga >= 61) {
          ga = 1;
          EEPROM.write(adga, ga);
        }
      };

      if ((!down) & (!Cal))
      {
        delay(250);
        ga--;
        EEPROM.write(adga, ga);
        if (ga <= 0) {
          ga = 60;
          EEPROM.write(adga, ga);
        }
      };
      e = ga;
      lcd.setCursor(0, 0);
      lcd.print("Ga-67 ");
      tampil(); break;

    case 5:
      if ((!up) & (!Cal))
      {
        delay(250);
        xe++;
        EEPROM.write(adxe, xe);
        if (xe >= 61) {
          xe = 1;
          EEPROM.write(adxe, xe);
        }
      };

      if ((!down) & (!Cal))
      {
        delay(250);
        xe--;
        EEPROM.write(adxe, xe);
        if (xe <= 0) {
          xe = 60;
          EEPROM.write(adxe, xe);
        }
      };
      e = xe;
      lcd.setCursor(0, 0);
      lcd.print("Xe-133");
      tampil(); break;

    case 6:
      if ((!up) & (!Cal))
      {
        delay(250);
        di++;
        EEPROM.write(addi, di);
        if (di >= 61) {
          di = 1;
          EEPROM.write(addi, di);
        }
      };

      if ((!down) & (!Cal))
      {
        delay(250);
        di--;
        EEPROM.write(addi, di);
        if (di <= 0) {
          di = 60;
          EEPROM.write(addi, di);
        }
      };
      e = di;
      lcd.setCursor(0, 0);
      lcd.print("DIAL  ");
      tampil(); break;
  }
}

void kerja()
{
  if (!start)
  {
    delay(100);
    TCNT2 = 99;
    TCNT1 = 0;
    TCCR2A = 0x00;
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
    TCCR1B |= (1 << CS12) | (1 << CS11);
    b = 0;
    t = 0;
    digitalWrite(lampu, HIGH);
    lcd.clear();
  }

  if (t >= e)
  {
    TCCR1B = 0x00;
    TCCR2B = 0x00;
    looping = 0;
    digitalWrite(lampu, LOW);

    sprintf(buff, "t=""%2ds", e);
    lcd.setCursor(11, 0);
    lcd.print(buff);
    dtostrf(d, -1, 3, bd);
    sprintf(buff, "%s mCi", bd);
    lcd.setCursor(0, 1);
    lcd.print(buff);
  }

  if (!stops)
  {
    TCCR1B = 0x00;
    TCCR2B = 0x00;
    delay(100);
    looping = 0;
    digitalWrite(lampu, LOW);
  }

  if (!set)
  {
    delay(250);
    x++;
    EEPROM.write(adx, x);
    if (x == 7) {
      x = 1;
      EEPROM.write(adx, x);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  setting();
  kerja();
}

ISR(TIMER1_OVF_vect) {
  b += 1;
}


//TIMER2 overflow interrupt subroutine
ISR(TIMER2_OVF_vect) {
  TCNT2 = 99; //per 10ms
  looping++;
  if (looping == 100) {
    t++;
    looping = 0;
  }
}

