float PosZ = 0;
float Feedrate = 5000;  //um/s
float currentPosZ = 115;                   //The values at which the servos naturally start
extern boolean homez;
extern char Command[];

M2_EXTERN_ALIGN(el_z_home_first);

void MovingCommand() {
  if (homez == 1) {
    if (PositionAllowed() == true) {
      SetSteppersMovement();
    }
    else {
    }
  }
  else {
    m2_SetRoot(&el_z_home_first);
  }
}
