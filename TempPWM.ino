#include <math.h>

// Initial Temp
int temperature = 0;

// Initial Fan Speeds
double topSpeed = 0;

// PWM Pins
int top_a = 5;
int top_b = 6;

double Thermister(int RawADC) {
  double Temp;
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp);

  Temp = Temp - 273.15; // Convert Kelvin to Celcius
  return Temp;
}

void setup() {
  pinMode(top_a, OUTPUT);   //PWM1
  pinMode(top_b, OUTPUT);   //PWM2
  Serial.begin(9600);
}
void loop() {
  temperature = Thermister(analogRead(0));
  Serial.print(temperature); //read pin A0
  Serial.println("c");
  
  topSpeed = 10 + ((temperature-15)*10);
  Serial.print((topSpeed/255)*100);
  Serial.print("% PWM signal\n");
  
  // Write the changes to the PWM pins
  analogWrite(top_a, topSpeed);
  analogWrite(top_b, topSpeed);
                                                  
  delay(1000); //waiting a second
}
