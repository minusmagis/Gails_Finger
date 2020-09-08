unsigned long previousMillis = 0;        // will store last time LED was updated
M2_EXTERN_ALIGN(el_top);

// constants won't change:
#define interval 1000           // interval at which to blink (milliseconds)

boolean newFrame()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    return true;
  }
  else {
    return false;
  }
}
