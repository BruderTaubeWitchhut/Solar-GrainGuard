#include <DHT.h>
#include <Servo.h>

#define DHTPIN 4
#define DHTTYPE DHT11

int motorPin = 8;
int servoPin = 6;
Servo servo;
bool isHumidityDoorOpen = false;
bool isFanOn = false;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(servoPin, OUTPUT);  
  servo.attach(servoPin);
  servo.write(45);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Humidity (%): ");
  Serial.println(humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println(temperature, 2);

  if (isnan(humidity) || isnan(temperature)) 
  {
      Serial.println("Failed to read from DHT sensor!");
  } 
  else
  {
      if (humidity > 48.00)  //
      {   
        Serial.println("Humidity is high");
        servo.write(90);

        isHumidityDoorOpen = true;
      }
      if(isHumidityDoorOpen == true && humidity <= 48.00) //
      {
        servo.write(45);
        Serial.println("Humidity is low");
        isHumidityDoorOpen = false;
      } 
      if (temperature > 23.00) //
      {
        digitalWrite(motorPin, HIGH);
        Serial.println("Temperature is high");
        isFanOn = true;
      }
      if (isFanOn == true && temperature <= 23.00) //
      {
          digitalWrite(motorPin, LOW);
          Serial.println("Temperature is low");
          isFanOn = false;
      }
  }
}