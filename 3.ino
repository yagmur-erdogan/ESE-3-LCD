#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

SimpleDHT11 dht11(8);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // Ekran baslatma
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
  delay(2000);
  lcd.clear();
}

void loop() {
  int toplamSicaklik = 0;
  int toplamNem = 0;

  for (int i = 0; i < 5; i++) {
    byte sicaklik = 0;
    byte nem = 0;

    dht11.read(&sicaklik, &nem, NULL);

    Serial.print("Sicaklik: ");
    Serial.print((int)sicaklik);
    Serial.print(" C | Nem: %");
    Serial.println((int)nem);

    toplamSicaklik = toplamSicaklik + sicaklik;
    toplamNem = toplamNem + nem;

    delay(200); 
  }

  //ortalama alma
  int ortSicaklik = toplamSicaklik / 5;
  int ortNem = toplamNem / 5;


  lcd.setCursor(0, 0);
  lcd.print("Sicaklik: ");
  lcd.print(ortSicaklik);
  lcd.print(" C  "); 

  lcd.setCursor(0, 1);
  lcd.print("Nem: %");
  lcd.print(ortNem);
  lcd.print("    ");

  delay(1000);
}