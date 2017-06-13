#ifndef Helper_h
#define Helper_h

#include "Arduino.h"

class Helper
{
  public:
    static int sensorCount;
    static boolean isValidNumber(String input);
    static int getSensorValue(int sensorId);
    static void activateSensorArray();
    static void deactivateSensorArray();
};
#endif
