#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Configuración de la pantalla ---
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

// --- Pines ---
#define PIN_POT 34   // ADC1, solo entrada

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);   // 0 - 4095

  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("Error: OLED no encontrada");
    while (true);
  }
}

void loop() {
  int valorADC = analogRead(PIN_POT);                 // 0 - 4095
  int porcentaje = map(valorADC, 0, 4095, 0, 100);    // 0 - 100 %
  int anchoBarra = map(valorADC, 0, 4095, 0, 124);    // Barra de progreso

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("ADC: ");
  display.print(valorADC);

  display.setTextSize(3);
  display.setCursor(20, 20);
  display.print(porcentaje);
  display.print("%");

  // Barra de progreso
  display.drawRect(0, 52, 128, 10, SSD1306_WHITE);
  display.fillRect(2, 54, anchoBarra, 6, SSD1306_WHITE);

  display.display();

  Serial.printf("ADC: %d | %d%%\n", valorADC, porcentaje);
  delay(100);
}