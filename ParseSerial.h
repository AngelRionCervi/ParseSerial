#include <Arduino.h>

class ParseSerial {
public:
  char startMarker;
  char endMarker;
  char* receivedChars;
  bool newData = false;
  byte numChars;
public:
  ParseSerial(byte _numChars, char _startMarker = '<', char _endMarker = '>');
  bool receiveWithMarkers(HardwareSerial* SerialPort);
  static String getSerialValuesString(String str, char splitMarker);
};
