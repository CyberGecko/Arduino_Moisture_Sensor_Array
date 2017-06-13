#include "Arduino.h"
#include "Helper.h"
#include "ctype.h"

int SENSOR_RAW_MAXIMUM = 1023;
int SENSOR_RAW_MINIMUM = 0;

int sensorArrayTogglePin = 7;
int sensorPins[] = {0, 1, 2, 3, 4};

int Helper::sensorCount = 5;

boolean Helper::isValidNumber(String input)
{
  boolean isNumber = false;
  for(byte inputIndex = 0; inputIndex < input.length(); inputIndex++)
  {
    isNumber = isDigit(input.charAt(inputIndex)) || 
               input.charAt(inputIndex) == '+' || 
               input.charAt(inputIndex) == '.' || 
               input.charAt(inputIndex) == '-';
    if(!isNumber)
    {
      return false;
    }
  }
  return isNumber;
}

int Helper::getSensorValue(int sensorId)
{
  int rawValue = 0;

  rawValue = analogRead(sensorPins[sensorId + 1]);

  return map(rawValue, SENSOR_RAW_MINIMUM, SENSOR_RAW_MAXIMUM, 100, 0);
}

void Helper::activateSensorArray()
{
  digitalWrite(sensorArrayTogglePin, HIGH);
}

void Helper::deactivateSensorArray()
{
  digitalWrite(sensorArrayTogglePin, LOW);
}

