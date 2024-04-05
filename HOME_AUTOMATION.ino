#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define led1 D5
#define led2 D6
#define led3 D7
#define led4 D8

void setup() {
  Serial.begin(115200);
  WiFi.softAP("Vermaji", "12345678");
  Serial.println();
  Serial.println("NodeMCU Started");
  Serial.println(WiFi.softAPIP());
  server.begin();
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
}

void loop() {
  client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    request.trim();

    if (request.startsWith("GET /LEDON1")) {
      digitalWrite(led1, HIGH);
    } else if (request.startsWith("GET /LEDOFF1")) {
      digitalWrite(led1, LOW);
    } else if (request.startsWith("GET /LEDON2")) {
      digitalWrite(led2, HIGH);
    } else if (request.startsWith("GET /LEDOFF2")) {
      digitalWrite(led2, LOW);
    } else if (request.startsWith("GET /LEDON3")) {
      digitalWrite(led3, HIGH);
    } else if (request.startsWith("GET /LEDOFF3")) {
      digitalWrite(led3, LOW);
    } else if (request.startsWith("GET /LEDON4")) {
      digitalWrite(led4, HIGH);
    } else if (request.startsWith("GET /LEDOFF4")) {
      digitalWrite(led4, LOW);
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<html><body style='background-image: url(\"https://example.com/your-image.jpg\"); background-size: cover;'>");
    client.println("<div style='text-align: center;'>");
    client.println("<h1>Avaneesh Tutorial</h1>");
    client.println("<h3>Home Automation</h3>");

    // Style for the buttons with hover effect using JavaScript
    String buttonStyleOn = "style='background-color: #4CAF50; color: white; padding: 10px 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;'";
    String buttonStyleOff = "style='background-color: #FF0000; color: white; padding: 10px 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;' onmouseover='changeButtonColor(this)' onmouseout='resetButtonColor(this)'";

    client.println("<style>");
    client.println("  .hover-color { background-color: #00FFFF; }");
    client.println("</style>");

    client.println("<script>");
    client.println("  function changeButtonColor(button) { button.classList.add('hover-color'); }");
    client.println("  function resetButtonColor(button) { button.classList.remove('hover-color'); }");
    client.println("</script>");

    // Button 1
    client.println("<form action='/LEDON1' method='get'><button " + buttonStyleOn + ">Turn On</button></form>");
    client.println("<form action='/LEDOFF1' method='get'><button " + buttonStyleOff + ">Turn Off</button></form>");

    // Button 2
    client.println("<form action='/LEDON2' method='get'><button " + buttonStyleOn + ">Turn On</button></form>");
    client.println("<form action='/LEDOFF2' method='get'><button " + buttonStyleOff + ">Turn Off</button></form>");

    // Button 3
    client.println("<form action='/LEDON3' method='get'><button " + buttonStyleOn + ">Turn On</button></form>");
    client.println("<form action='/LEDOFF3' method='get'><button " + buttonStyleOff + ">Turn Off</button></form>");

    // Button 4
    client.println("<form action='/LEDON4' method='get'><button " + buttonStyleOn + ">Turn On</button></form>");
    client.println("<form action='/LEDOFF4' method='get'><button " + buttonStyleOff + ">Turn Off</button></form>");

    client.println("</div>");  // Close the center-align div
    client.println("</body></html>");

    delay(1);
    client.stop();
  }
}
