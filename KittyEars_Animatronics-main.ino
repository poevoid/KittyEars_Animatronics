
#include <Servo.h>


//приводы
#define       LeftVerPin                     3
#define       LeftAngPin                     5
#define       RightVerPin                    2
#define       RightAngPin                    4
//кнопки
#define       KEY_0_PIN                      6
#define       KEY_1_PIN                      7
#define       KEY_2_PIN                      8
#define       KEY_3_PIN                      9
#define       KEY_4_PIN                      10
#define       KEY_5_PIN                      11
#define       KEY_6_PIN                      12
#define       KEY_7_PIN                      13

#define       KEYS_NUM                       8

#define       KEYBOARD_0                     0
#define       KEYBOARD_1                     1
#define       KEYBOARD_2                     2
#define       KEYBOARD_3                     3
#define       KEYBOARD_4                     4
#define       KEYBOARD_5                     5
#define       KEYBOARD_6                     6
#define       KEYBOARD_7                     7
#define       KEYBOARD_RELEASED              8

//начальное положение приводов
#define       INIT_EARS_POS                  90
#define       INIT_LEFT_VER_POS              130
#define       INIT_RIGHT_VER_POS             50
#define       INIT_LEFT_ANG_POS              80
#define       INIT_RIGHT_ANG_POS             100


Servo LeftVer;
Servo LeftAng;
Servo RightVer;
Servo RightAng;


void setup()
{
  byte KEYS_PINS[KEYS_NUM] = {KEY_0_PIN, KEY_1_PIN, KEY_2_PIN, KEY_3_PIN,
                              KEY_4_PIN, KEY_5_PIN, KEY_6_PIN, KEY_7_PIN};

  for(byte i = 0; i < KEYS_NUM; i++)
  {
    pinMode(KEYS_PINS[i], INPUT);
    digitalWrite(KEYS_PINS[i], HIGH);
  }
  
  LeftVer.attach(LeftVerPin);
  RightVer.attach(RightVerPin);
  LeftAng.attach(LeftAngPin);
  RightAng.attach(RightAngPin);

  LeftVer.write(INIT_LEFT_VER_POS);
  RightVer.write(INIT_RIGHT_VER_POS);
  LeftAng.write(INIT_LEFT_ANG_POS);
  RightAng.write(INIT_RIGHT_ANG_POS);
  delay(300);

  LeftAng.detach();
  RightAng.detach();
  LeftVer.detach();
  RightVer.detach();
}
//------------------------------------------------------
void loop()
{
  byte Key = ScanKeyBoard();

  if (Key != KEYBOARD_RELEASED)
  {
    void (*EARS[KEYS_NUM])(void) = {Ears_0, Ears_1, Ears_2, Ears_3,
                                    Ears_4, Ears_5, Ears_6, Ears_7};    
    (*EARS[Key])();
  }
}
//------------------------------------------------------
void Ears_0()
{
  const byte MaxAngleShift = 30;
  unsigned int MoveDelay = 5;
  unsigned int PosDelay = 500;

  LeftVer.attach(LeftVerPin);
  RightVer.attach(RightVerPin);
  
  for(byte i=0; i <= MaxAngleShift; i++)
  {
    LeftVer.write(INIT_LEFT_VER_POS - i);
    RightVer.write(INIT_RIGHT_VER_POS + i);
    delay(MoveDelay);
  }
  
  for(byte i=0; i <= 3*MaxAngleShift; i++)
  {
    LeftVer.write(INIT_LEFT_VER_POS - MaxAngleShift + i);
    RightVer.write(INIT_RIGHT_VER_POS + MaxAngleShift - i);
    delay(3*MoveDelay);
  }
  
  delay(PosDelay);

  LeftVer.write(INIT_LEFT_VER_POS);
  RightVer.write(INIT_RIGHT_VER_POS);
  delay(500);

  LeftVer.detach();
  RightVer.detach();
}
//------------------------------------------------------
void Ears_1()
{
  const byte MaxAngleShift = 100;
  unsigned int MoveDelay = 10;
  unsigned int PosDelay = 500;

  
  LeftAng.attach(LeftAngPin);
  RightAng.attach(RightAngPin);
  
  for(byte i=0; i <= MaxAngleShift; i++)
  {
    LeftAng.write(INIT_LEFT_ANG_POS + i);
    RightAng.write(INIT_RIGHT_ANG_POS - i);
    delay(MoveDelay);
  }
  LeftAng.detach();
  RightAng.detach();
  
  LeftVer.attach(LeftVerPin);
  RightVer.attach(RightVerPin);
  for(byte i=0; i <= MaxAngleShift/2; i++)
  {
    LeftVer.write(INIT_LEFT_VER_POS + i);
    RightVer.write(INIT_RIGHT_VER_POS - i);
    delay(MoveDelay/5);
  }
  
  delay(PosDelay);

  LeftAng.attach(LeftAngPin);
  RightAng.attach(RightAngPin);
  
  LeftVer.write(INIT_LEFT_VER_POS);
  RightVer.write(INIT_RIGHT_VER_POS);
  LeftAng.write(INIT_LEFT_ANG_POS);
  RightAng.write(INIT_RIGHT_ANG_POS);
  delay(500);

  LeftVer.detach();
  RightVer.detach();
  LeftAng.detach();
  RightAng.detach();
}
//------------------------------------------------------
void Ears_2()
{
  unsigned int MoveDelay = 10;
  byte AnglePos;
  
  LeftAng.attach(LeftAngPin);
  for(byte i=0; i <= 50; i++)
  {
    LeftAng.write(INIT_LEFT_ANG_POS + i);
    delay(3);
  }
  LeftAng.detach();

  AnglePos = INIT_LEFT_VER_POS;
  LeftVer.attach(LeftVerPin);
  for(byte i=0; i <= 50; i++)
  {
    LeftVer.write(AnglePos);
    AnglePos = INIT_LEFT_VER_POS + i;
    delay(MoveDelay);
  }
  
    
  for(byte i=0; i <= 10; i++)
  {
    LeftVer.write(AnglePos);
    AnglePos -= i;
    delay(MoveDelay);
  }
      
  for(byte j=0; j<5; j++)
  {
    for(byte i=0; i <= 10; i++)
    {
      LeftVer.write(AnglePos);
      AnglePos += i;
      delay(MoveDelay);
    }
    
    for(byte i=0; i <= 10; i++)
    {
      LeftVer.write(AnglePos);
      AnglePos -= i;
      delay(MoveDelay);
    }
  }

  
  LeftAng.attach(LeftAngPin);
  LeftVer.write(INIT_LEFT_VER_POS);
  LeftAng.write(INIT_LEFT_ANG_POS);
  delay(500);

  LeftAng.detach();
  LeftVer.detach();
}
//------------------------------------------------------
void Ears_3()
{
  unsigned int MoveDelay = 10;
  byte AnglePos;
  
  
  RightAng.attach(RightAngPin);
  for(byte i=0; i <= 50; i++)
  {
    RightAng.write(INIT_RIGHT_ANG_POS - i);
    delay(1);
  }
  RightAng.detach();

  AnglePos = INIT_RIGHT_VER_POS;
  RightVer.attach(RightVerPin);
  for(byte i=0; i <= 50; i++)
  {
    RightVer.write(AnglePos);
    AnglePos = INIT_RIGHT_VER_POS - i;
    delay(MoveDelay);
  }
  
  for(byte i=0; i <= 10; i++)
  {
    RightVer.write(AnglePos);
    AnglePos += i;
    delay(MoveDelay);
  }
    
  for(byte j=0; j<5; j++)
  {
    for(byte i=0; i <= 10; i++)
    {
      RightVer.write(AnglePos);
      AnglePos -= i;
      delay(MoveDelay);
    }
    
    for(byte i=0; i <= 10; i++)
    {
      RightVer.write(AnglePos);
      AnglePos += i;
      delay(MoveDelay);
    }
  }
  
  RightAng.attach(RightAngPin);
  RightVer.write(INIT_RIGHT_VER_POS);
  RightAng.write(INIT_RIGHT_ANG_POS);
  delay(500);

  RightAng.detach();
  RightVer.detach();
}
//------------------------------------------------------
void Ears_4()
{
  unsigned int MoveDelay = 10;
  byte AngleLeftPos;
  byte AngleRightPos;

  LeftAng.attach(LeftAngPin);
  RightAng.attach(RightAngPin);
  for(byte i=0; i <= 50; i++)
  {
    LeftAng.write(INIT_LEFT_ANG_POS + i);
    RightAng.write(INIT_RIGHT_ANG_POS - i);
    delay(3);
  }
  LeftAng.detach();
  RightAng.detach();

  AngleLeftPos = INIT_LEFT_VER_POS;
  AngleRightPos = INIT_RIGHT_VER_POS;
  LeftVer.attach(LeftVerPin);
  RightVer.attach(RightVerPin);
  for(byte i=0; i <= 50; i++)
  {
    LeftVer.write(AngleLeftPos);
    RightVer.write(AngleRightPos);
    AngleLeftPos = INIT_LEFT_VER_POS + i;
    AngleRightPos = INIT_RIGHT_VER_POS - i;
    delay(MoveDelay);
  }

  for(byte i=0; i <= 10; i++)
  {
    LeftVer.write(AngleLeftPos);
    RightVer.write(AngleRightPos);
    AngleLeftPos -= i;
    AngleRightPos += i;
    delay(MoveDelay);
  }

  for(byte j=0; j<5; j++)
  {
    for(byte i=0; i <= 10; i++)
    {
      LeftVer.write(AngleLeftPos);
      RightVer.write(AngleRightPos);
      AngleLeftPos += i;
      AngleRightPos -= i;
      delay(MoveDelay);
    }
    
    for(byte i=0; i <= 10; i++)
    {
      LeftVer.write(AngleLeftPos);
      RightVer.write(AngleRightPos);
      AngleLeftPos -= i;
      AngleRightPos += i;
      delay(MoveDelay);
    }
  }

  LeftAng.attach(LeftAngPin);
  RightAng.attach(RightAngPin);
  LeftVer.write(INIT_LEFT_VER_POS);
  LeftAng.write(INIT_LEFT_ANG_POS);
  RightVer.write(INIT_RIGHT_VER_POS);
  RightAng.write(INIT_RIGHT_ANG_POS);
  delay(300);

  LeftAng.detach();
  LeftVer.detach();
  RightAng.detach();
  RightVer.detach();
}
//------------------------------------------------------
void Ears_5()
{
  const byte MaxAngleShift = 50;
  unsigned int PosDelay = 300;

  byte PosLeft = INIT_LEFT_VER_POS;
  byte PosRight = INIT_RIGHT_VER_POS;
  
  LeftVer.attach(LeftVerPin);
  RightVer.attach(RightVerPin);

  PosLeft -= MaxAngleShift;
  PosRight -= MaxAngleShift;
  LeftVer.write(PosLeft);
  RightVer.write(PosRight);

  delay(PosDelay);

  for(byte i = 0; i < 2; i++)
  {
    PosLeft += 2*MaxAngleShift;
    PosRight += 2*MaxAngleShift;
    LeftVer.write(PosLeft);
    RightVer.write(PosRight);
    delay(PosDelay);
    PosLeft -= 2*MaxAngleShift;
    PosRight -= 2*MaxAngleShift;
    LeftVer.write(PosLeft);
    RightVer.write(PosRight);
    delay(PosDelay);
  }

  LeftVer.write(INIT_LEFT_VER_POS);
  RightVer.write(INIT_RIGHT_VER_POS);
  delay(500);

  LeftVer.detach();
  RightVer.detach();
}
//------------------------------------------------------
void Ears_6()
{
  const byte MaxAngleShift = 70;
  
  LeftVer.attach(LeftVerPin);
  RightVer.attach(RightVerPin);
  LeftVer.write(INIT_LEFT_VER_POS - MaxAngleShift);
  RightVer.write(INIT_RIGHT_VER_POS + MaxAngleShift);
  delay(1000);
    
  for(byte i=0; i <= MaxAngleShift; i++)
  {
    LeftVer.write(INIT_LEFT_VER_POS - MaxAngleShift + i);
    RightVer.write(INIT_RIGHT_VER_POS + MaxAngleShift - i);
    delay(30);
  }
  delay(500);

  LeftVer.write(INIT_LEFT_VER_POS);
  RightVer.write(INIT_RIGHT_VER_POS);
  delay(500);

  LeftVer.detach();
  RightVer.detach();
}
//------------------------------------------------------
void Ears_7()
{
  const unsigned int pause = 3000;
  
  Ears_0();
  delay(pause);
  Ears_1();
  delay(pause);
  Ears_2();
  delay(pause);
  Ears_3();
  delay(pause);
  Ears_4();
  delay(pause);
  Ears_5();
  delay(pause);
  Ears_6();
}
//-----------------------------------
//проверка клавиатуры
byte ScanKeyBoard()
{
  byte KEYS_PINS[KEYS_NUM] = {KEY_0_PIN, KEY_1_PIN, KEY_2_PIN, KEY_3_PIN,
                              KEY_4_PIN, KEY_5_PIN, KEY_6_PIN, KEY_7_PIN};

  for (byte i = 0; i < KEYS_NUM; i++)
  {
    if (digitalRead(KEYS_PINS[i]) == 0)
    {
      delay(70);
      if (digitalRead(KEYS_PINS[i]) == 0)
        return i;
    }
  }
  
  return KEYBOARD_RELEASED;
}
