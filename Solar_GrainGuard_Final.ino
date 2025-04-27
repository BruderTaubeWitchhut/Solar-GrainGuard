  #include <DHT.h>
  #include <Servo.h>
  #include <SoftwareSerial.h>

  #define DHTPIN 4
  #define DHTTYPE DHT11

  char value;
  int Tx = 2;
  int Rx = 3;
  int h = 0;
  int temp = 0;
  int motorPin = 8;
  int servoPin = 6;
  Servo servo;
  bool isHumidityDoorOpen = false;
  bool isFanOn = false;

  DHT dht(DHTPIN, DHTTYPE);

  SoftwareSerial bluetooth(Tx, Rx);

  void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);
    pinMode(motorPin, OUTPUT);
    pinMode(servoPin, OUTPUT);
    servo.attach(servoPin);
    servo.write(45);
    dht.begin(); 
  }

  void loop() {
    delay(2000);

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    Serial.println("Humidity (%): ");
    Serial.println(humidity, 2);

    Serial.print("Temperature  (C): ");
    Serial.println(temperature, 2);

    
      if (bluetooth.available()) {
        
        value = bluetooth.read();
        Serial.println(value);
        if (value == "1") {
          Serial.println("Rice");
          h = 14;
          temp = 25;
        }
        
        if (value == "2") {
          Serial.println("Maize");
          h = 13;
          temp = 25;
        }
        
        if (value =="3") {
          Serial.println("Chickpea");
          h = 12;
          temp = 25;
        }
        
      }
    if (isnan(humidity) || isnan(temperature)) 
    {
      Serial.println("Failed to read from DHT sensor!");
    } 
    else
    {
        if (humidity > h)  //
        {   
          Serial.println("Humidity is high");
          servo.write(90);

          isHumidityDoorOpen = true;
        }
        if(isHumidityDoorOpen == true && humidity <= h) //
        {
          servo.write(45);
          Serial.println("Humidity is low");
          isHumidityDoorOpen = false;
        } 
        if (temperature > temp) //
        {
          digitalWrite(motorPin, HIGH);
          Serial.println("Temperature is high");
          isFanOn = true;
        }
        if (isFanOn == true && temperature <= temp) //
        {
            digitalWrite(motorPin, LOW);
            Serial.println("Temperature is low");
            isFanOn = false;
        }
    }
  }