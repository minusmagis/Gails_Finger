
/* 
 *  This is the software for controling the Gail's Finger Dip coater created by Martí Gibert Roca as a PhD student on ICMAB-CSIC  
 * 
 * To find all the 3d printer files and bill of materials as well as assembly instructions go to the following link: 
 * 
 * For more information contact: minusmagis@gmail.com
 * 
*/

// We include all the necessary libraries as well as the definitions file we have created
#include <SpeedyStepper.h>
#include "U8glib.h"
#include "M2tk.h"
#include "utility/m2ghu8g.h"
#include "Definitions.h"

// We need to declare the stepper class here because this way it propagates through all the Sketches and we do not get any errors
SpeedyStepper stepperZ;

// We set up both the Stepper and the LCD calling their respective setup loops
void setup() {
  Setup_Stepper_Motors();
  Setup_LCD();
}

// The loop mainly refreshes the LCD Screen. The instructions are called via interrupts so they do not need to be actively polled
void loop() {
  Refresh_LCD();
}


  
