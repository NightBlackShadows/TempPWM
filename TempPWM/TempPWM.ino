/*     ---------------------------------------------------------
 *     |  Arduino Experimentation Kit Example Code             |
 *     |  CIRC-10 .: Temperature :. (TMP36 Temperature Sensor) |
 *     ---------------------------------------------------------
 *   
 *  A simple program to output the current temperature to the IDE's debug window 
 * 
 *  For more details on this circuit: http://tinyurl.com/c89tvd 
 */

//TMP36 Pin Variables
int temperaturePin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade 
                        //(500 mV offset) to make negative temperatures an option

// Initial Fan Speeds
int frontSpeed = 0;

// PWM Pins
int front_a = 5;
int front_b = 6;

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup()
{
  pinMode(front_a, OUTPUT);   //front 140mm
  pinMode(front_b, OUTPUT);   //front 140mm
  Serial.begin(9600);  //Start the serial connection with the copmuter
                       //to view the result open the serial monitor 
                       //last button beneath the file bar (looks like a box with an antenae)

  
}
 
void loop()                     // run over and over again
{
 float temperature = getVoltage(temperaturePin);  //getting the voltage reading from the temperature sensor
 temperature = (temperature - .5) * 100;          //converting from 10 mv per degree wit 500 mV offset
                                                  //to degrees ((volatge - 500mV) times 100)

 frontSpeed = 100 + ((temperature-15)*20);
                                                  
 // Serial output for debugging
 Serial.print("Front: "); Serial.println(frontSpeed);
 Serial.println();

 // Write the changes to the PWM pins
 analogWrite(front_a, frontSpeed);
 analogWrite(front_b, frontSpeed);
                                                  
 Serial.println(temperature);                     //printing the result
 delay(1000);                                     //waiting a second
}

/*
 * getVoltage() - returns the voltage on the analog input defined by
 * pin
 */
float getVoltage(int pin){
 return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}
