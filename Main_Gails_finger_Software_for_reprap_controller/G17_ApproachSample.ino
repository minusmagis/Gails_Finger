extern float PosZ;
extern float Feedrate ;
extern float currentPosZ;                   //The values at which the servos naturally start
extern char Command[];


M2_EXTERN_ALIGN(el_z_home_first);
M2_EXTERN_LABEL(el_approach_success_label);
M2_EXTERN_LABEL(el_approach_fail_label);
M2_EXTERN_LABEL(el_z_homing_success_label);
M2_EXTERN_LABEL(el_z_homing_fail_label);
M2_EXTERN_ALIGN(el_top);

#define MeasuringInterval 1000              //Capacitance measurement interval in steps to prevent the movement from being too slow

extern float ZStepsPerSecond;
extern float ZStepsPerSecondPerSecond;
extern const float Zstepsmm ;                                       //Define the steps per mm of the z axis
extern const float ZspeedinMMs;                                     //Define the speed in mm/s for the z axis

extern boolean homez;


void ApproachSample() {
  if (homez == 1) {
    Refresh_LCD();
    Approach();
  }
  else {
    m2_SetRoot(&el_z_home_first);
  }
}

void Approach() {
  CapacitiveReset();
  if (Feedrate >= 1000) {
    Feedrate = 1000;
  }
  boolean sucAp = 0;
  long i = 0;
    unsigned int j = 0;
  int k = 0;
  long offsetHome = ((ZaxisRange - 5) - currentPosZ) * Zstepsmm;
  ZStepsPerSecond = Feedrate * Zstepsmm * ZspeedinMMs / 1000;
  long stepsZ = -currentPosZ * Zstepsmm;
  stepperZ.setSpeedInStepsPerSecond(ZStepsPerSecond);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(ZStepsPerSecondPerSecond);
  stepperZ.setupRelativeMoveInSteps(stepsZ);
  while (!stepperZ.motionComplete())
  {
    stepperZ.processMovement();
    i = stepperZ.getCurrentPositionInSteps();
//        j++;
    k++;
//        if (j > 300)
//        {
//          Serial.print("Approaching...");
//          Serial.println(i);
//          j = 0;
//        }

    if (k > MeasuringInterval) {
      k = 0;
      if (CapacitiveValue()) {
        sucAp = 1;
        m2_SetRoot(&el_approach_success_label);
        Refresh_LCD();
        delay(1000);
        m2_SetRoot(&el_top);
        break;
      }
    }
  }
#if defined debug
  Serial.println("Total Steps");
  Serial.println(i);
#endif
  currentPosZ = ZaxisRange + (i / Zstepsmm);
  if (sucAp == 0) {
    m2_SetRoot(&el_approach_fail_label);
    Refresh_LCD();
    delay(1000);
    m2_SetRoot(&el_top);
  }

}
