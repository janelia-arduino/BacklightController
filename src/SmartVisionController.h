// ----------------------------------------------------------------------------
// SmartVisionController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SMART_VISION_CONTROLLER_H
#define SMART_VISION_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <Parent.h>

#include "SmartVisionController/Constants.h"


class SmartVisionController : public Parent
{
public:
  SmartVisionController();
  virtual void setup();

private:
  modular_server::Property properties_[smart_vision_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[smart_vision_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[smart_vision_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[smart_vision_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
