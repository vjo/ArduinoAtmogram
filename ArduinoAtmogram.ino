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
  
  //LCD blink 3 times
  lcdBlink(3, 200);
  
  // Captor part : logs in the serial monitor
  Serial.begin(9600); 
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
  } 
  else {
    Serial.print("Humidity: "); 
    Serial.print(humi);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(temp);
    Serial.println(" *C");
  }
  
  lcd.LCD_clear();
  
  //int raw = analogRead(8);
  //int temp = MULTIPLIER * (float) raw;
  char tempString[6] = "";
  char humiString[6] = "";
  
  sprintf(tempString,"%d",(int)temp);
  sprintf(humiString,"%d",(int)humi);
  
  //draw a cloud    
  unsigned char sunnycloudbmp[] = 
  {
    0x00,0xE0,0x18,0x0C,0x0C,0x08,0x08,0xD0,0x20,0x10,0x08,0x08,0x08,0x10,0x10,0x30,0x10,0x20,0x24,0x44,0x48,0xB0,0x10,0x13,0x0C,0x08,0x08,0x1C,0x16,0x71,0xA0,0x10,0x18,0x08,0x00,
    0x00,0x71,0x9F,0x03,0x02,0x02,0x00,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x08,0x08,0x0F,0x08,0x88,0x88,0x90,0xF0,0x70,0xCC,0x0F,0x19,0x31,0x61,0x01,
    0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x02,0x02,0x01,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x03,0x04,0x04,0x0C,0x08,0x08,0x08,0x0C,0x07,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00
  };
  lcd.LCD_draw_bmp_pixel(40, 0, sunnycloudbmp, 35,20); //position de base / nom / taille
  
  //Display temp
  lcd.LCD_write_string(0, 1, "+", MENU_NORMAL);
  lcd.LCD_write_string_big(6, 0, tempString, MENU_NORMAL);
  lcd.LCD_write_string(30, 1, "C", MENU_NORMAL);
   
  //draw a drop 
  unsigned char dropbmp[] = 
    {
      0x00,0x00,0x00,0x80,0x40,0x20,0x18,0x07,0x0C,0x10,0x60,0x80,0x00,0x00,0x00,
      0x00,0x00,0x06,0x0B,0x10,0x26,0x28,0x28,0x20,0x20,0x10,0x0F,0x00,0x00,0x00
    };
  lcd.LCD_draw_bmp_pixel(32,4, dropbmp, 15,15); //position de base / nom / taille   
  
  //Display humidity
  lcd.LCD_write_string_big(50, 3, humiString, MENU_NORMAL);
  lcd.LCD_write_string(75, 4, "%", MENU_NORMAL);

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
