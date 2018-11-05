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
  modular_server::Pin & btn_a_pin = modular_server_.pin(modular_device_base::constants::btn_a_pin_name);

  modular_server::Pin & btn_b_pin = modular_server_.pin(modular_device_base::constants::btn_b_pin_name);

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

  modular_server::Property & ir_backlight_power_max_property = modular_server_.createProperty(constants::ir_backlight_power_max_property_name,constants::ir_backlight_power_max_default);
  ir_backlight_power_max_property.setRange(digital_controller::constants::power_min,digital_controller::constants::power_max);
  ir_backlight_power_max_property.setUnits(digital_controller::constants::percent_units);
  ir_backlight_power_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&BacklightController::setIrBacklightPowerMaxHandler));

  modular_server::Property & visible_backlight_power_max_property = modular_server_.createProperty(constants::visible_backlight_power_max_property_name,constants::visible_backlight_power_max_default);
  visible_backlight_power_max_property.setRange(digital_controller::constants::power_min,digital_controller::constants::power_max);
  visible_backlight_power_max_property.setUnits(digital_controller::constants::percent_units);
  visible_backlight_power_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&BacklightController::setVisibleBacklightPowerMaxHandler));

  modular_server::Property & high_voltage_power_max_property = modular_server_.createProperty(constants::high_voltage_power_max_property_name,constants::high_voltage_power_max_default);
  high_voltage_power_max_property.setRange(digital_controller::constants::power_min,digital_controller::constants::power_max);
  high_voltage_power_max_property.setUnits(digital_controller::constants::percent_units);
  high_voltage_power_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&BacklightController::setHighVoltagePowerMaxHandler));

  modular_server::Property & low_voltage_power_max_property = modular_server_.createProperty(constants::low_voltage_power_max_property_name,constants::low_voltage_power_max_default);
  low_voltage_power_max_property.setRange(digital_controller::constants::power_max,digital_controller::constants::power_max);
  low_voltage_power_max_property.setUnits(digital_controller::constants::percent_units);
  low_voltage_power_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&BacklightController::setLowVoltagePowerMaxHandler));

  // Parameters
  modular_server::Parameter & power_parameter = modular_server_.parameter(digital_controller::constants::power_parameter_name);

  modular_server::Parameter & ir_backlight_parameter = modular_server_.createParameter(constants::ir_backlight_parameter_name);
  ir_backlight_parameter.setRange(digital_controller::constants::channel_min,(long)(constants::IR_BACKLIGHT_COUNT - 1));

  modular_server::Parameter & visible_backlight_parameter = modular_server_.createParameter(constants::visible_backlight_parameter_name);
  visible_backlight_parameter.setRange(digital_controller::constants::channel_min,(long)(constants::VISIBLE_BACKLIGHT_COUNT - 1));

  modular_server::Parameter & high_voltage_parameter = modular_server_.createParameter(constants::high_voltage_parameter_name);
  high_voltage_parameter.setRange(digital_controller::constants::channel_min,(long)(constants::HIGH_VOLTAGE_COUNT - 1));

  modular_server::Parameter & low_voltage_parameter = modular_server_.createParameter(constants::low_voltage_parameter_name);
  low_voltage_parameter.setRange(digital_controller::constants::channel_min,(long)(constants::LOW_VOLTAGE_COUNT - 1));

  setChannelCountHandler();

  // Functions
  modular_server::Function & set_all_ir_backlights_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_all_ir_backlights_on_at_power_function_name);
  set_all_ir_backlights_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setAllIrBacklightsOnAtPowerHandler));
  set_all_ir_backlights_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_ir_backlight_on_function = modular_server_.createFunction(backlight_controller::constants::set_ir_backlight_on_function_name);
  set_ir_backlight_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setIrBacklightOnHandler));
  set_ir_backlight_on_function.addParameter(ir_backlight_parameter);

  modular_server::Function & set_ir_backlight_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_ir_backlight_on_at_power_function_name);
  set_ir_backlight_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setIrBacklightOnAtPowerHandler));
  set_ir_backlight_on_at_power_function.addParameter(ir_backlight_parameter);
  set_ir_backlight_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_ir_backlight_off_function = modular_server_.createFunction(backlight_controller::constants::set_ir_backlight_off_function_name);
  set_ir_backlight_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setIrBacklightOffHandler));
  set_ir_backlight_off_function.addParameter(ir_backlight_parameter);

  modular_server::Function & get_ir_backlight_powers_when_on_function = modular_server_.createFunction(constants::get_ir_backlight_powers_when_on_function_name);
  get_ir_backlight_powers_when_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::getIrBacklightPowersWhenOnHandler));
  get_ir_backlight_powers_when_on_function.setResultTypeArray();
  get_ir_backlight_powers_when_on_function.setResultTypeLong();

  modular_server::Function & get_ir_backlight_powers_function = modular_server_.createFunction(constants::get_ir_backlight_powers_function_name);
  get_ir_backlight_powers_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::getIrBacklightPowersHandler));
  get_ir_backlight_powers_function.setResultTypeArray();
  get_ir_backlight_powers_function.setResultTypeLong();

  modular_server::Function & set_all_visible_backlights_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_all_visible_backlights_on_at_power_function_name);
  set_all_visible_backlights_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setAllVisibleBacklightsOnAtPowerHandler));
  set_all_visible_backlights_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_visible_backlight_on_function = modular_server_.createFunction(backlight_controller::constants::set_visible_backlight_on_function_name);
  set_visible_backlight_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setVisibleBacklightOnHandler));
  set_visible_backlight_on_function.addParameter(visible_backlight_parameter);

  modular_server::Function & set_visible_backlight_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_visible_backlight_on_at_power_function_name);
  set_visible_backlight_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setVisibleBacklightOnAtPowerHandler));
  set_visible_backlight_on_at_power_function.addParameter(visible_backlight_parameter);
  set_visible_backlight_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_visible_backlight_off_function = modular_server_.createFunction(backlight_controller::constants::set_visible_backlight_off_function_name);
  set_visible_backlight_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setVisibleBacklightOffHandler));
  set_visible_backlight_off_function.addParameter(visible_backlight_parameter);

  modular_server::Function & get_visible_backlight_powers_when_on_function = modular_server_.createFunction(constants::get_visible_backlight_powers_when_on_function_name);
  get_visible_backlight_powers_when_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::getVisibleBacklightPowersWhenOnHandler));
  get_visible_backlight_powers_when_on_function.setResultTypeArray();
  get_visible_backlight_powers_when_on_function.setResultTypeLong();

  modular_server::Function & get_visible_backlight_powers_function = modular_server_.createFunction(constants::get_visible_backlight_powers_function_name);
  get_visible_backlight_powers_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::getVisibleBacklightPowersHandler));
  get_visible_backlight_powers_function.setResultTypeArray();
  get_visible_backlight_powers_function.setResultTypeLong();

  modular_server::Function & set_all_high_voltages_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_all_high_voltages_on_at_power_function_name);
  set_all_high_voltages_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setAllHighVoltagesOnAtPowerHandler));
  set_all_high_voltages_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_high_voltage_on_function = modular_server_.createFunction(backlight_controller::constants::set_high_voltage_on_function_name);
  set_high_voltage_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setHighVoltageOnHandler));
  set_high_voltage_on_function.addParameter(high_voltage_parameter);

  modular_server::Function & set_high_voltage_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_high_voltage_on_at_power_function_name);
  set_high_voltage_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setHighVoltageOnAtPowerHandler));
  set_high_voltage_on_at_power_function.addParameter(high_voltage_parameter);
  set_high_voltage_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_high_voltage_off_function = modular_server_.createFunction(backlight_controller::constants::set_high_voltage_off_function_name);
  set_high_voltage_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setHighVoltageOffHandler));
  set_high_voltage_off_function.addParameter(high_voltage_parameter);

  modular_server::Function & get_high_voltage_powers_when_on_function = modular_server_.createFunction(constants::get_high_voltage_powers_when_on_function_name);
  get_high_voltage_powers_when_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::getHighVoltagePowersWhenOnHandler));
  get_high_voltage_powers_when_on_function.setResultTypeArray();
  get_high_voltage_powers_when_on_function.setResultTypeLong();

  modular_server::Function & get_high_voltage_powers_function = modular_server_.createFunction(constants::get_high_voltage_powers_function_name);
  get_high_voltage_powers_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::getHighVoltagePowersHandler));
  get_high_voltage_powers_function.setResultTypeArray();
  get_high_voltage_powers_function.setResultTypeLong();

  modular_server::Function & set_all_low_voltages_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_all_low_voltages_on_at_power_function_name);
  set_all_low_voltages_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setAllLowVoltagesOnAtPowerHandler));
  set_all_low_voltages_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_low_voltage_on_function = modular_server_.createFunction(backlight_controller::constants::set_low_voltage_on_function_name);
  set_low_voltage_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setLowVoltageOnHandler));
  set_low_voltage_on_function.addParameter(low_voltage_parameter);

  modular_server::Function & set_low_voltage_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_low_voltage_on_at_power_function_name);
  set_low_voltage_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setLowVoltageOnAtPowerHandler));
  set_low_voltage_on_at_power_function.addParameter(low_voltage_parameter);
  set_low_voltage_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_low_voltage_off_function = modular_server_.createFunction(backlight_controller::constants::set_low_voltage_off_function_name);
  set_low_voltage_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setLowVoltageOffHandler));
  set_low_voltage_off_function.addParameter(low_voltage_parameter);

  modular_server::Function & get_low_voltage_powers_when_on_function = modular_server_.createFunction(constants::get_low_voltage_powers_when_on_function_name);
  get_low_voltage_powers_when_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::getLowVoltagePowersWhenOnHandler));
  get_low_voltage_powers_when_on_function.setResultTypeArray();
  get_low_voltage_powers_when_on_function.setResultTypeLong();

  modular_server::Function & get_low_voltage_powers_function = modular_server_.createFunction(constants::get_low_voltage_powers_function_name);
  get_low_voltage_powers_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::getLowVoltagePowersHandler));
  get_low_voltage_powers_function.setResultTypeArray();
  get_low_voltage_powers_function.setResultTypeLong();

  // Callbacks
  modular_server::Callback & enable_all_callback = modular_server_.callback(digital_controller::constants::enable_all_callback_name);
  enable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::enableAllHandler));

  modular_server::Callback & disable_all_callback = modular_server_.callback(digital_controller::constants::disable_all_callback_name);
  disable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::disableAllHandler));

  modular_server::Callback & set_all_ir_backlights_on_callback = modular_server_.createCallback(backlight_controller::constants::set_all_ir_backlights_on_callback_name);
  set_all_ir_backlights_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllIrBacklightsOnHandler));

  modular_server::Callback & set_all_ir_backlights_off_callback = modular_server_.createCallback(backlight_controller::constants::set_all_ir_backlights_off_callback_name);
  set_all_ir_backlights_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllIrBacklightsOffHandler));

  modular_server::Callback & toggle_all_ir_backlights_callback = modular_server_.createCallback(backlight_controller::constants::toggle_all_ir_backlights_callback_name);
  toggle_all_ir_backlights_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::toggleAllIrBacklightsHandler));

  modular_server::Callback & set_all_visible_backlights_on_callback = modular_server_.createCallback(backlight_controller::constants::set_all_visible_backlights_on_callback_name);
  set_all_visible_backlights_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllVisibleBacklightsOnHandler));

  modular_server::Callback & set_all_visible_backlights_off_callback = modular_server_.createCallback(backlight_controller::constants::set_all_visible_backlights_off_callback_name);
  set_all_visible_backlights_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllVisibleBacklightsOffHandler));
  set_all_visible_backlights_off_callback.attachTo(btn_b_pin,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & toggle_all_visible_backlights_callback = modular_server_.createCallback(backlight_controller::constants::toggle_all_visible_backlights_callback_name);
  toggle_all_visible_backlights_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::toggleAllVisibleBacklightsHandler));
  toggle_all_visible_backlights_callback.attachTo(btn_a_pin,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & set_all_high_voltages_on_callback = modular_server_.createCallback(backlight_controller::constants::set_all_high_voltages_on_callback_name);
  set_all_high_voltages_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllHighVoltagesOnHandler));

  modular_server::Callback & set_all_high_voltages_off_callback = modular_server_.createCallback(backlight_controller::constants::set_all_high_voltages_off_callback_name);
  set_all_high_voltages_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllHighVoltagesOffHandler));

  modular_server::Callback & toggle_all_high_voltages_callback = modular_server_.createCallback(backlight_controller::constants::toggle_all_high_voltages_callback_name);
  toggle_all_high_voltages_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::toggleAllHighVoltagesHandler));

  modular_server::Callback & set_all_low_voltages_on_callback = modular_server_.createCallback(backlight_controller::constants::set_all_low_voltages_on_callback_name);
  set_all_low_voltages_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllLowVoltagesOnHandler));

  modular_server::Callback & set_all_low_voltages_off_callback = modular_server_.createCallback(backlight_controller::constants::set_all_low_voltages_off_callback_name);
  set_all_low_voltages_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllLowVoltagesOffHandler));

  modular_server::Callback & toggle_all_low_voltages_callback = modular_server_.createCallback(backlight_controller::constants::toggle_all_low_voltages_callback_name);
  toggle_all_low_voltages_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::toggleAllLowVoltagesHandler));

  enableAll();
  setAllChannelsOff();
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

void BacklightController::setAllIrBacklightsOnAtPower(long power)
{
  setChannelsOnAtPower(getIrBacklightDigitalChannels(),power);
}

void BacklightController::setAllIrBacklightsOn()
{
  setChannelsOn(getIrBacklightDigitalChannels());
}

void BacklightController::setAllIrBacklightsOff()
{
  setChannelsOff(getIrBacklightDigitalChannels());
}

void BacklightController::toggleAllIrBacklights()
{
  toggleChannels(getIrBacklightDigitalChannels());
}

size_t BacklightController::getIrBacklightCount()
{
  return constants::IR_BACKLIGHT_COUNT;
}

void BacklightController::setIrBacklightOn(size_t ir_backlight)
{
  setChannelOn(irBacklightToDigitalChannel(ir_backlight));
}

void BacklightController::setIrBacklightOnAtPower(size_t ir_backlight,
  long power)
{
  setChannelOnAtPower(irBacklightToDigitalChannel(ir_backlight),power);
}

void BacklightController::setIrBacklightOff(size_t ir_backlight)
{
  setChannelOff(irBacklightToDigitalChannel(ir_backlight));
}

long BacklightController::getIrBacklightPowerWhenOn(size_t ir_backlight)
{
  return getPowerWhenOn(irBacklightToDigitalChannel(ir_backlight));
}

long BacklightController::getIrBacklightPower(size_t ir_backlight)
{
  return getPower(irBacklightToDigitalChannel(ir_backlight));
}

void BacklightController::setAllVisibleBacklightsOnAtPower(long power)
{
  setChannelsOnAtPower(getVisibleBacklightDigitalChannels(),power);
}

void BacklightController::setAllVisibleBacklightsOn()
{
  setChannelsOn(getVisibleBacklightDigitalChannels());
}

void BacklightController::setAllVisibleBacklightsOff()
{
  setChannelsOff(getVisibleBacklightDigitalChannels());
}

void BacklightController::toggleAllVisibleBacklights()
{
  toggleChannels(getVisibleBacklightDigitalChannels());
}

size_t BacklightController::getVisibleBacklightCount()
{
  return constants::VISIBLE_BACKLIGHT_COUNT;
}

void BacklightController::setVisibleBacklightOn(size_t visible_backlight)
{
  setChannelOn(visibleBacklightToDigitalChannel(visible_backlight));
}

void BacklightController::setVisibleBacklightOnAtPower(size_t visible_backlight,
  long power)
{
  setChannelOnAtPower(visibleBacklightToDigitalChannel(visible_backlight),power);
}

void BacklightController::setVisibleBacklightOff(size_t visible_backlight)
{
  setChannelOff(visibleBacklightToDigitalChannel(visible_backlight));
}

long BacklightController::getVisibleBacklightPowerWhenOn(size_t visible_backlight)
{
  return getPowerWhenOn(visibleBacklightToDigitalChannel(visible_backlight));
}

long BacklightController::getVisibleBacklightPower(size_t visible_backlight)
{
  return getPower(visibleBacklightToDigitalChannel(visible_backlight));
}

void BacklightController::setAllHighVoltagesOnAtPower(long power)
{
  setChannelsOnAtPower(getHighVoltageDigitalChannels(),power);
}

void BacklightController::setAllHighVoltagesOn()
{
  setChannelsOn(getHighVoltageDigitalChannels());
}

void BacklightController::setAllHighVoltagesOff()
{
  setChannelsOff(getHighVoltageDigitalChannels());
}

void BacklightController::toggleAllHighVoltages()
{
  toggleChannels(getHighVoltageDigitalChannels());
}

size_t BacklightController::getHighVoltageCount()
{
  return constants::HIGH_VOLTAGE_COUNT;
}

void BacklightController::setHighVoltageOn(size_t high_voltage)
{
  setChannelOn(highVoltageToDigitalChannel(high_voltage));
}

void BacklightController::setHighVoltageOnAtPower(size_t high_voltage,
  long power)
{
  setChannelOnAtPower(highVoltageToDigitalChannel(high_voltage),power);
}

void BacklightController::setHighVoltageOff(size_t high_voltage)
{
  setChannelOff(highVoltageToDigitalChannel(high_voltage));
}

long BacklightController::getHighVoltagePowerWhenOn(size_t high_voltage)
{
  return getPowerWhenOn(highVoltageToDigitalChannel(high_voltage));
}

long BacklightController::getHighVoltagePower(size_t high_voltage)
{
  return getPower(highVoltageToDigitalChannel(high_voltage));
}

void BacklightController::setAllLowVoltagesOnAtPower(long power)
{
  setChannelsOnAtPower(getLowVoltageDigitalChannels(),power);
}

void BacklightController::setAllLowVoltagesOn()
{
  setChannelsOn(getLowVoltageDigitalChannels());
}

void BacklightController::setAllLowVoltagesOff()
{
  setChannelsOff(getLowVoltageDigitalChannels());
}

void BacklightController::toggleAllLowVoltages()
{
  toggleChannels(getLowVoltageDigitalChannels());
}

size_t BacklightController::getLowVoltageCount()
{
  return constants::LOW_VOLTAGE_COUNT;
}

void BacklightController::setLowVoltageOn(size_t low_voltage)
{
  setChannelOn(lowVoltageToDigitalChannel(low_voltage));
}

void BacklightController::setLowVoltageOnAtPower(size_t low_voltage,
  long power)
{
  setChannelOnAtPower(lowVoltageToDigitalChannel(low_voltage),power);
}

void BacklightController::setLowVoltageOff(size_t low_voltage)
{
  setChannelOff(lowVoltageToDigitalChannel(low_voltage));
}

long BacklightController::getLowVoltagePowerWhenOn(size_t low_voltage)
{
  return getPowerWhenOn(lowVoltageToDigitalChannel(low_voltage));
}

long BacklightController::getLowVoltagePower(size_t low_voltage)
{
  return getPower(lowVoltageToDigitalChannel(low_voltage));
}

void BacklightController::setChannelOnAtHighFrequency(size_t channel,
  long high_frequency_duty_cycle)
{
  analogWrite(constants::channel_pins[channel],high_frequency_duty_cycle);
}

size_t BacklightController::irBacklightToDigitalChannel(size_t ir_backlight)
{
  if (ir_backlight >= constants::IR_BACKLIGHT_COUNT)
  {
    ir_backlight = 0;
  }
  return constants::ir_backlight_channels[ir_backlight];
}

uint32_t BacklightController::getIrBacklightDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t ir_backlight=0; ir_backlight<constants::IR_BACKLIGHT_COUNT; ++ir_backlight)
  {
    channel = irBacklightToDigitalChannel(ir_backlight);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::visibleBacklightToDigitalChannel(size_t visible_backlight)
{
  if (visible_backlight >= constants::VISIBLE_BACKLIGHT_COUNT)
  {
    visible_backlight = 0;
  }
  return constants::visible_backlight_channels[visible_backlight];
}

uint32_t BacklightController::getVisibleBacklightDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t visible_backlight=0; visible_backlight<constants::VISIBLE_BACKLIGHT_COUNT; ++visible_backlight)
  {
    channel = visibleBacklightToDigitalChannel(visible_backlight);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::highVoltageToDigitalChannel(size_t high_voltage)
{
  if (high_voltage >= constants::HIGH_VOLTAGE_COUNT)
  {
    high_voltage = 0;
  }
  return constants::high_voltage_channels[high_voltage];
}

uint32_t BacklightController::getHighVoltageDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t high_voltage=0; high_voltage<constants::HIGH_VOLTAGE_COUNT; ++high_voltage)
  {
    channel = highVoltageToDigitalChannel(high_voltage);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::lowVoltageToDigitalChannel(size_t low_voltage)
{
  if (low_voltage >= constants::LOW_VOLTAGE_COUNT)
  {
    low_voltage = 0;
  }
  return constants::low_voltage_channels[low_voltage];
}

uint32_t BacklightController::getLowVoltageDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t low_voltage=0; low_voltage<constants::LOW_VOLTAGE_COUNT; ++low_voltage)
  {
    channel = lowVoltageToDigitalChannel(low_voltage);
    channels |= (bit << channel);
  }
  return channels;
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

void BacklightController::enableAllHandler(modular_server::Pin * pin_ptr)
{
  enableAll();
}

void BacklightController::disableAllHandler(modular_server::Pin * pin_ptr)
{
  disableAll();
}

void BacklightController::setIrBacklightPowerMaxHandler(size_t ir_backlight)
{
  long power_max;
  modular_server::Property & ir_backlight_power_max_property = modular_server_.property(constants::ir_backlight_power_max_property_name);
  ir_backlight_power_max_property.getElementValue(ir_backlight,power_max);

  size_t digital_channel = irBacklightToDigitalChannel(ir_backlight);

  modular_server::Property & power_max_property = modular_server_.property(digital_controller::constants::power_max_property_name);
  power_max_property.setElementValue(digital_channel,power_max);
}

void BacklightController::setVisibleBacklightPowerMaxHandler(size_t visible_backlight)
{
  long power_max;
  modular_server::Property & visible_backlight_power_max_property = modular_server_.property(constants::visible_backlight_power_max_property_name);
  visible_backlight_power_max_property.getElementValue(visible_backlight,power_max);

  size_t digital_channel = visibleBacklightToDigitalChannel(visible_backlight);

  modular_server::Property & power_max_property = modular_server_.property(digital_controller::constants::power_max_property_name);
  power_max_property.setElementValue(digital_channel,power_max);
}

void BacklightController::setHighVoltagePowerMaxHandler(size_t high_voltage)
{
  long power_max;
  modular_server::Property & high_voltage_power_max_property = modular_server_.property(constants::high_voltage_power_max_property_name);
  high_voltage_power_max_property.getElementValue(high_voltage,power_max);

  size_t digital_channel = highVoltageToDigitalChannel(high_voltage);

  modular_server::Property & power_max_property = modular_server_.property(digital_controller::constants::power_max_property_name);
  power_max_property.setElementValue(digital_channel,power_max);
}

void BacklightController::setLowVoltagePowerMaxHandler(size_t low_voltage)
{
  long power_max;
  modular_server::Property & low_voltage_power_max_property = modular_server_.property(constants::low_voltage_power_max_property_name);
  low_voltage_power_max_property.getElementValue(low_voltage,power_max);

  size_t digital_channel = lowVoltageToDigitalChannel(low_voltage);

  modular_server::Property & power_max_property = modular_server_.property(digital_controller::constants::power_max_property_name);
  power_max_property.setElementValue(digital_channel,power_max);
}

void BacklightController::setAllIrBacklightsOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setAllIrBacklightsOnAtPower(power);
}

void BacklightController::setAllIrBacklightsOnHandler(modular_server::Pin * pin_ptr)
{
  setAllIrBacklightsOn();
}

void BacklightController::setAllIrBacklightsOffHandler(modular_server::Pin * pin_ptr)
{
  setAllIrBacklightsOff();
}

void BacklightController::toggleAllIrBacklightsHandler(modular_server::Pin * pin_ptr)
{
  toggleAllIrBacklights();
}

void BacklightController::setIrBacklightOnHandler()
{
  long ir_backlight;
  modular_server_.parameter(constants::ir_backlight_parameter_name).getValue(ir_backlight);

  setIrBacklightOn(ir_backlight);
}

void BacklightController::setIrBacklightOnAtPowerHandler()
{
  long ir_backlight;
  modular_server_.parameter(constants::ir_backlight_parameter_name).getValue(ir_backlight);

  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setIrBacklightOnAtPower(ir_backlight,power);
}

void BacklightController::setIrBacklightOffHandler()
{
  long ir_backlight;
  modular_server_.parameter(constants::ir_backlight_parameter_name).getValue(ir_backlight);

  setIrBacklightOff(ir_backlight);
}

void BacklightController::getIrBacklightPowersWhenOnHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  long power;
  for (size_t channel=0; channel<getIrBacklightCount(); ++channel)
  {
    power = getIrBacklightPowerWhenOn(channel);
    modular_server_.response().write(power);
  }
  modular_server_.response().endArray();
}

void BacklightController::getIrBacklightPowersHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  long power;
  for (size_t channel=0; channel<getIrBacklightCount(); ++channel)
  {
    power = getIrBacklightPower(channel);
    modular_server_.response().write(power);
  }
  modular_server_.response().endArray();
}

void BacklightController::setAllVisibleBacklightsOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setAllVisibleBacklightsOnAtPower(power);
}

void BacklightController::setAllVisibleBacklightsOnHandler(modular_server::Pin * pin_ptr)
{
  setAllVisibleBacklightsOn();
}

void BacklightController::setAllVisibleBacklightsOffHandler(modular_server::Pin * pin_ptr)
{
  setAllVisibleBacklightsOff();
}

void BacklightController::toggleAllVisibleBacklightsHandler(modular_server::Pin * pin_ptr)
{
  toggleAllVisibleBacklights();
}

void BacklightController::setVisibleBacklightOnHandler()
{
  long visible_backlight;
  modular_server_.parameter(constants::visible_backlight_parameter_name).getValue(visible_backlight);

  setVisibleBacklightOn(visible_backlight);
}

void BacklightController::setVisibleBacklightOnAtPowerHandler()
{
  long visible_backlight;
  modular_server_.parameter(constants::visible_backlight_parameter_name).getValue(visible_backlight);

  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setVisibleBacklightOnAtPower(visible_backlight,power);
}

void BacklightController::setVisibleBacklightOffHandler()
{
  long visible_backlight;
  modular_server_.parameter(constants::visible_backlight_parameter_name).getValue(visible_backlight);

  setVisibleBacklightOff(visible_backlight);
}

void BacklightController::getVisibleBacklightPowersWhenOnHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  long power;
  for (size_t channel=0; channel<getVisibleBacklightCount(); ++channel)
  {
    power = getVisibleBacklightPowerWhenOn(channel);
    modular_server_.response().write(power);
  }
  modular_server_.response().endArray();
}

void BacklightController::getVisibleBacklightPowersHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  long power;
  for (size_t channel=0; channel<getVisibleBacklightCount(); ++channel)
  {
    power = getVisibleBacklightPower(channel);
    modular_server_.response().write(power);
  }
  modular_server_.response().endArray();
}

void BacklightController::setAllHighVoltagesOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setAllHighVoltagesOnAtPower(power);
}

void BacklightController::setAllHighVoltagesOnHandler(modular_server::Pin * pin_ptr)
{
  setAllHighVoltagesOn();
}

void BacklightController::setAllHighVoltagesOffHandler(modular_server::Pin * pin_ptr)
{
  setAllHighVoltagesOff();
}

void BacklightController::toggleAllHighVoltagesHandler(modular_server::Pin * pin_ptr)
{
  toggleAllHighVoltages();
}

void BacklightController::setHighVoltageOnHandler()
{
  long high_voltage;
  modular_server_.parameter(constants::high_voltage_parameter_name).getValue(high_voltage);

  setHighVoltageOn(high_voltage);
}

void BacklightController::setHighVoltageOnAtPowerHandler()
{
  long high_voltage;
  modular_server_.parameter(constants::high_voltage_parameter_name).getValue(high_voltage);

  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setHighVoltageOnAtPower(high_voltage,power);
}

void BacklightController::setHighVoltageOffHandler()
{
  long high_voltage;
  modular_server_.parameter(constants::high_voltage_parameter_name).getValue(high_voltage);

  setHighVoltageOff(high_voltage);
}

void BacklightController::getHighVoltagePowersWhenOnHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  long power;
  for (size_t channel=0; channel<getHighVoltageCount(); ++channel)
  {
    power = getHighVoltagePowerWhenOn(channel);
    modular_server_.response().write(power);
  }
  modular_server_.response().endArray();
}

void BacklightController::getHighVoltagePowersHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  long power;
  for (size_t channel=0; channel<getHighVoltageCount(); ++channel)
  {
    power = getHighVoltagePower(channel);
    modular_server_.response().write(power);
  }
  modular_server_.response().endArray();
}

void BacklightController::setAllLowVoltagesOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setAllLowVoltagesOnAtPower(power);
}

void BacklightController::setAllLowVoltagesOnHandler(modular_server::Pin * pin_ptr)
{
  setAllLowVoltagesOn();
}

void BacklightController::setAllLowVoltagesOffHandler(modular_server::Pin * pin_ptr)
{
  setAllLowVoltagesOff();
}

void BacklightController::toggleAllLowVoltagesHandler(modular_server::Pin * pin_ptr)
{
  toggleAllLowVoltages();
}

void BacklightController::setLowVoltageOnHandler()
{
  long low_voltage;
  modular_server_.parameter(constants::low_voltage_parameter_name).getValue(low_voltage);

  setLowVoltageOn(low_voltage);
}

void BacklightController::setLowVoltageOnAtPowerHandler()
{
  long low_voltage;
  modular_server_.parameter(constants::low_voltage_parameter_name).getValue(low_voltage);

  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setLowVoltageOnAtPower(low_voltage,power);
}

void BacklightController::setLowVoltageOffHandler()
{
  long low_voltage;
  modular_server_.parameter(constants::low_voltage_parameter_name).getValue(low_voltage);

  setLowVoltageOff(low_voltage);
}

void BacklightController::getLowVoltagePowersWhenOnHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  long power;
  for (size_t channel=0; channel<getLowVoltageCount(); ++channel)
  {
    power = getLowVoltagePowerWhenOn(channel);
    modular_server_.response().write(power);
  }
  modular_server_.response().endArray();
}

void BacklightController::getLowVoltagePowersHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  long power;
  for (size_t channel=0; channel<getLowVoltageCount(); ++channel)
  {
    power = getLowVoltagePower(channel);
    modular_server_.response().write(power);
  }
  modular_server_.response().endArray();
}
