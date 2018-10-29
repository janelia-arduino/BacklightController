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

  void setAllIrBacklightsOn();
  void setAllIrBacklightsOnAtPower(long power);
  void setAllIrBacklightsOff();
  size_t getIrBacklightChannelCount();
  void setIrBacklightOn(size_t ir_backlight_channel);
  void setIrBacklightOnAtPower(size_t ir_backlight_channel,
    long power);
  void setIrBacklightOff(size_t ir_backlight_channel);
  long getIrBacklightPowerWhenOn(size_t ir_backlight_channel);
  long getIrBacklightPower(size_t ir_backlight_channel);

  void setAllVisibleBacklightsOn();
  void setAllVisibleBacklightsOnAtPower(long power);
  void setAllVisibleBacklightsOff();
  size_t getVisibleBacklightChannelCount();
  void setVisibleBacklightOn(size_t visible_backlight_channel);
  void setVisibleBacklightOnAtPower(size_t visible_backlight_channel,
    long power);
  void setVisibleBacklightOff(size_t visible_backlight_channel);
  long getVisibleBacklightPowerWhenOn(size_t visible_backlight_channel);
  long getVisibleBacklightPower(size_t visible_backlight_channel);

  void setAllHighVoltagesOn();
  void setAllHighVoltagesOnAtPower(long power);
  void setAllHighVoltagesOff();
  size_t getHighVoltageChannelCount();
  void setHighVoltageOn(size_t high_voltage_channel);
  void setHighVoltageOnAtPower(size_t high_voltage_channel,
    long power);
  void setHighVoltageOff(size_t high_voltage_channel);
  long getHighVoltagePowerWhenOn(size_t high_voltage_channel);
  long getHighVoltagePower(size_t high_voltage_channel);

  void setAllLowVoltagesOn();
  void setAllLowVoltagesOnAtPower(long power);
  void setAllLowVoltagesOff();
  size_t getLowVoltageChannelCount();
  void setLowVoltageOn(size_t low_voltage_channel);
  void setLowVoltageOnAtPower(size_t low_voltage_channel,
    long power);
  void setLowVoltageOff(size_t low_voltage_channel);
  long getLowVoltagePowerWhenOn(size_t low_voltage_channel);
  long getLowVoltagePower(size_t low_voltage_channel);

protected:
  virtual void setChannelOnAtHighFrequency(size_t channel,
    long high_frequency_duty_cycle);

  size_t irBacklightToDigitalChannel(size_t ir_backlight_channel);
  uint32_t getIrBacklightDigitalChannels();
  size_t visibleBacklightToDigitalChannel(size_t visible_backlight_channel);
  uint32_t getVisibleBacklightDigitalChannels();
  size_t highVoltageToDigitalChannel(size_t high_voltage_channel);
  uint32_t getHighVoltageDigitalChannels();
  size_t lowVoltageToDigitalChannel(size_t low_voltage_channel);
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
  void setVisibleBacklightPowerMaxHandler(size_t visibl_backlight_channel);
  void setHighVoltagePowerMaxHandler(size_t high_voltage_channel);
  void setLowVoltagePowerMaxHandler(size_t low_voltage_channel);

  void setAllIrBacklightsOnAtPowerHandler();
  void setAllIrBacklightsOnHandler(modular_server::Pin * pin_ptr);
  void setAllIrBacklightsOffHandler(modular_server::Pin * pin_ptr);
  void setIrBacklightOnHandler();
  void setIrBacklightOnAtPowerHandler();
  void setIrBacklightOffHandler();
  void getIrBacklightPowersWhenOnHandler();
  void getIrBacklightPowersHandler();

  void setAllVisibleBacklightsOnAtPowerHandler();
  void setAllVisibleBacklightsOnHandler(modular_server::Pin * pin_ptr);
  void setAllVisibleBacklightsOffHandler(modular_server::Pin * pin_ptr);
  void setVisibleBacklightOnHandler();
  void setVisibleBacklightOnAtPowerHandler();
  void setVisibleBacklightOffHandler();
  void getVisibleBacklightPowersWhenOnHandler();
  void getVisibleBacklightPowersHandler();

  void setAllHighVoltagesOnAtPowerHandler();
  void setAllHighVoltagesOnHandler(modular_server::Pin * pin_ptr);
  void setAllHighVoltagesOffHandler(modular_server::Pin * pin_ptr);
  void setHighVoltageOnHandler();
  void setHighVoltageOnAtPowerHandler();
  void setHighVoltageOffHandler();
  void getHighVoltagePowersWhenOnHandler();
  void getHighVoltagePowersHandler();

  void setAllLowVoltagesOnAtPowerHandler();
  void setAllLowVoltagesOnHandler(modular_server::Pin * pin_ptr);
  void setAllLowVoltagesOffHandler(modular_server::Pin * pin_ptr);
  void setLowVoltageOnHandler();
  void setLowVoltageOnAtPowerHandler();
  void setLowVoltageOffHandler();
  void getLowVoltagePowersWhenOnHandler();
  void getLowVoltagePowersHandler();

};

#endif
