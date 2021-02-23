extern float currentPosZ;                           //Declare external variables for use in this part of the script
extern float PosZ;
extern float Feedrate;
extern boolean AllowedPosition;



void Setup_Stepper_Motors(){
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);                  // Set the enable pin as an output
  pinMode(LIMIT_SWITCH_Z_PIN, INPUT_PULLUP);
  
  stepperZ.connectToPins(MOTOR_Z_STEP_PIN, MOTOR_Z_DIR_PIN);        //Initialize the motors
  stepperZ.setStepsPerMillimeter(Zstepsmm);
  stepperZ.setAccelerationInMillimetersPerSecondPerSecond(Zmmss);

  digitalWrite(STEPPERS_ENABLE_PIN, LOW);                // Enable the steppers
  Serial.begin(250000);
}


void SetSteppersMovement() {                             //Function for moving the steppers around sinchronously
  //  Serial.println("Move Steppers Checked");           //For Development purposes
  float Zmove = 0;                               //This variable stores the direction vector towards which we want the XZ carriage to move

  //Serial.println("Absolute Check");
  //Scan the PosZ and calculate the distance between the desired position and the current position in each axis
  Zmove = PosZ - currentPosZ;                  //Store the value of the direction vector


  MoveSteppers(Zmove);
  currentPosZ = PosZ;
}

boolean PositionAllowed() {                                 //Check if the position to which the command tells the carriage to move is within the carriage range, and if so return true, otherwise return false

  if ( (0 <= PosZ) && ( PosZ <= ZaxisRange)) {    //If the desired position is whithin this range the movement is allowed
    //      Serial.println("Whithin range Abs");                                                        //For development purposes
    return true;

  }
  else {
    //      Serial.println("Out of range Abs");                           //For development purposes
    return false;

  }


}
