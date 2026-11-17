#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Configuración de la pantalla ---
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

// --- Pines ---
#define PIN_LED 19

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool ledEncendido = false;
unsigned long ultimoCambio = 0;
const unsigned long INTERVALO = 1000; // ms entre cambios

void mostrarEstado() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Control de LED");

  display.setTextSize(2);
  display.setCursor(10, 30);
  display.print(ledEncendido ? "ACTIVADO" : "DESACTIV.");

  display.display();
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("Error: OLED no encontrada");
    while (true);
  }
  mostrarEstado();
}

void loop() {
  // Alterna el LED sin bloquear el programa (millis en lugar de delay)
  if (millis() - ultimoCambio >= INTERVALO) {
    ultimoCambio = millis();
    ledEncendido = !ledEncendido;
    digitalWrite(PIN_LED, ledEncendido);
    Serial.println(ledEncendido ? "LED: ACTIVADO" : "LED: DESACTIVADO");
    mostrarEstado();
  }
}