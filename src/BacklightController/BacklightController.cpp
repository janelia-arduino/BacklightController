// ----------------------------------------------------------------------------
// BacklightController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../BacklightController.h"


using namespace backlight_controller;

BacklightController::BacklightController()
{
}

void BacklightController::setup()
{
  // Parent Setup
  DigitalController::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Pin Setup
  pinMode(constants::enable_all_pin,OUTPUT);

  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    pinMode(constants::channel_pins[channel],OUTPUT);
  }

  // Pins

  // Add Hardware
  modular_server_.addHardware(constants::hardware_info,
    pins_);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & channel_count_property = modular_server_.property(digital_controller::constants::channel_count_property_name);
  channel_count_property.disableFunctors();
  channel_count_property.setDefaultValue(constants::channel_count);
  channel_count_property.setRange(constants::channel_count,constants::channel_count);
  channel_count_property.reenableFunctors();

  // Parameters

  setChannelCountHandler();

  // Functions
  modular_server::Function & enable_all_function = modular_server_.function(digital_controller::constants::enable_all_function_name);
  enable_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::enableAllHandler));

  modular_server::Function & disable_all_function = modular_server_.function(digital_controller::constants::disable_all_function_name);
  disable_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::disableAllHandler));


  // Callbacks
}

void BacklightController::enableAll()
{
  digitalWrite(constants::enable_all_pin,LOW);
  DigitalController::enableAll();
}

void BacklightController::disableAll()
{
  digitalWrite(constants::enable_all_pin,HIGH);
  DigitalController::disableAll();
}

void BacklightController::setChannelOnAtHighFrequency(size_t channel,
  long high_frequency_duty_cycle)
{
  analogWrite(constants::channel_pins[channel],high_frequency_duty_cycle);
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void BacklightController::enableAllHandler()
{
  enableAll();
}

void BacklightController::disableAllHandler()
{
  disableAll();
}
