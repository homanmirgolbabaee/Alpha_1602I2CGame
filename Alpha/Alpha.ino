#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<Keypad.h>
#define LED_PIN 13
LiquidCrystal_I2C lcd(0x27,16,2);
byte object[] = {
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};
byte Block[]={
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000
};
//-------------------- VARIABLES -----------------------//
const byte ROWS=4; //LEFT -> RIGHT PINS FOR 4X3 keypad //digital pins from 9 -> ~3 
const byte COLS=3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3};
Keypad keypad= Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);
int cursorCount = 0; //for dispalying object and moving on to the next block
int cursorUP_DOWN = 0; // for column
int OCP = 5;
//-------------------- VARIABLES -----------------------//


//--------------------  FUNCTIONS   -------------------//

int Move(int x , int y){
  lcd.setCursor(x,y);
  lcd.write(3);
  if( x >= 16 ){
      x = 0;
      lcd.setCursor(0,0);
  }
  Serial.print(" X => ");
  Serial.println(x);
}

int MOVE_DOWN(int x , int y){
  lcd.setCursor(x,y);
  lcd.write(3);
}
//--------------------  FUNCTIONS   -------------------//
// || SETUP_FUNCTION ||  ............. || ............||
void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  // lcd.setCursor(0,0);
  lcd.createChar(3, object);
  lcd.createChar(0, Block);
  lcd.setCursor(0,0);
  lcd.home();
  digitalWrite(LED_PIN,LOW);
  Serial.begin(9600);
  
}


void loop() {
  char key = keypad.getKey();
  if(key){
    switch(key){
      case '6': //forward
        cursorCount = cursorCount + 1; 
        Serial.println(cursorCount);
        Move(cursorCount,cursorUP_DOWN);  
        if(cursorCount ==16){
          cursorCount =0;
        }
        delay(175); //------- MOVEMENT SPEED ---------//
        lcd.clear();
        break;
      case '4': // ---- MOVE BACK ----// 
        cursorCount = cursorCount - 1;
        Move(cursorCount,cursorUP_DOWN);
        if(cursorCount < 0 ){
          cursorCount =0;
        }
        delay(175);
        lcd.clear();
        break;
      case '8': // MOVE-DOWN
        cursorUP_DOWN = 1;
        MOVE_DOWN(cursorCount,cursorUP_DOWN);
        delay(175);
        lcd.clear();
        break;
      case '2':
        cursorUP_DOWN = 0;
        MOVE_DOWN(cursorCount,cursorUP_DOWN);
        delay(175);
        lcd.clear();
        break;
    }
  }
  
  /* --------OLD CODE WITH 'IF'--------------/
  if (key== keys[1][2]){
    Serial.print("Key : ");
    Serial.println(key);
    lcd.setCursor(cursorCount,0);
    lcd.write(3);
    delay(500);
    cursorCount = cursorCount +1;
    if(cursorCount == 16){
      cursorCount = 0;
    }
    delay(50);
    lcd.clear();
  }
  if(key == keys[1][0]){
    int newCursor = cursorCount -2;
    lcd.setCursor(newCursor, 0);
    lcd.write(3);
    delay(500);
    cursorCount ==cursorCount -1;
    if(cursorCount == 16){
      cursorCount = 0;
    }
    delay(50);
    lcd.clear();
     
  }
  --------OLD CODE WITH 'IF'-------------- */
}
