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

  void setAllIrBacklightsOnAtPower(double power);
  void setAllIrBacklightsOn();
  void setAllIrBacklightsOff();
  void toggleAllIrBacklights();
  size_t getIrBacklightCount();
  void setIrBacklightOn(size_t ir_backlight);
  void setIrBacklightOnAtPower(size_t ir_backlight,
    double power);
  void setIrBacklightOff(size_t ir_backlight);
  void toggleIrBacklight(size_t ir_backlight);
  double getIrBacklightPowerWhenOn(size_t ir_backlight);
  double getIrBacklightPower(size_t ir_backlight);

  void setAllVisibleBacklightsOnAtPower(double power);
  void setAllVisibleBacklightsOn();
  void setAllVisibleBacklightsOff();
  void toggleAllVisibleBacklights();
  size_t getVisibleBacklightCount();
  void setVisibleBacklightOn(size_t visible_backlight);
  void setVisibleBacklightOnAtPower(size_t visible_backlight,
    double power);
  void setVisibleBacklightOff(size_t visible_backlight);
  void toggleVisibleBacklight(size_t visible_backlight);
  double getVisibleBacklightPowerWhenOn(size_t visible_backlight);
  double getVisibleBacklightPower(size_t visible_backlight);

  void setAllHighVoltagesOnAtPower(double power);
  void setAllHighVoltagesOn();
  void setAllHighVoltagesOff();
  void toggleAllHighVoltages();
  size_t getHighVoltageCount();
  void setHighVoltageOn(size_t high_voltage);
  void setHighVoltageOnAtPower(size_t high_voltage,
    double power);
  void setHighVoltageOff(size_t high_voltage);
  void toggleHighVoltage(size_t high_voltage);
  double getHighVoltagePowerWhenOn(size_t high_voltage);
  double getHighVoltagePower(size_t high_voltage);

  void setAllLowVoltagesOnAtPower(double power);
  void setAllLowVoltagesOn();
  void setAllLowVoltagesOff();
  void toggleAllLowVoltages();
  size_t getLowVoltageCount();
  void setLowVoltageOn(size_t low_voltage);
  void setLowVoltageOnAtPower(size_t low_voltage,
    double power);
  void setLowVoltageOff(size_t low_voltage);
  void toggleLowVoltage(size_t low_voltage);
  double getLowVoltagePowerWhenOn(size_t low_voltage);
  double getLowVoltagePower(size_t low_voltage);

protected:
  virtual double getPowerLowerBound(size_t channel);
  virtual double getPowerUpperBound(size_t channel);
  virtual double setChannelToPower(size_t channel,
    double power);

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

  long channels_switching_frequency_max_[digital_controller::constants::CHANNEL_COUNT_MAX];

  void updateAllSwitchingFrequencies();

  void channelAnalogWrite(size_t channel,
    long value);

  long powerToAnalogValue(size_t channel,
    double power);

  // Handlers
  void enableAllHandler(modular_server::Pin * pin_ptr);
  void disableAllHandler(modular_server::Pin * pin_ptr);

  void setIrBacklightPowerMaxHandler(size_t ir_backlight);
  void setVisibleBacklightPowerMaxHandler(size_t visible_backlight);
  void setHighVoltagePowerMaxHandler(size_t high_voltage);
  void setLowVoltagePowerMaxHandler(size_t low_voltage);

  void setIrBacklightSwitchingFrequencyMaxHandler(size_t ir_backlight);
  void setVisibleBacklightSwitchingFrequencyMaxHandler(size_t visible_backlight);
  void setHighVoltageSwitchingFrequencyMaxHandler(size_t high_voltage);
  void setLowVoltageSwitchingFrequencyMaxHandler(size_t low_voltage);

  void setAllIrBacklightsOnAtPowerHandler();
  void setAllIrBacklightsOnHandler(modular_server::Pin * pin_ptr);
  void setAllIrBacklightsOffHandler(modular_server::Pin * pin_ptr);
  void toggleAllIrBacklightsHandler(modular_server::Pin * pin_ptr);
  void setIrBacklightOnHandler();
  void setIrBacklightOnAtPowerHandler();
  void setIrBacklightOffHandler();
  void toggleIrBacklightHandler();
  void getIrBacklightPowersWhenOnHandler();
  void getIrBacklightPowersHandler();
  void getIrBacklightPowerBoundsHandler();

  void setAllVisibleBacklightsOnAtPowerHandler();
  void setAllVisibleBacklightsOnHandler(modular_server::Pin * pin_ptr);
  void setAllVisibleBacklightsOffHandler(modular_server::Pin * pin_ptr);
  void toggleAllVisibleBacklightsHandler(modular_server::Pin * pin_ptr);
  void setVisibleBacklightOnHandler();
  void setVisibleBacklightOnAtPowerHandler();
  void setVisibleBacklightOffHandler();
  void toggleVisibleBacklightHandler();
  void getVisibleBacklightPowersWhenOnHandler();
  void getVisibleBacklightPowersHandler();
  void getVisibleBacklightPowerBoundsHandler();

  void setAllHighVoltagesOnAtPowerHandler();
  void setAllHighVoltagesOnHandler(modular_server::Pin * pin_ptr);
  void setAllHighVoltagesOffHandler(modular_server::Pin * pin_ptr);
  void toggleAllHighVoltagesHandler(modular_server::Pin * pin_ptr);
  void setHighVoltageOnHandler();
  void setHighVoltageOnAtPowerHandler();
  void setHighVoltageOffHandler();
  void toggleHighVoltageHandler();
  void getHighVoltagePowersWhenOnHandler();
  void getHighVoltagePowersHandler();
  void getHighVoltagePowerBoundsHandler();

  void setAllLowVoltagesOnAtPowerHandler();
  void setAllLowVoltagesOnHandler(modular_server::Pin * pin_ptr);
  void setAllLowVoltagesOffHandler(modular_server::Pin * pin_ptr);
  void toggleAllLowVoltagesHandler(modular_server::Pin * pin_ptr);
  void setLowVoltageOnHandler();
  void setLowVoltageOnAtPowerHandler();
  void setLowVoltageOffHandler();
  void toggleLowVoltageHandler();
  void getLowVoltagePowersWhenOnHandler();
  void getLowVoltagePowersHandler();
  void getLowVoltagePowerBoundsHandler();

};

#endif
