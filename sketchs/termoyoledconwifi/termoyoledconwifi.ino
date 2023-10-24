#include <max6675.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "redcasaA2"; // Cambiado a tu SSID
const char* password = "nicaragua7001"; // Cambiado a tu contraseña
const char* serverAddress = "http://192.168.0.124:8000/en_vivo/"; // Tu dirección IP y ruta

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

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  
  Serial.println("Conectado a WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
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

    // Enviar datos a Django
    HTTPClient http;
    http.begin(serverAddress);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "nodo=" + String(nodo) + "&temperatura=" + String(temperatura);
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode == 200) {
      Serial.println("Datos enviados exitosamente a Django.");
    } else {
      Serial.print("Error al enviar datos a Django. Código de estado: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    delay(15000); // Esperar 15 segundos antes de la siguiente lectura
  }
}
