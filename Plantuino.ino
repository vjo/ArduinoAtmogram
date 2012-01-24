// Global area
#include "LCD4884.h"
#include "DHT.h"


#define DHTPIN A1     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 : our captor

const float MULTIPLIER = 0.48828;
DHT dht(DHTPIN, DHTTYPE);

// Initialization that run on 
// powerup or after reset
void setup() {
  lcd.LCD_init();
  lcd.LCD_clear();
  lcd.LCD_write_string(0, 0, "Florian &", MENU_NORMAL );
  lcd.LCD_write_string(0, 1, "Victor", MENU_NORMAL );
  lcd.LCD_write_string(0, 2, "presents:", MENU_NORMAL );
  lcd.LCD_write_string(0, 3, "temp &", MENU_NORMAL );
  lcd.LCD_write_string(0, 4, "humidity", MENU_NORMAL );
  lcd.LCD_write_string(0, 5, "sensor", MENU_NORMAL );
  
  lcdBlink(3, 200);
  
  // Captor part : logs in the serial monitor
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  dht.begin();
}


void loop() {
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(temp) || isnan(humi)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(humi);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(temp);
    Serial.println(" *C");
  }
  
  
  lcd.LCD_clear();
//  int raw = analogRead(8);
//  int temp = MULTIPLIER * (float) raw;
  char tempString[6] = "";
  char humiString[6] = "";
  
  sprintf(tempString,"%d",(int)temp);
  sprintf(humiString,"%d",(int)humi);
  
  lcd.LCD_write_string(
      0, 0, "+", MENU_NORMAL);
  lcd.LCD_write_string_big(
      6, 0, tempString, MENU_NORMAL);
  lcd.LCD_write_string(
      35, 1, "C", MENU_NORMAL);
  //unsigned char cloudbmp[] = {0x00,0x00,0x00,0x80,0x40,0x20,0x18,0x07,0x0C,0x10,0x60,0x80,0x00,0x00,0x00,
//0x00,0x00,0x06,0x0B,0x10,0x26,0x28,0x28,0x20,0x20,0x10,0x0F,0x00,0x00,0x00};
    //lcd.LCD_draw_bmp_pixel(24,24, cloudbmp, 15,15); //position de base / nom / taille
      
  lcd.LCD_write_string_big(
      40, 3, humiString, MENU_NORMAL);
  lcd.LCD_write_string(
      75, 4, "%", MENU_NORMAL);
  unsigned char cloudbmp[] = {0x00,0x00,0x00,0x80,0x40,0x20,0x18,0x07,0x0C,0x10,0x60,0x80,0x00,0x00,0x00,
0x00,0x00,0x06,0x0B,0x10,0x26,0x28,0x28,0x20,0x20,0x10,0x0F,0x00,0x00,0x00};
    lcd.LCD_draw_bmp_pixel(20,20, cloudbmp, 15,15); //position de base / nom / taille
  delay(2000);
}

void lcdBlink(int count, int delayMs) {
    for(int i=0; i< count; i++){
     lcd.LCD_backlight(1);
     delay(delayMs);
     lcd.LCD_backlight(0);     
     delay(delayMs);
   }
   lcd.LCD_backlight(1);
}
