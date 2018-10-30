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

  void setAllIrBacklightsOnAtPower(long power);
  void setAllIrBacklightsOn();
  void setAllIrBacklightsOff();
  size_t getIrBacklightCount();
  void setIrBacklightOn(size_t ir_backlight);
  void setIrBacklightOnAtPower(size_t ir_backlight,
    long power);
  void setIrBacklightOff(size_t ir_backlight);
  long getIrBacklightPowerWhenOn(size_t ir_backlight);
  long getIrBacklightPower(size_t ir_backlight);

  void setAllVisibleBacklightsOnAtPower(long power);
  void setAllVisibleBacklightsOn();
  void setAllVisibleBacklightsOff();
  size_t getVisibleBacklightCount();
  void setVisibleBacklightOn(size_t visible_backlight);
  void setVisibleBacklightOnAtPower(size_t visible_backlight,
    long power);
  void setVisibleBacklightOff(size_t visible_backlight);
  long getVisibleBacklightPowerWhenOn(size_t visible_backlight);
  long getVisibleBacklightPower(size_t visible_backlight);

  void setAllHighVoltagesOnAtPower(long power);
  void setAllHighVoltagesOn();
  void setAllHighVoltagesOff();
  size_t getHighVoltageCount();
  void setHighVoltageOn(size_t high_voltage);
  void setHighVoltageOnAtPower(size_t high_voltage,
    long power);
  void setHighVoltageOff(size_t high_voltage);
  long getHighVoltagePowerWhenOn(size_t high_voltage);
  long getHighVoltagePower(size_t high_voltage);

  void setAllLowVoltagesOnAtPower(long power);
  void setAllLowVoltagesOn();
  void setAllLowVoltagesOff();
  size_t getLowVoltageCount();
  void setLowVoltageOn(size_t low_voltage);
  void setLowVoltageOnAtPower(size_t low_voltage,
    long power);
  void setLowVoltageOff(size_t low_voltage);
  long getLowVoltagePowerWhenOn(size_t low_voltage);
  long getLowVoltagePower(size_t low_voltage);

protected:
  virtual void setChannelOnAtHighFrequency(size_t channel,
    long high_frequency_duty_cycle);

  size_t irBacklightToDigitalChannel(size_t ir_backlight);
  uint32_t getIrBacklightDigitalChannels();
  size_t visibleBacklightToDigitalChannel(size_t visible_backlight);
  uint32_t getVisibleBacklightDigitalChannels();
  size_t highVoltageToDigitalChannel(size_t high_voltage);
  uint32_t getHighVoltageDigitalChannels();
  size_t lowVoltageToDigitalChannel(size_t low_voltage);
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

  void setIrBacklightPowerMaxHandler(size_t ir_backlight);
  void setVisibleBacklightPowerMaxHandler(size_t visible_backlight);
  void setHighVoltagePowerMaxHandler(size_t high_voltage);
  void setLowVoltagePowerMaxHandler(size_t low_voltage);

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
