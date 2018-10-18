// ----------------------------------------------------------------------------
// BacklightController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef BACKLIGHT_CONTROLLER_H
#define BACKLIGHT_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <DigitalController.h>

#include "BacklightController/Constants.h"


class BacklightController : public DigitalController
{
public:
  BacklightController();
  virtual void setup();

  void enableAll();
  void disableAll();

protected:
  virtual void setChannelOnAtHighFrequency(size_t channel,
    long high_frequency_duty_cycle);

private:
  modular_server::Pin pins_[backlight_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[backlight_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[backlight_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[backlight_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[backlight_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers
  void enableAllHandler();
  void disableAllHandler();

};

#endif
