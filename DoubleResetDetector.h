/*
	FILE: 		DoubleResetDetector.h
	VERSION: 	0.0.1
	PURPOSE: 	Trigger configure mode by resetting Arduino twice.
	LICENCE:	GPL v3 (http://www.gnu.org/licenses/gpl.html)
 */

#ifndef DoubleResetDetector_H__
#define DoubleResetDetector_H__

#include <FS.h>

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DOUBLERESETDETECTOR_VERSION "0.0.1"

class DoubleResetDetector
{
public:
	DoubleResetDetector(int timeout);
	void detectDoubleReset();
	void detectDoubleReset(bool mounted);
	bool doubleResetDetected();
	void loop();
	void stop();
	
private:
	int timeout;
	bool waitingForDoubleReboot;
	bool doubleReset;
	bool fsMounted;
};
#endif // DoubleResetDetector_H__
