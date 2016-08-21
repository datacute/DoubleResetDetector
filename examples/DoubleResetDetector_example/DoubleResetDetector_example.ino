#include <FS.h>
#include <DoubleResetDetector.h>

// Number of seconds after reset during which a 
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

DoubleResetDetector drd(DRD_TIMEOUT);

bool fsMounted = false;

// The Double Reset Detector uses the SPIFFS.
// If you also wish to use SPIFFS in your code,
// then you can inform the Double Reset Detector
// that it has been mounted.
void initFS()
{
  Serial.println("Mounting FS...");

  fsMounted = SPIFFS.begin();
  if (fsMounted) {
    Serial.println("Mounted file system");
    drd.detectDoubleReset(fsMounted);

    // use SPIFFS in your own code here
    
  } else {
    Serial.println("Failed to mount FS");
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("DoubleResetDetector Example Program");
  Serial.println("-----------------------------------");

  initFS();

  if (drd.doubleResetDetected()) {
    Serial.println("Double Reset Detected");
  } else {
    Serial.println("No Double Reset Detected");
  }
}

void loop()
{
  // Call the double reset detector loop method every so often,
  // so that it can recognise when the timeout expires.
  // You can also call drd.stop() when you wish to no longer
  // consider the next reset as a double reset.
  drd.loop();
}

