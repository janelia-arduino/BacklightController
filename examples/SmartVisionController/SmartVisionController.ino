#include <SmartVisionController.h>


SmartVisionController dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
