#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define sensor A0

#define BLYNK_TEMPLATE_ID "TMPL3a0MYRmOw"
#define BLYNK_TEMPLATE_NAME "IoT Baby Smart Cradle"
#define BLYNK_AUTH_TOKEN "8HjBG3sF56c7DIjWoOVO-yw2_cEvvHkx"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "esp";
char pass[] = "wifi1234";

BlynkTimer timer;

#include <Servo.h>
int button = D0; //D2(gpio4)
int buttonState=0;
Servo myservo;
  int pos;
void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT);
 pinMode(button, INPUT_PULLUP);
  myservo.attach(D4);
   myservo.write(180);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("");

    Serial.println("  Searching WiFi ");  //transformer oil level indicator

    Serial.println("Network........X");
  }

  Serial.println("Connected WiFi   ");  //transformer oil level indicator

  Serial.println("X    Network   X");

  digitalWrite(2, HIGH);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.println("- starting client");
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  //Call the functions
  timer.setInterval(100L, ultrasonic);
}

//Get the ultrasonic sensor values
void ultrasonic() {
  int val = analogRead(sensor);
  float sensor = (val * (100.0 / 1023.0));
  Serial.print("Water level = ");
  Serial.println(sensor);
  Blynk.virtualWrite(V1, sensor);

  if (sensor > 70) {
    Blynk.logEvent("wetness_level","above to 50 %");
    for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      delay(15);           // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
      myservo.write(pos);                  // tell servo to go to position in variable 'pos'
      delay(15);                           // waits 15ms for the servo to reach the position
    }
  }
   
    
  buttonState=digitalRead(button); // put your main code here, to run repeatedly:
 if (buttonState == 1)
 {
   Blynk.logEvent("cry_detecting","swinging mechanism ON");
          
   for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      delay(15);           // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
      myservo.write(pos);                  // tell servo to go to position in variable 'pos'
      delay(15);                           // waits 15ms for the servo to reach the position
    }
 }

}
  void loop() {
  
    Blynk.run();  //Run the Blynk library
    timer.run();  //Run the Blynk timer
  }