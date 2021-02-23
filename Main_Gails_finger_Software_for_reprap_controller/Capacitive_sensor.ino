/*
   This is a modified version from the CapitiveSense Library Demo Sketch by Paul Badger 2008. Modified By Minusmagis on 2019
   Uses a high value resistor e.g. 10 megohm between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
*/

// This script takes care of the sensing for the approach mecanism that automatically detects when the sample contacts the surface of the solvent via capacitive detection

// First we include the needed library
#include <CapacitiveSensor.h>

// We initialize the variables that will be used to decide when the sample contacts the whater
long CapacitiveThreshold = 50;                                // This variable will store the value at which we decide that the sample is in contact (It will be modified for calibrating purposes later so it can be any value)
int AverageCapacitiveValue = 0;                               // This variable will store the Average capacitive measured value 

#define Samples 20                                 // The ammount of samples that will be taken for calibration purposes

int MeasurementsArray[Samples];                     // This array will store the last "Samples" ammount of measurements so that we can average the last n measurements.
int nextIndex = 0;                                            // We create a variable that will store the next index to store the measurements ciclically within the array


CapacitiveSensor   Capacitive_Sensor = CapacitiveSensor(12, 13);        // We first declare the sensing pins
                                                                        // 10 megohm resistor between pins 12 & 13, pin 13 is sensor pin, add wire, foil

                                                               

void CapacitiveReset() {                                                                                // This function resets the capacitive sensor and it is used to calibrate the 0 value
  
  AverageCapacitiveValue = 0;                                                                           // We set the average to 0
  for (int i = 0; i < Samples; i++) {                                                                   // We set the entire array to 0
    MeasurementsArray[i] = 0;
  }
  
   for (int h = 0; h < Samples * 50; h++) {                                                             // We calibrate with 50 times the ammount of samples we will take for measuring
      long Measured_Value =  Capacitive_Sensor.capacitiveSensor(100);                                   // For each loop we store the measured value within the temporal variable Measured_Value
      MeasurementsArray[nextIndex] =  Measured_Value;                                                   // We store the Measured_Value value within the MeasurementsArray array on its corresponding index
                                                               
      nextIndex = (nextIndex + 1) % Samples;                                                            // Since each measurement will be performed "Samples" ammount of times and then averaged we will store 
                                                                                                        // each value within the array circularly
      for (int i = 0; i < Samples; i++)                                                                 // We add all obtained values
      {
         AverageCapacitiveValue = AverageCapacitiveValue + MeasurementsArray[i];
      }
      AverageCapacitiveValue = AverageCapacitiveValue / Samples;                                        // Finally we average them with the number of Samples
  }
  CapacitiveThreshold = AverageCapacitiveValue + 30;                                                    // We set a threshold, the value can be modified at will so that it is more or less sensitive
  Serial.print("capacitive threshold = ");                                                              // We print it for debugging purposes
  Serial.println(CapacitiveThreshold);
}

boolean CapacitiveValue()                                      // This function measures the capacitive value and if it is greater than the specified threshold returns a 'true' value
{
  long total1 =  Capacitive_Sensor.capacitiveSensor(100);               // We measure the capacitive value
  MeasurementsArray[nextIndex] =  total1;                                 // And we store it into an array
  
  nextIndex = (nextIndex + 1) % Samples;                       //The "%" is the modulo operator. "a = b%c" gives you the remainder of dividing b by c

  for (int i = 0; i < Samples; i++)                            // We add all obtained values
  {
    AverageCapacitiveValue = AverageCapacitiveValue + MeasurementsArray[i];
  }
  AverageCapacitiveValue = AverageCapacitiveValue / Samples;                                 // Finally we average them with the number of Samples
   
  Serial.println(AverageCapacitiveValue);                                     // We print the average value for debugging purposes
   
  if (AverageCapacitiveValue > CapacitiveThreshold) {                         // If the measured value is larger than the specified threshold we return a 1
    return 1;
  }
  else {                                                       // Otherwise we return a 0
    return 0;
  }
}
