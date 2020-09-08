#include <SpeedyStepper.h>
#include "U8glib.h"
#include "M2tk.h"
#include "utility/m2ghu8g.h"
//#define debug 1
//#define debug2 1

U8GLIB_ST7920_128X64_4X u8g(17, 15, 16);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17

#define STEPPERS_ENABLE_PIN 8
#define MOTOR_Z_STEP_PIN 2
#define MOTOR_Z_DIR_PIN 5
#define LIMIT_SWITCH_Z_PIN 11
#define Zmmss 15 
#define ZaxisRange 115 
#define fastfeed 5000

extern const float Zstepsmm;


SpeedyStepper stepperZ;

M2_EXTERN_ALIGN(el_top);  // forward declaration of the top level element

M2tk m2(&el_top, m2_es_arduino_rotary_encoder, m2_eh_4bd, m2_gh_u8g_ffs);

void setup() {
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);                  // Set the enable pin as an output
  pinMode(LIMIT_SWITCH_Z_PIN, INPUT_PULLUP);
  
  stepperZ.connectToPins(MOTOR_Z_STEP_PIN, MOTOR_Z_DIR_PIN);        //Initialize the motors
  stepperZ.setStepsPerMillimeter(Zstepsmm);
  stepperZ.setAccelerationInMillimetersPerSecondPerSecond(Zmmss);

  digitalWrite(STEPPERS_ENABLE_PIN, LOW);                // Enable the steppers
  Serial.begin(250000);

  // Connect u8glib with m2tklib
  m2_SetU8g(u8g.getU8g(), m2_u8g_box_icon);

  // Assign u8g font to index 0
  m2.setFont(0, u8g_font_6x13);

  // Setup keys
  m2.setPin(M2_KEY_SELECT, 14);
  m2.setPin(M2_KEY_ROT_ENC_A, 10);
  m2.setPin(M2_KEY_ROT_ENC_B, 9);
  
}

void loop() {
  refresh();
}

void refresh(){
      m2.checkKey();
  if ( m2.handleKey() || newFrame() ) {
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );
  }
}

  
