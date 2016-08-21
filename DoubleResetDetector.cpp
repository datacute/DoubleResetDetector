/*
	FILE: 		DoubleResetDetector.cpp
	VERSION: 	0.0.1
	PURPOSE: 	Trigger configure mode by resetting Arduino twice.
	LICENCE:	GPL v3 (http://www.gnu.org/licenses/gpl.html)
 */

#include "DoubleResetDetector.h"
#define DEBUG_DOUBLERESETCONFIG

DoubleResetDetector::DoubleResetDetector(int timeout) {
	this->timeout = timeout*1000;
	fsMounted = false;
	doubleReset = false;
	waitingForDoubleReboot = false;
}

void DoubleResetDetector::detectDoubleReset() {
  fsMounted = SPIFFS.begin();
  detectDoubleReset(fsMounted);
}

void DoubleResetDetector::detectDoubleReset(bool mounted) {
  fsMounted = mounted;
  if (!fsMounted) return;
  // This file's existance means we were recently reset
  if (SPIFFS.exists("/booted")) {
    Serial.println("/booted already exists. Double reset detected.");
    if (!SPIFFS.remove("/booted")) {
      Serial.println("failed to remove /booted");
    } else {
      Serial.println("/booted removed");
    }
    doubleReset = true;
  } else {
    File bootedFile = SPIFFS.open("/booted", "w");
    if (!bootedFile) {
      Serial.println("failed to open config file for writing");
    } else {
      bootedFile.println("booted");
      bootedFile.close();
      Serial.println("/booted created to help detect a double reset.");
      waitingForDoubleReboot = true;
    }
    doubleReset = false;
  }
}

bool DoubleResetDetector::doubleResetDetected() {
	return doubleReset;
}

void DoubleResetDetector::loop() {
  if (waitingForDoubleReboot && millis() > timeout) stop();
}

void DoubleResetDetector::stop() {
  if (fsMounted && SPIFFS.exists("/booted")) {
    if (!SPIFFS.remove("/booted")) {
      Serial.println("failed to remove /booted");
    } else {
      Serial.println("/booted removed");
    }
  }
  waitingForDoubleReboot = false;
}
// EOF
