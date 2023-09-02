#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "PotatoChipishipss";
const char* password = "paba1234";

// Define motor control pins for Motor 1
#define MOTOR_1_PIN_1 D1
#define MOTOR_1_PIN_2 D2
#define ENABLE_1_PIN D5 // GPIO5 (D1) for motor 1 speed control

// Define motor control pins for Motor 2
#define MOTOR_2_PIN_1 D3
#define MOTOR_2_PIN_2 D4
#define ENABLE_2_PIN D6 // GPIO4 (D2) for motor 2 speed control

ESP8266WebServer server(80);

void setup() {
  pinMode(MOTOR_1_PIN_1, OUTPUT);
  pinMode(MOTOR_1_PIN_2, OUTPUT);
  pinMode(ENABLE_1_PIN, OUTPUT);
  
  pinMode(MOTOR_2_PIN_1, OUTPUT);
  pinMode(MOTOR_2_PIN_2, OUTPUT);
  pinMode(ENABLE_2_PIN, OUTPUT);
  
  analogWrite(ENABLE_1_PIN, 255);
  analogWrite(ENABLE_2_PIN, 255);

  Serial.begin(115200);
  Serial.println();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Define web server routes
  server.on("/", HTTP_GET, []() {
    String html = "<html><head>";
html += "<style>";
html += "table {";
html += "  border-collapse: collapse;";
html += "}";
html += "td {";
html += "  padding: 10px;";
html += "}";
html += ".centered {";
html += "  display: flex;";
html += "  justify-content: center;";
html += "  align-items: center;";
html += "  height: 200vh;";
html += "}";
html += "button {";
html += "  background-color: blue;";
html += "  color: white;";
html += "  border: none;";
html += "  padding: 10px;";
html += "  cursor: pointer;";
html += "}";
html += "</style>";
html += "</head><body>";
html += "<h1>WiFi Robot Control</h1>";
html += "<div class='centered'>";
html += "<table>";
html += "<tr>";
html += "<td></td>";
html += "<td><button id='backward' onclick='sendCommand(\"forward\")'>Forward</button></td>";
html += "<td></td>";
html += "</tr>";
html += "<tr>";
html += "<td><button id='left' onclick='sendCommand(\"left\")'>Left</button></td>";
html += "<td><button id='stop' onclick='sendCommand(\"stop\")'>Stop</button></td>";
html += "<td><button id='right' onclick='sendCommand(\"right\")'>Right</button></td>";
html += "</tr>";
html += "<tr>";
html += "<td></td>";
html += "<td><button id='forward' onclick='sendCommand(\"backward\")'>Backward</button></td>";
html += "<td></td>";
html += "</tr>";
html += "</table>";
html += "</div>";
html += "<script>";
html += "function sendCommand(cmd) {";
html += "  var xhr = new XMLHttpRequest();";
html += "  xhr.open('GET', '/action?cmd=' + cmd, true);";
html += "  xhr.send();";
html += "}";
html += "</script>";
html += "</body></html>";

    server.send(200, "text/html", html);
  });

  server.on("/action", HTTP_GET, []() {
    String cmd = server.arg("cmd");
    Serial.print("Received command: ");
  Serial.println(cmd);
    if (cmd == "forward") {
      Serial.println("Forward");
      digitalWrite(MOTOR_1_PIN_1, LOW);
      digitalWrite(MOTOR_1_PIN_2, HIGH);
      digitalWrite(MOTOR_2_PIN_1, LOW);
      digitalWrite(MOTOR_2_PIN_2, HIGH);
      delay(200);
      digitalWrite(MOTOR_1_PIN_1, LOW);
      digitalWrite(MOTOR_1_PIN_2, LOW);
      digitalWrite(MOTOR_2_PIN_1, LOW);
      digitalWrite(MOTOR_2_PIN_2, LOW);
    } else if (cmd == "backward") {
      Serial.println("Backward");
      digitalWrite(MOTOR_1_PIN_1, HIGH);
    digitalWrite(MOTOR_1_PIN_2, LOW);
    digitalWrite(MOTOR_2_PIN_1, HIGH);
    digitalWrite(MOTOR_2_PIN_2, LOW);
    delay(200);
      digitalWrite(MOTOR_1_PIN_1, LOW);
      digitalWrite(MOTOR_1_PIN_2, LOW);
      digitalWrite(MOTOR_2_PIN_1, LOW);
      digitalWrite(MOTOR_2_PIN_2, LOW);
    } else if (cmd == "left") {
      Serial.println("Left");
      digitalWrite(MOTOR_1_PIN_1, HIGH);
    digitalWrite(MOTOR_1_PIN_2, LOW);
    digitalWrite(MOTOR_2_PIN_1, LOW);
    digitalWrite(MOTOR_2_PIN_2, HIGH);
    delay(200);
      digitalWrite(MOTOR_1_PIN_1, LOW);
      digitalWrite(MOTOR_1_PIN_2, LOW);
      digitalWrite(MOTOR_2_PIN_1, LOW);
      digitalWrite(MOTOR_2_PIN_2, LOW);
    } else if (cmd == "right") {
      Serial.println("Right");
      digitalWrite(MOTOR_1_PIN_1, LOW);
    digitalWrite(MOTOR_1_PIN_2, HIGH);
    digitalWrite(MOTOR_2_PIN_1, HIGH);
    digitalWrite(MOTOR_2_PIN_2, LOW);
    delay(200);
      digitalWrite(MOTOR_1_PIN_1, LOW);
      digitalWrite(MOTOR_1_PIN_2, LOW);
      digitalWrite(MOTOR_2_PIN_1, LOW);
      digitalWrite(MOTOR_2_PIN_2, LOW);
    } else if (cmd == "stop") {
      Serial.println("Stop");
      digitalWrite(MOTOR_1_PIN_1, LOW);
      digitalWrite(MOTOR_1_PIN_2, LOW);
      digitalWrite(MOTOR_2_PIN_1, LOW);
      digitalWrite(MOTOR_2_PIN_2, LOW);
    }
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient();
  // Add any additional robot control logic here based on button presses
}
