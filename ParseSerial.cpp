#include "ParseSerial.h"

ParseSerial::ParseSerial(byte _numChars, char _startMarker, char _endMarker) {
  numChars = _numChars;
  startMarker = _startMarker;
  endMarker = _endMarker;
  receivedChars = new char[numChars];
}

bool ParseSerial::receiveWithMarkers(HardwareSerial* SerialPort) {
  static bool receiveInProgress = false;
  static byte index = 0;
  char receivedChar;

  while (SerialPort->available() > 0 && newData == false) {
    receivedChar = SerialPort->read();

    if (receiveInProgress) {
      if (receivedChar != endMarker) {
        receivedChars[index] = receivedChar;
        index++;
        if (index >= numChars) {
          index = numChars - 1;
        }
      } else {
        receivedChars[index] = '\0';
        receiveInProgress = false;
        index = 0;
        newData = true;
      }
    } else if (receivedChar == startMarker) {
      receiveInProgress = true;
    }
  }

  return newData;
}

String ParseSerial::getSerialValuesString(String str, char splitMarker) {
  int startIndex = str.lastIndexOf(splitMarker);
  String valueStr = str.substring(startIndex + 1);

  return valueStr;
}
