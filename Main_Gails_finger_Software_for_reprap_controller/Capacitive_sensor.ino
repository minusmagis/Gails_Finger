#include <CapacitiveSensor.h>

long capacitiveThreshold = 50;                                 //We initialize some variables that will be used later
int average = 0;
#define samples 20

int arrays[samples];
int nextIndex = 0;
int l = 0;
int m = 0;

/*
   This is a modified version from the CapitiveSense Library Demo Sketch by Paul Badger 2008. Modified By Minusmagis on 2019
   Uses a high value resistor e.g. 10 megohm between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
*/


CapacitiveSensor   cs_12_13 = CapacitiveSensor(12, 13);        // We first declare the sensing pins
                                                               // 10 megohm resistor between pins 12 & 13, pin 13 is sensor pin, add wire, foil

void capacitiveReset() {                                       // This function resets the capacitive sensor and it is used to calibrate the 0 value
  
  average = 0;
  for (int i = 0; i < samples; i++) {                          // We first set the entire array to 0
    arrays[i] = 0;
  }
  
   for (int h = 0; h < samples * 50; h++) {                    // We calibrate with 50 times the ammount of samples we will take for measuring
      long total1 =  cs_12_13.capacitiveSensor(100);           // For each loop we store the measured value within the variable total1
      arrays[nextIndex] =  total1;                             // We store the total1 value within the arrays array on its corresponding index
                                                               
      nextIndex = (nextIndex + 1) % samples;                   // Since each measurement will be performed "samples" ammount of times and then averaged we will store 
      m = nextIndex;                                           // each value within the array circularly
                                                               // I'm not particularly sure why this code works and I'm pretty sure it is utterly unoptimized but it works so I will not touch it
      for (int i = 0; i < samples; i++)                        // We add all obtained values
      {
         average = average + arrays[i];
      }
      average = average / samples;                             // Finally we average them with the number of samples
  }
  capacitiveThreshold = average + 30;                          // We set a threshold, the value can be modified at will so that it is more or less sensitive
  Serial.print("capacitive threshold = ");                     // We print it for debugging purposes
  Serial.println(capacitiveThreshold);
}

boolean capacitiveValue()                                      // This function measures the capacitive value and if it is greater than the specified threshold returns a 'true' value
{
  long total1 =  cs_12_13.capacitiveSensor(100);               // We measure the capacitive value
  arrays[nextIndex] =  total1;                                 // And we store it into an array
  
  nextIndex = (nextIndex + 1) % samples;                       //The "%" is the modulo operator. "a = b%c" gives you the remainder of dividing b by c
  m = nextIndex;                                               // I'm not particularly sure why this code works and I'm pretty sure it is utterly unoptimized but it works so I will not touch it
  for (int i = 0; i < samples; i++)                            // We add all obtained values
  {
    average = average + arrays[i];
  }
  average = average / samples;                                 // Finally we average them with the number of samples
   
  Serial.println(average);                                     // We print the average value for debugging purposes
   
  if (average > capacitiveThreshold) {                         // If the measured value is larger than the specified threshold we return a 1
    return 1;
  }
  else {                                                       // Otherwise we return a 0
    return 0;
  }
}
