#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

char password[] = "1234"; // Pin Agar Membuka, Bisa di Ubah Ubah Sesuai Keinginan
char inputCode[5]; 
int inputCount = 0;

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(32, 16, 2); 
Servo myservo;

void setup() {
  lcd.init();
  lcd.backlight();
  myservo.attach(10);
  myservo.write(0); 
  lcd.print("Pin :");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    inputCode[inputCount] = key;
    lcd.setCursor(inputCount, 1);
    lcd.print('*');
    inputCount++;

    if (inputCount == 4) {
      inputCode[inputCount] = '\0';
      delay(500);
      
      if (strcmp(inputCode, password) == 0) {
        lcd.clear();
        lcd.print("Akses Diterima");
        myservo.write(90); 
        delay(3000);
        myservo.write(0);  
        resetLcd();
      } else {
        lcd.clear();
        lcd.print("Password Salah!");
        delay(2000);
        resetLcd();
      }
      inputCount = 0;
    }
  }
}

void resetLcd() {
  lcd.clear();
  lcd.print("Pin :");
  inputCount = 0;
}
