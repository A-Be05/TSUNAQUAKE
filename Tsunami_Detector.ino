//Program arduino dengan sensor jarak HC-SR4
//untuk aplikasi pendeteksi bahaya tsunami
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define trigPin A0
#define echoPin A1
#define merah 11
#define kuning 12
#define hijau 13
#define buzzer 10


void setup() 
{
  lcd.init();
  lcd.backlight();
  Serial.begin (9600);
  pinMode(buzzer, OUTPUT);
  lcd.setCursor(4,0);
  lcd.print("Tsunami ");
  lcd.setCursor(4,1);
  lcd.print("Detector ");
  delay(2000);
  lcd.clear();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(merah, OUTPUT);
  pinMode(kuning, OUTPUT);
  pinMode(hijau, OUTPUT);
  lcd.setCursor(2,0);
  lcd.print("Device Ready");
  delay(2000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(" Distance :  ");
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  //JARAK APABILA KURANG DARI 150 CM
  if (distance <= 150 && distance > 30) {
  digitalWrite(hijau, HIGH); //led peringatan berhenti hidup
  noTone(buzzer);
  }
  else {
  digitalWrite(hijau,LOW); //led peringatan berhenti mati
  }

  //JARAK APABILA KURANG DARI 30 CM
  if (distance <=30 && distance > 10) {
  digitalWrite(kuning, HIGH);
  tone(buzzer, 1000);
  }

  else {
  digitalWrite(kuning, LOW);
  }

  //JARAK APABILA KURANG DARI 10 CM
  if (distance <= 10) {
  digitalWrite(merah, HIGH);
  tone(buzzer, 2000);
  }

  else {
  digitalWrite(merah, LOW);
  }

  if (distance > 150 || distance <= 0){
  Serial.println("Jarak diluar jangkauan!");
  noTone(buzzer);
  }

  else {
    if (distance < 100 && distance > 9){
      lcd.setCursor(5,1);
      lcd.print(distance);
      lcd.setCursor(7,1);
      lcd.print(" ");
    }else if (distance < 10 && distance > -1){
      lcd.setCursor(5,1);
      lcd.print(distance);
      lcd.setCursor(7,1);
      lcd.print(" ");
      lcd.setCursor(6,1);
      lcd.print(" ");
    }else if (distance > 99){
      lcd.setCursor(5,1);
      lcd.print(distance);
    }
  lcd.setCursor(9,1);
  lcd.print("cm");
  Serial.print(distance);
  Serial.println(" cm");  //perintah mencetak jarak pada serial monitor PC
  }

  delay(500);
}
