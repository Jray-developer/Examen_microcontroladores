#include <ESP8266WiFi.h>          
#include <ESP8266WebServer.h>     

const char* ssid = "POCO X6";
const char* password = "20202020";

const int pinPotenciometro = A0;  
const int pinLED = 5;  

int valorDigital = 0;
int nivel = 1;
int tiempoEspera = 0;

int umbral = 0; 

ESP8266WebServer server(80);

String paginaWeb() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'></head><body style='font-family:Arial; text-align:center;'>";
  html += "<h1>Control de Umbral con Potenciómetro</h1>";
  html += "<h2>Valor Físico (Potenciómetro): <span id='valDigital'>0</span></h2>";
  html += "<h2>Umbral Configurado: <span id='valUmbral'>0</span></h2>";
  html += "<h2>Nivel Actual: <span id='valNivel'>1</span> de 5</h2>";
  
  html += "<div style='margin-top:20px; border:1px solid #ccc; padding:15px; display:inline-block; border-radius:8px;'>";
  html += "  <h3>Configurar Umbral Mínimo (0 a 1023):</h3>";
  html += "  <input type='number' id='inputUmbral' min='0' max='1023' placeholder='Ej: 400' style='padding:8px; font-size:16px; width:100px;'>";
  html += "  <button onclick='enviarUmbral()' style='padding:8px 15px; font-size:16px; margin-left:10px;'>Definir Umbral</button>";
  html += "</div>";

  html += "<script>";
  html += "function enviarUmbral() {";
  html += "  var u = document.getElementById('inputUmbral').value;";
  html += "  if(u >= 0 && u <= 1023 && u !== '') {";
  html += "    fetch('/setUmbral?u=' + u);";
  html += "  } else { alert('Ingresa un número entre 0 y 1023'); }";
  html += "}";

  html += "function actualizar(){";
  html += "  fetch('/valor').then(r => r.text()).then(texto => {";
  html += "    var datos = texto.split(',');"; 
  html += "    document.getElementById('valDigital').innerHTML = datos[0];";
  html += "    document.getElementById('valNivel').innerHTML = datos[1];";
  html += "    document.getElementById('valUmbral').innerHTML = datos[2];"; // Tercer dato
  html += "  });";
  html += "}";
  html += "setInterval(actualizar, 500);";
  html += "</script>";
  
  html += "</body></html>";
  return html;
}

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n¡Conectado!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP()); 

  server.on("/", [](){
    server.send(200, "text/html", paginaWeb());
  });

  server.on("/valor", [](){
    String respuesta = String(valorDigital) + "," + String(nivel) + "," + String(umbral);
    server.send(200, "text/plain", respuesta);
  });

  server.on("/setUmbral", [](){
    if (server.hasArg("u")) {
      umbral = server.arg("u").toInt(); 
    }
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient(); 

  valorDigital = analogRead(pinPotenciometro);
  
  if (valorDigital < umbral) {
    nivel = 1; 
  } 
  else {
    nivel = map(valorDigital, umbral, 1023, 1, 5);
  }

  if (nivel == 1) {
    digitalWrite(pinLED, LOW);
    delay(10); 
  } 
  else {
    if (nivel == 2) t
    
    iempoEspera = 40; 
    if (nivel == 3) tiempoEspera = 20; 
    if (nivel == 4) tiempoEspera = 8;  
    if (nivel == 5) tiempoEspera = 3;  

    digitalWrite(pinLED, HIGH);
    for(int i = 0; i < tiempoEspera; i++) { 
      server.handleClient(); 
      delay(10); 
    }
    
    digitalWrite(pinLED, LOW);
    for(int i = 0; i < tiempoEspera; i++) { 
      server.handleClient(); 
      delay(10); 
    }
  }
}