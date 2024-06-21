#include <LiquidCrystal_I2C.h> // lcd Header
LiquidCrystal_I2C lcd(0x27, 16, 2); // pins for LCD Connection
 
#define buzzer 12 // buzzer pin
#define led 13 //led pin
 
#define x A0 // x_out pin of Accelerometer
#define y A1 // y_out pin of Accelerometer
#define z A2 // z_out pin of Accelerometer
 
/*variables*/
int xsample=0;
int ysample=0;
int zsample=0;
long start;
int buz=0;
 
/*Macros*/
#define samples 50
#define maxVal 20 // max change limit
#define minVal -20 // min change limit
#define buzTime 5000 // buzzer on time

void setup() 
{
  // put your setup code here, to run once:
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight 
  Serial.begin(9600); // initializing serial
  delay(1000);
  lcd.print("EarthQuake ");
  lcd.setCursor(0,1);
  lcd.print("Detector ");
  delay(2000);
  lcd.clear();
  lcd.print("Calibrating.....");
  lcd.setCursor(0,1);
  lcd.print("Please wait...");
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  buz=0;
  digitalWrite(buzzer, buz);
  digitalWrite(led, buz);
  for(int i=0;i<samples;i++) 
  {
    xsample+=analogRead(x);
    ysample+=analogRead(y);
    zsample+=analogRead(z);
  }

  xsample/=samples; 
  ysample/=samples; 
  zsample/=samples; 

  delay(3000);
  lcd.clear();
  lcd.print("Calibrated");
  delay(1000);
  lcd.clear();
  lcd.print("Device Ready");
  delay(1000);
  lcd.clear();
  lcd.print(" X Y Z ");

}

void loop() 
{
  int value1=analogRead(x);
  int value2=analogRead(y);
  int value3=analogRead(z);

  int xValue=xsample-value1; // finding change in x
  int yValue=ysample-value2; // finding change in y
  int zValue=zsample-value3; // finding change in z

  lcd.setCursor(0,1);
  lcd.print(xValue);
  lcd.setCursor(6,1);
  lcd.print(yValue);
  lcd.setCursor(12,1);
  lcd.print(zValue);
  delay(100);

  if(xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal)
  {
    start=millis(); // timer start
    buz=1; // buzzer / led flag activated
  }
  else if(buz == 1) // buzzer flag activated then alerting earthquake
  {
    lcd.setCursor(0,0);
    lcd.print("Earthquake Alert ");
    if(millis()>= start+buzTime)
    buz=0;
  }
  else
  {
    lcd.clear();
    lcd.print(" X Y Z ");
  }

  if(buz == 0){ //LED and buzzer on/off command
    noTone(buzzer); 
    digitalWrite(led, LOW); 
  }else if(buz == 1){
    tone(buzzer, 1000); 
    digitalWrite(led, HIGH); 
  }

  Serial.print("x=");
  Serial.println(xValue);
  Serial.print("y=");
  Serial.println(yValue);
  Serial.print("z=");
  Serial.println(zValue);
  Serial.println(" $");

}
