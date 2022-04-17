#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define baudrate 9600

#define Pin 0 

float R1 = 100000.0;
float R5 = 10000.0;
float R3 = 100000.0;
float R2 = 1000.0;
float vcc= 5.0;
  

//------------------Bluetooth------------------

#define rxPin 10
#define txPin 11

SoftwareSerial MyPhone(rxPin ,txPin);

//------------------Rotary encoder------------------

#define clkPin 3
#define dtPin  4
#define swPin  2

bool clkState  = LOW;
bool clkLast  = HIGH;
bool swState  = HIGH;
bool swLast  = HIGH;

int rotVal  = 0;
int menu = 0 ;

//------------------OLED Screen------------------

#define Width 128
#define Height 64
#define Reset -1
#define Address 0x3C

Adafruit_SSD1306 OLED(Width, Height, &Wire, Reset);

//------------------------------------------------------

/*functions :
  spinEncoder: detects the spins of the encoder and print the value of the rotation
  switch: detects if the button of the encoder is pressed and returns how many times it was pressed
  R_Display : displays the value of the resistance
  V_Display : displays the value of the voltage
  StartScreen 
  Menu
*/

void spinEncoder() {
  clkState = digitalRead(clkPin);
  if ((clkLast == LOW) && (clkState == HIGH)) {
    Serial.print("Rotary position ");
    if (digitalRead(dtPin) == HIGH) {
      rotVal = rotVal - 1;
      if ( rotVal < 0 ) {
        rotVal = 0;
      }
    }
    else {
      rotVal++;
      if ( rotVal > 3 ) {
        rotVal = 3;
      }
    }
    Serial.println(rotVal);
    delay(200);
  }
  clkLast = clkState;
}

int Switch() {
  swState = digitalRead(swPin);
  if (swState == LOW && swLast == HIGH) {
    menu++;
    Serial.println(menu);
    delay(100);//debounce
  }
  swLast = swState;
  return menu;

}

void V_Display (float u)
{
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);

  OLED.setCursor(25, 20);
  OLED.println(F("Voltage"));
  OLED.setCursor(30, 45);
  OLED.println(u);
  OLED.setCursor(90, 45);
  OLED.println(F("V"));
}

void R_Display (float r)
{
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);

  OLED.setCursor(5, 15);
  OLED.println(F("Resistance"));
  OLED.setCursor(0, 35);
  OLED.println(r, 1);
  OLED.setCursor(65, 35);
  OLED.println(F("MOhms"));
}

void Calib_Display()
{
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);

  OLED.setCursor(5, 15);
  OLED.println(F("Calib."));
}

void StartScreen () {
  
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);

  OLED.setCursor(30, 15);
  OLED.println("PROJET");
  OLED.setCursor(25, 30);
  OLED.println("CAPTEUR");
  OLED.setCursor(50, 50);
  OLED.setTextSize(1);
  OLED.println("4A-GP");
  OLED.display();
}

void Menu0() {

  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);
  
  OLED.setCursor(5, 5);
  OLED.println("Resistance");
  OLED.fillRect(0, 5, 128, 15, SSD1306_INVERSE);
  OLED.setCursor(5, 25);
  OLED.println("Voltage");
  //OLED.fillRect(0, 25, 130, 17, SSD1306_INVERSE);
  OLED.setCursor(5, 45);
  OLED.println("Calib.");
  //OLED.fillRect(0, 45, 130, 15, SSD1306_INVERSE);
}

void Menu1() {
  
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);
  
  OLED.setCursor(5, 5);
  OLED.println("Resistance");
  //OLED.fillRect(0, 5, 128, 15, SSD1306_INVERSE);
  OLED.setCursor(5, 25);
  OLED.println("Voltage");
  OLED.fillRect(0, 25, 130, 17, SSD1306_INVERSE);
  OLED.setCursor(5, 45);
  OLED.println("Calib.");
  //OLED.fillRect(0, 45, 130, 15, SSD1306_INVERSE);
}

void Menu2() {
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setTextColor(WHITE);
  OLED.setCursor(5, 5);
  OLED.println("Resistance");
  //OLED.fillRect(0, 5, 128, 15, SSD1306_INVERSE);
  OLED.setCursor(5, 25);
  OLED.println("Voltage");
  //OLED.fillRect(0, 25, 130, 17, SSD1306_INVERSE);
  OLED.setCursor(5, 45);
  OLED.println("Calib.");
  OLED.fillRect(0, 45, 130, 15, SSD1306_INVERSE);
}

//============================================================

void setup() {

  Serial.begin(baudrate);
  Serial.println(F("System initialized"));

 //Initializing the rotary encoder
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);

  //Initializing the bluetooth
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  MyPhone.begin(baudrate);

  //Initialisation the OLED screen
  OLED.begin(SSD1306_SWITCHCAPVCC, Address);
  OLED.clearDisplay();
  StartScreen();
  delay(3000);  

  attachInterrupt(digitalPinToInterrupt(clkPin), spinEncoder, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(swPin), Switch, CHANGE);

}

//=============================================================

void loop() {
  
  float Voltage = analogRead(Pin)*5.0/1024.0 ; //4.88e-3; 
  
  if (Voltage <= 0.05){
    Voltage = 0.00 ;
  }
  
  float Rsensor=((1.0+(R3/R2))*R1*(vcc/Voltage)-R1-R5)/1.0e6; 
  MyPhone.write(Voltage/4.0);
  
  spinEncoder();
  Switch();

  Serial.println("V = " + String(Voltage) + ", R=" + String(Rsensor));

  if (rotVal > 2){
    rotVal=0;
  } else {
    switch (rotVal){
      case 0 : 
        Menu0();
        if (!(Switch() == 0)) {
          if (Switch() % 2 == 1) {
              R_Display(Rsensor);
          } else if (Switch() % 2 == 0) { 
              Menu0() ;
          }
        }
        break;
      case 1 :
        Menu1();
        if (!(Switch() == 0)) {
          if (Switch() % 2 == 1) {
              V_Display(Voltage);
          } else if (Switch() % 2 == 0) { 
              Menu1() ;
          }
         }
         break;
      case 2 : 
        Menu2();
        if (!(Switch() == 0)) {
          if (Switch() % 2 == 1) {
              Calib_Display() ;
          } else if (Switch() % 2 == 0) { 
              Menu2() ;
          }
        }
        break;
    }
  }

OLED.display();
}
