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

  void setAllIrBacklightChannelsOn();
  void setAllIrBacklightChannelsOnAtPower(long power);
  void setAllIrBacklightChannelsOff();
  void setIrBacklightChannelOn(size_t ir_backlight_channel);
  void setIrBacklightChannelOnAtPower(size_t ir_backlight_channel,
    long power);
  void setIrBacklightChannelOff(size_t ir_backlight_channel);

  void setAllVisibleBacklightChannelsOn();
  void setAllVisibleBacklightChannelsOnAtPower(long power);
  void setAllVisibleBacklightChannelsOff();
  void setVisibleBacklightChannelOn(size_t visible_backlight_channel);
  void setVisibleBacklightChannelOnAtPower(size_t visible_backlight_channel,
    long power);
  void setVisibleBacklightChannelOff(size_t visible_backlight_channel);

  void setAllHighVoltageChannelsOn();
  void setAllHighVoltageChannelsOnAtPower(long power);
  void setAllHighVoltageChannelsOff();
  void setHighVoltageChannelOn(size_t high_voltage_channel);
  void setHighVoltageChannelOnAtPower(size_t high_voltage_channel,
    long power);
  void setHighVoltageChannelOff(size_t high_voltage_channel);

  void setAllLowVoltageChannelsOn();
  void setAllLowVoltageChannelsOnAtPower(long power);
  void setAllLowVoltageChannelsOff();
  void setLowVoltageChannelOn(size_t low_voltage_channel);
  void setLowVoltageChannelOnAtPower(size_t low_voltage_channel,
    long power);
  void setLowVoltageChannelOff(size_t low_voltage_channel);

protected:
  virtual void setChannelOnAtHighFrequency(size_t channel,
    long high_frequency_duty_cycle);

  size_t irBacklightChannelToDigitalChannel(size_t ir_backlight_channel);
  uint32_t getIrBacklightDigitalChannels();
  size_t visibleBacklightChannelToDigitalChannel(size_t visible_backlight_channel);
  uint32_t getVisibleBacklightDigitalChannels();
  size_t highVoltageChannelToDigitalChannel(size_t high_voltage_channel);
  uint32_t getHighVoltageDigitalChannels();
  size_t lowVoltageChannelToDigitalChannel(size_t low_voltage_channel);
  uint32_t getLowVoltageDigitalChannels();

private:
  modular_server::Pin pins_[backlight_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[backlight_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[backlight_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[backlight_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[backlight_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers
  void enableAllHandler(modular_server::Pin * pin_ptr);
  void disableAllHandler(modular_server::Pin * pin_ptr);

  void setIrBacklightPowerMaxHandler(size_t ir_backlight_channel);
  void setVisibleBacklightPowerMaxHandler(size_t channel);
  void setHighVoltagePowerMaxHandler(size_t channel);
  void setLowVoltagePowerMaxHandler(size_t channel);

  void setAllIrBacklightChannelsOnAtPowerHandler();
  void setAllIrBacklightChannelsOnHandler(modular_server::Pin * pin_ptr);
  void setAllIrBacklightChannelsOffHandler(modular_server::Pin * pin_ptr);
  void setIrBacklightChannelOnHandler();
  void setIrBacklightChannelOnAtPowerHandler();
  void setIrBacklightChannelOffHandler();

  void setAllVisibleBacklightChannelsOnAtPowerHandler();
  void setAllVisibleBacklightChannelsOnHandler(modular_server::Pin * pin_ptr);
  void setAllVisibleBacklightChannelsOffHandler(modular_server::Pin * pin_ptr);
  void setVisibleBacklightChannelOnHandler();
  void setVisibleBacklightChannelOnAtPowerHandler();
  void setVisibleBacklightChannelOffHandler();

  void setAllHighVoltageChannelsOnAtPowerHandler();
  void setAllHighVoltageChannelsOnHandler(modular_server::Pin * pin_ptr);
  void setAllHighVoltageChannelsOffHandler(modular_server::Pin * pin_ptr);
  void setHighVoltageChannelOnHandler();
  void setHighVoltageChannelOnAtPowerHandler();
  void setHighVoltageChannelOffHandler();

  void setAllLowVoltageChannelsOnAtPowerHandler();
  void setAllLowVoltageChannelsOnHandler(modular_server::Pin * pin_ptr);
  void setAllLowVoltageChannelsOffHandler(modular_server::Pin * pin_ptr);
  void setLowVoltageChannelOnHandler();
  void setLowVoltageChannelOnAtPowerHandler();
  void setLowVoltageChannelOffHandler();

};

#endif
