extern float PosZ;                          //Define external variaables
#define ZhomingSpeedInMMPerSec  10
#define ZmaxHomingDistanceInMM 115   // The axis is max 115 mm long so homing for a longer distance does not make sense
#define directionTowardHome 1        // Direction to move toward limit switch: 1 goes positive direction, -1 backward
boolean homez = false;
extern float currentPosZ;                           //Declare external variables for use in this part of the script


M2_EXTERN_LABEL(el_z_homing_success_label);
M2_EXTERN_LABEL(el_z_homing_fail_label);
M2_EXTERN_ALIGN(el_top);

void Home() {
refresh();
  PosZ = 115;                                   //Set the position to the homing position and home the steppers
  currentPosZ = 115;
  homez = stepperZ.moveToHomeInMillimeters(directionTowardHome, ZhomingSpeedInMMPerSec, ZmaxHomingDistanceInMM, LIMIT_SWITCH_Z_PIN);
  //delay(500);
  if (homez){
  m2_SetRoot(&el_z_homing_success_label);
  refresh();
  delay(1000);
  m2_SetRoot(&el_top);
  }
  else{
  m2_SetRoot(&el_z_homing_fail_label);
  refresh();
  delay(1000);
  m2_SetRoot(&el_top);
  }
}
