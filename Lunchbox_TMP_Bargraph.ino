/*34567891123456789212345678931234567894123456789512345678961234567897123456789812345
Bargraph Thermometer. Based on the SparkFun Bar Graph Breakout Kit Library and the 
TMP36 circuit-7 for the SparkFun Inventors Kit
*/
//Inclusions
#include <SFEbarGraph.h>               // SFEbarGraph library available at
                                       // http://www.sparkfun.com/products/10936
#include <SPI.h>                       // Accesses the Serial Peripheral Interface 

//Declarations
SFEbarGraph Thermometer;               // Bargraph object
const int numBarGraphs = 1;            // Number of attached bargraphs
const int latchPin = 10;               // Latch Pin for Bargraph
const int tmpPin = 0;                  // Analog pin used to connect the TMP36

unsigned char pipr;                    // Variable to hold value from the analog pin

void setup()
{
  Thermometer.begin(latchPin,numBarGraphs);
                                       // Invoke the bargraph
  Serial.begin(9600);                  // Useful for debugging
  Thermometer.clear();
}

void loop()
{
  float temperature = (((getVoltage(tmpPin) - .5) * 100)*1.8)+32;  
                                       // Reads the converted voltage from the 
                                       // temperature sensor and Converts from 
                                       // 10 mv per degree C with 500 mV offset 
                                       // ((volatge - 500mV) times 100)
                                       // to degrees F (times (9/5)+32)
  pipr = map(temperature, 20, 110, 0, 30); 
                                       // Scale the temperature range (20F-110F) 
                                       // to the bargraph. 3 degrees per LED
  Serial.println(temperature);         // Send decimal temperature value 
                                       // to the Serial Monitor
  Thermometer.clear();                 // Clear the canvas

  Thermometer.paint(pipr,HIGH);        // Turn on one LED
  Thermometer.send();                  // Send the canvas to the display
  delay(50);                           // Block the code for 50ms
}

/* getVoltage() - 
returns a floating-point value for the voltage on the analog input defined by
the integer "pin".
Approximates a 10-bit digital reading to an analog voltage (0-5V).
each reading is about 5 millivolts.
 */
float getVoltage(int pin)
{
  return (analogRead(pin) * .004882814);
}
