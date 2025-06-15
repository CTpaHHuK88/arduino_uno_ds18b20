#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Пин подключения датчика температуры
#define ONE_WIRE_BUS 5
// Настройка 1-Wire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Подключение TFT дисплея

#define TFT_CS    7
#define TFT_RST   8
#define TFT_DC    9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void updateDisplay(float value) {

  // Координаты и размер области вывода
  #define TEXT_X   5
  #define TEXT_Y   30
  #define TEXT_W   60  // Ширина области
  #define TEXT_H   20  // Высота области

  tft.fillRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ST77XX_BLACK);  // Закрашиваем старые данные
  tft.setCursor(TEXT_X, TEXT_Y);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print(value, 2);  // 2 знака после запятой
}

void setup() {
  Serial.begin(9600);
  sensors.begin(); // Инициализация датчика
// Инициализация дисплея (ST7735S)
  tft.initR(INITR_MINI160x80);  // Инициализация для 80x160
  tft.setRotation(3);           // Ориентация экрана
  tft.fillScreen(ST77XX_BLACK); // Очистка экрана
}

void loop() {
  sensors.requestTemperatures(); // Запрос температуры
  float tempC = sensors.getTempCByIndex(0); // Чтение для первого датчика
  updateDisplay(tempC);

  tft.fillRect(5, 10, TEXT_W, TEXT_H, ST77XX_BLACK);  // Закрашиваем старые данные
  tft.setCursor(5, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Temp \xF8""C:");
  delay(500);  // Задержка между обновлениями
}