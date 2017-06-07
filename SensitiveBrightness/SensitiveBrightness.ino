/*
 Sketch que roda na lembrança oferecida aos palestrantes do Acontece Educação,
 realizado na Escola Eleva em parceria com o CESAR em 08/07/2017

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.

 In other words, in this simple example the LED's just get brighter in the dark.
 
 Also prints the results to the serial monitor, for debugging purposes.

 The circuit:
 * 01 LDR connected to analog pin 1.
 * 04 LEDs connected from digital PWM pins 5, 6, 10 and 11 to ground

 Based on Analog input, analog output, serial output
 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe
 
 modified 7 Jun. 2017
 by Rodrigo Rodrigues da Silva <rodrigo.silva@escolaeleva.com.br>

 This code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used and standard constant values:

#define LDR A1  // Analog input pin that the light sensor (LDR) is attached to

// output pins connected to LED's. Please notice that they are all PWM pins, which means
// we can output values from 0 to 255 that are converted to a range between 0 and 5V (instead of 0 or 5V digital values)
#define LED0 11
#define LED1 10
#define LED2 6
#define LED3 5

const int sensor_min = 250;  // lower boundary for sensor value mapping
const int sensor_max = 850; // upper boundary for sensor value mapping
const int bright_min = 0;    // min bright value. reduce it to get less brightness in light
const int bright_max = 255;  // max bright value. increase it to get more brightness in dark

int sensorValue = 0;         // value read from the light sensor
int brightness = 0;          // initial brightness value
int _delay = 2;              // default delay value

void setup() {
  // here we initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // here we set pins (named above) for output.
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {

  // wait for ADC (analog digital converter) to initialize
  delay(_delay);

  // read value from sensor and update brightness for all LEDs at once
  updateSensor();

  // change the analog out value:
  analogWrite(LED3, brightness);
  analogWrite(LED2, brightness);
  analogWrite(LED1, brightness);
  analogWrite(LED0, brightness);
}

/*
 * This function reads a value from  LDR (at pin A1) and maps it to delay and brightness values
 */
void updateSensor() {
  // read the analog in value:
  sensorValue = analogRead(LDR);

  // map it to the range of the analog out:
  brightness = constrain(map(sensorValue, sensor_min, sensor_max, bright_max, bright_min), bright_min, bright_max);

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t brightness = ");
  Serial.print(brightness);
  Serial.print("\t delay = ");
  Serial.println(_delay);
}
