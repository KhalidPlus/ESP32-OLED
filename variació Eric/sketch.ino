#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Configuración de la pantalla ---
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

// --- Pines ---
#define PIN_BOTON 18

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int contador = 0;
bool estadoAnterior = HIGH;          // Con pull-up, reposo = HIGH
unsigned long ultimoRebote = 0;
const unsigned long TIEMPO_REBOTE = 50; // ms (antirrebote)

void mostrarContador() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Contador de pulsos");

  display.setTextSize(4);
  display.setCursor(30, 25);
  display.print(contador);

  display.display();
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOTON, INPUT);   // Pull-up externa de 10k

  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("Error: OLED no encontrada");
    while (true);
  }
  mostrarContador();
}

void loop() {
  bool estadoActual = digitalRead(PIN_BOTON);

  // Detecta flanco de bajada (pulsación) con antirrebote
  if (estadoAnterior == HIGH && estadoActual == LOW &&
      (millis() - ultimoRebote) > TIEMPO_REBOTE) {
    contador++;
    ultimoRebote = millis();
    Serial.print("Pulsaciones: ");
    Serial.println(contador);
    mostrarContador();
  }
  estadoAnterior = estadoActual;
}