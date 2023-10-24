#include <max6675.h>
#include <Wire.h>
#include "SSD1306Wire.h"

const int CLK_PIN = 18;
const int CS_PIN = 5;
const int MISO_PIN = 19;

MAX6675 thermocouple(CLK_PIN, CS_PIN, MISO_PIN);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
SSD1306Wire display(0x3C, SDA, SCL);

int nodo = 1; // Define el número de nodo
double temperatura = 0.0; // Variable para guardar la temperatura

void setup() {
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);

  if(!display.init()) {
    Serial.println(F("Error con la pantalla"));
    for(;;);
  }

  display.display();
  delay(2000);
  display.clear();
}

void loop() {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Termometro Digital");

  // Mostrar número de nodo
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 12, "Nodo: " + String(nodo));

  // Leer la temperatura del MAX6675
  temperatura = thermocouple.readCelsius();

  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 32, "Temp: " + String(temperatura) + " C");

  display.display();

  // Envío de datos por el puerto serial
  Serial.print("Nodo: "); 
  Serial.print(nodo);
  Serial.print(", Temperatura (desde variable): "); 
  Serial.print(temperatura);
  Serial.println(" C");

  delay(3000); // Esperar 1 segundo antes de la siguiente lectura
}
