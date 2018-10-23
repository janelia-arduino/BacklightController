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

  void setAllIrLightChannelsOn();
  void setAllIrLightChannelsOnAtPower(long power);
  void setAllIrLightChannelsOff();

protected:
  virtual void setChannelOnAtHighFrequency(size_t channel,
    long high_frequency_duty_cycle);

  size_t irLightChannelToDigitalChannel(size_t ir_light_channel);
  uint32_t getIrLightDigitalChannels();
  size_t visibleLightChannelToDigitalChannel(size_t visible_light_channel);
  uint32_t getVisibleLightDigitalChannels();
  size_t highPowerChannelToDigitalChannel(size_t high_power_channel);
  uint32_t getHighPowerDigitalChannels();
  size_t lowPowerChannelToDigitalChannel(size_t low_power_channel);
  uint32_t getLowPowerDigitalChannels();

private:
  modular_server::Pin pins_[backlight_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[backlight_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[backlight_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[backlight_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[backlight_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers
  void enableAllHandler(modular_server::Pin * pin_ptr);
  void disableAllHandler(modular_server::Pin * pin_ptr);
  void setAllIrChannelsOnHandler(modular_server::Pin * pin_ptr);
  void setAllIrChannelsOffHandler(modular_server::Pin * pin_ptr);

};

#endif
