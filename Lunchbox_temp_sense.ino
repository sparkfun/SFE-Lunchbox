/*345678911234567892123456789312345678941234567895123456789612345678971234567898123456789
Bargraph Thermometer. Based on the SparkFun Bargraph Breakout Sketch by Mike Grusin, and 
the TMP36 circuit-10 for the SparkFun Inventors Kit 
*/
//Inclusions
#include <SFEbarGraph.h> // this utilizes the SFEbarGraph library available at
                         // http://www.sparkfun.com/products/10936
#include <SPI.h>         // accesses the Serial Peripheral Interface on the ATMEGA 328

//Declarations
SFEbarGraph BG;          // Bargraph object
const int numbargraphs = 1;
int temperaturePin = A0; // analog pin used to connect the TMP36
unsigned char pipr;      // variable to read the value from the analog pin

//setup
void setup()
{
  BG.begin(10,numbargraphs);
                        // Latch Pin = 10, Number of Bargraphs = 1
  Serial.begin(9600);   // useful for debugging
}

//loop
void loop()
{
  float temperature = getVoltage(temperaturePin);  
                         //getting the voltage reading from the temperature sensor
  temperature = (((temperature - .5) * 100)*1.8)+32;          
                         //converting from 10 mv per degree wit 500 mV offset
                         //to degrees ((volatge - 500mV) times 100)
  pipr = map(temperature, 20, 110, 0, 30); 
                         // scale the temperature range (20F-110F) 
                         //to the bargraph. 3 degrees per LED
  Serial.println(temperature);
                         // Read back the actual decimal value of the temperature
  BG.clear();            // Clear the canvas

  BG.paint(pipr,HIGH);   // Turn on one LED
  BG.send();             // Send the canvas to the display
  delay(50);             // Pause a moment (decrease delay to increase speed!)
}

/* getVoltage() - returns the voltage on the analog input defined by "pin"
 *
 */
float getVoltage(int pin){
 return (analogRead(pin) * .004882814); 
                         //converting from a 0 to 1024 digital range
                         // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}


