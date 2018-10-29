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
  low_voltage_power_max_property.setRange(digital_controller::constants::power_min,digital_controller::constants::power_max);
  low_voltage_power_max_property.setUnits(digital_controller::constants::percent_units);
  low_voltage_power_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&BacklightController::setLowVoltagePowerMaxHandler));

  // Parameters
  modular_server::Parameter & power_parameter = modular_server_.parameter(digital_controller::constants::power_parameter_name);

  modular_server::Parameter & ir_backlight_channel_parameter = modular_server_.createParameter(constants::ir_backlight_channel_parameter_name);
  ir_backlight_channel_parameter.setRange(digital_controller::constants::channel_min,(long)(constants::IR_BACKLIGHT_CHANNEL_COUNT - 1));

  modular_server::Parameter & visible_backlight_channel_parameter = modular_server_.createParameter(constants::visible_backlight_channel_parameter_name);
  visible_backlight_channel_parameter.setRange(digital_controller::constants::channel_min,(long)(constants::VISIBLE_BACKLIGHT_CHANNEL_COUNT - 1));

  modular_server::Parameter & high_voltage_channel_parameter = modular_server_.createParameter(constants::high_voltage_channel_parameter_name);
  high_voltage_channel_parameter.setRange(digital_controller::constants::channel_min,(long)(constants::HIGH_VOLTAGE_CHANNEL_COUNT - 1));

  modular_server::Parameter & low_voltage_channel_parameter = modular_server_.createParameter(constants::low_voltage_channel_parameter_name);
  low_voltage_channel_parameter.setRange(digital_controller::constants::channel_min,(long)(constants::LOW_VOLTAGE_CHANNEL_COUNT - 1));

  setChannelCountHandler();

  // Functions
  modular_server::Function & set_all_ir_backlight_channels_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_all_ir_backlight_channels_on_at_power_function_name);
  set_all_ir_backlight_channels_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setAllIrBacklightChannelsOnAtPowerHandler));
  set_all_ir_backlight_channels_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_ir_backlight_channel_on_function = modular_server_.createFunction(backlight_controller::constants::set_ir_backlight_channel_on_function_name);
  set_ir_backlight_channel_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setIrBacklightChannelOnHandler));
  set_ir_backlight_channel_on_function.addParameter(ir_backlight_channel_parameter);

  modular_server::Function & set_ir_backlight_channel_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_ir_backlight_channel_on_at_power_function_name);
  set_ir_backlight_channel_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setIrBacklightChannelOnAtPowerHandler));
  set_ir_backlight_channel_on_at_power_function.addParameter(ir_backlight_channel_parameter);
  set_ir_backlight_channel_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_ir_backlight_channel_off_function = modular_server_.createFunction(backlight_controller::constants::set_ir_backlight_channel_off_function_name);
  set_ir_backlight_channel_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setIrBacklightChannelOffHandler));
  set_ir_backlight_channel_off_function.addParameter(ir_backlight_channel_parameter);

  modular_server::Function & set_all_visible_backlight_channels_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_all_visible_backlight_channels_on_at_power_function_name);
  set_all_visible_backlight_channels_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setAllVisibleBacklightChannelsOnAtPowerHandler));
  set_all_visible_backlight_channels_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_visible_backlight_channel_on_function = modular_server_.createFunction(backlight_controller::constants::set_visible_backlight_channel_on_function_name);
  set_visible_backlight_channel_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setVisibleBacklightChannelOnHandler));
  set_visible_backlight_channel_on_function.addParameter(visible_backlight_channel_parameter);

  modular_server::Function & set_visible_backlight_channel_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_visible_backlight_channel_on_at_power_function_name);
  set_visible_backlight_channel_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setVisibleBacklightChannelOnAtPowerHandler));
  set_visible_backlight_channel_on_at_power_function.addParameter(visible_backlight_channel_parameter);
  set_visible_backlight_channel_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_visible_backlight_channel_off_function = modular_server_.createFunction(backlight_controller::constants::set_visible_backlight_channel_off_function_name);
  set_visible_backlight_channel_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setVisibleBacklightChannelOffHandler));
  set_visible_backlight_channel_off_function.addParameter(visible_backlight_channel_parameter);

  modular_server::Function & set_all_high_voltage_channels_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_all_high_voltage_channels_on_at_power_function_name);
  set_all_high_voltage_channels_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setAllHighVoltageChannelsOnAtPowerHandler));
  set_all_high_voltage_channels_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_high_voltage_channel_on_function = modular_server_.createFunction(backlight_controller::constants::set_high_voltage_channel_on_function_name);
  set_high_voltage_channel_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setHighVoltageChannelOnHandler));
  set_high_voltage_channel_on_function.addParameter(high_voltage_channel_parameter);

  modular_server::Function & set_high_voltage_channel_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_high_voltage_channel_on_at_power_function_name);
  set_high_voltage_channel_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setHighVoltageChannelOnAtPowerHandler));
  set_high_voltage_channel_on_at_power_function.addParameter(high_voltage_channel_parameter);
  set_high_voltage_channel_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_high_voltage_channel_off_function = modular_server_.createFunction(backlight_controller::constants::set_high_voltage_channel_off_function_name);
  set_high_voltage_channel_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setHighVoltageChannelOffHandler));
  set_high_voltage_channel_off_function.addParameter(high_voltage_channel_parameter);

  modular_server::Function & set_all_low_voltage_channels_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_all_low_voltage_channels_on_at_power_function_name);
  set_all_low_voltage_channels_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setAllLowVoltageChannelsOnAtPowerHandler));
  set_all_low_voltage_channels_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_low_voltage_channel_on_function = modular_server_.createFunction(backlight_controller::constants::set_low_voltage_channel_on_function_name);
  set_low_voltage_channel_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setLowVoltageChannelOnHandler));
  set_low_voltage_channel_on_function.addParameter(low_voltage_channel_parameter);

  modular_server::Function & set_low_voltage_channel_on_at_power_function = modular_server_.createFunction(backlight_controller::constants::set_low_voltage_channel_on_at_power_function_name);
  set_low_voltage_channel_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setLowVoltageChannelOnAtPowerHandler));
  set_low_voltage_channel_on_at_power_function.addParameter(low_voltage_channel_parameter);
  set_low_voltage_channel_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_low_voltage_channel_off_function = modular_server_.createFunction(backlight_controller::constants::set_low_voltage_channel_off_function_name);
  set_low_voltage_channel_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&BacklightController::setLowVoltageChannelOffHandler));
  set_low_voltage_channel_off_function.addParameter(low_voltage_channel_parameter);

  // Callbacks
  modular_server::Callback & enable_all_callback = modular_server_.callback(digital_controller::constants::enable_all_callback_name);
  enable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::enableAllHandler));

  modular_server::Callback & disable_all_callback = modular_server_.callback(digital_controller::constants::disable_all_callback_name);
  disable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::disableAllHandler));

  modular_server::Callback & set_all_ir_backlight_channels_on_callback = modular_server_.createCallback(backlight_controller::constants::set_all_ir_backlight_channels_on_callback_name);
  set_all_ir_backlight_channels_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllIrBacklightChannelsOnHandler));

  modular_server::Callback & set_all_ir_backlight_channels_off_callback = modular_server_.createCallback(backlight_controller::constants::set_all_ir_backlight_channels_off_callback_name);
  set_all_ir_backlight_channels_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllIrBacklightChannelsOffHandler));

  modular_server::Callback & set_all_visible_backlight_channels_on_callback = modular_server_.createCallback(backlight_controller::constants::set_all_visible_backlight_channels_on_callback_name);
  set_all_visible_backlight_channels_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllVisibleBacklightChannelsOnHandler));
  set_all_visible_backlight_channels_on_callback.attachTo(btn_a_pin,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & set_all_visible_backlight_channels_off_callback = modular_server_.createCallback(backlight_controller::constants::set_all_visible_backlight_channels_off_callback_name);
  set_all_visible_backlight_channels_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllVisibleBacklightChannelsOffHandler));
  set_all_visible_backlight_channels_off_callback.attachTo(btn_b_pin,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & set_all_high_voltage_channels_on_callback = modular_server_.createCallback(backlight_controller::constants::set_all_high_voltage_channels_on_callback_name);
  set_all_high_voltage_channels_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllHighVoltageChannelsOnHandler));

  modular_server::Callback & set_all_high_voltage_channels_off_callback = modular_server_.createCallback(backlight_controller::constants::set_all_high_voltage_channels_off_callback_name);
  set_all_high_voltage_channels_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllHighVoltageChannelsOffHandler));

  modular_server::Callback & set_all_low_voltage_channels_on_callback = modular_server_.createCallback(backlight_controller::constants::set_all_low_voltage_channels_on_callback_name);
  set_all_low_voltage_channels_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllLowVoltageChannelsOnHandler));

  modular_server::Callback & set_all_low_voltage_channels_off_callback = modular_server_.createCallback(backlight_controller::constants::set_all_low_voltage_channels_off_callback_name);
  set_all_low_voltage_channels_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllLowVoltageChannelsOffHandler));

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

void BacklightController::setAllIrBacklightChannelsOn()
{
  setChannelsOn(getIrBacklightDigitalChannels());
}

void BacklightController::setAllIrBacklightChannelsOnAtPower(long power)
{
  setChannelsOnAtPower(getIrBacklightDigitalChannels(),power);
}

void BacklightController::setAllIrBacklightChannelsOff()
{
  setChannelsOff(getIrBacklightDigitalChannels());
}

void BacklightController::setIrBacklightChannelOn(size_t ir_backlight_channel)
{
  setChannelOn(irBacklightChannelToDigitalChannel(ir_backlight_channel));
}

void BacklightController::setIrBacklightChannelOnAtPower(size_t ir_backlight_channel,
  long power)
{
  setChannelOnAtPower(irBacklightChannelToDigitalChannel(ir_backlight_channel),power);
}

void BacklightController::setIrBacklightChannelOff(size_t ir_backlight_channel)
{
  setChannelOff(irBacklightChannelToDigitalChannel(ir_backlight_channel));
}

void BacklightController::setAllVisibleBacklightChannelsOn()
{
  setChannelsOn(getVisibleBacklightDigitalChannels());
}

void BacklightController::setAllVisibleBacklightChannelsOnAtPower(long power)
{
  setChannelsOnAtPower(getVisibleBacklightDigitalChannels(),power);
}

void BacklightController::setAllVisibleBacklightChannelsOff()
{
  setChannelsOff(getVisibleBacklightDigitalChannels());
}

void BacklightController::setVisibleBacklightChannelOn(size_t visible_backlight_channel)
{
  setChannelOn(visibleBacklightChannelToDigitalChannel(visible_backlight_channel));
}

void BacklightController::setVisibleBacklightChannelOnAtPower(size_t visible_backlight_channel,
  long power)
{
  setChannelOnAtPower(visibleBacklightChannelToDigitalChannel(visible_backlight_channel),power);
}

void BacklightController::setVisibleBacklightChannelOff(size_t visible_backlight_channel)
{
  setChannelOff(visibleBacklightChannelToDigitalChannel(visible_backlight_channel));
}

void BacklightController::setAllHighVoltageChannelsOn()
{
  setChannelsOn(getHighVoltageDigitalChannels());
}

void BacklightController::setAllHighVoltageChannelsOnAtPower(long power)
{
  setChannelsOnAtPower(getHighVoltageDigitalChannels(),power);
}

void BacklightController::setAllHighVoltageChannelsOff()
{
  setChannelsOff(getHighVoltageDigitalChannels());
}

void BacklightController::setHighVoltageChannelOn(size_t high_voltage_channel)
{
  setChannelOn(highVoltageChannelToDigitalChannel(high_voltage_channel));
}

void BacklightController::setHighVoltageChannelOnAtPower(size_t high_voltage_channel,
  long power)
{
  setChannelOnAtPower(highVoltageChannelToDigitalChannel(high_voltage_channel),power);
}

void BacklightController::setHighVoltageChannelOff(size_t high_voltage_channel)
{
  setChannelOff(highVoltageChannelToDigitalChannel(high_voltage_channel));
}

void BacklightController::setAllLowVoltageChannelsOn()
{
  setChannelsOn(getLowVoltageDigitalChannels());
}

void BacklightController::setAllLowVoltageChannelsOnAtPower(long power)
{
  setChannelsOnAtPower(getLowVoltageDigitalChannels(),power);
}

void BacklightController::setAllLowVoltageChannelsOff()
{
  setChannelsOff(getLowVoltageDigitalChannels());
}

void BacklightController::setLowVoltageChannelOn(size_t low_voltage_channel)
{
  setChannelOn(lowVoltageChannelToDigitalChannel(low_voltage_channel));
}

void BacklightController::setLowVoltageChannelOnAtPower(size_t low_voltage_channel,
  long power)
{
  setChannelOnAtPower(lowVoltageChannelToDigitalChannel(low_voltage_channel),power);
}

void BacklightController::setLowVoltageChannelOff(size_t low_voltage_channel)
{
  setChannelOff(lowVoltageChannelToDigitalChannel(low_voltage_channel));
}

void BacklightController::setChannelOnAtHighFrequency(size_t channel,
  long high_frequency_duty_cycle)
{
  Serial << "channel = " << channel << "\n";
  Serial << "analogWrite(" << constants::channel_pins[channel] << "," << high_frequency_duty_cycle << ")\n";
  analogWrite(constants::channel_pins[channel],high_frequency_duty_cycle);
}

size_t BacklightController::irBacklightChannelToDigitalChannel(size_t ir_backlight_channel)
{
  if (ir_backlight_channel >= constants::IR_BACKLIGHT_CHANNEL_COUNT)
  {
    ir_backlight_channel = 0;
  }
  return constants::ir_backlight_channels[ir_backlight_channel];
}

uint32_t BacklightController::getIrBacklightDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t ir_backlight_channel=0; ir_backlight_channel<constants::IR_BACKLIGHT_CHANNEL_COUNT; ++ir_backlight_channel)
  {
    channel = irBacklightChannelToDigitalChannel(ir_backlight_channel);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::visibleBacklightChannelToDigitalChannel(size_t visible_backlight_channel)
{
  if (visible_backlight_channel >= constants::VISIBLE_BACKLIGHT_CHANNEL_COUNT)
  {
    visible_backlight_channel = 0;
  }
  return constants::visible_backlight_channels[visible_backlight_channel];
}

uint32_t BacklightController::getVisibleBacklightDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t visible_backlight_channel=0; visible_backlight_channel<constants::VISIBLE_BACKLIGHT_CHANNEL_COUNT; ++visible_backlight_channel)
  {
    channel = visibleBacklightChannelToDigitalChannel(visible_backlight_channel);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::highVoltageChannelToDigitalChannel(size_t high_voltage_channel)
{
  if (high_voltage_channel >= constants::HIGH_VOLTAGE_CHANNEL_COUNT)
  {
    high_voltage_channel = 0;
  }
  return constants::high_voltage_channels[high_voltage_channel];
}

uint32_t BacklightController::getHighVoltageDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t high_voltage_channel=0; high_voltage_channel<constants::HIGH_VOLTAGE_CHANNEL_COUNT; ++high_voltage_channel)
  {
    channel = highVoltageChannelToDigitalChannel(high_voltage_channel);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::lowVoltageChannelToDigitalChannel(size_t low_voltage_channel)
{
  if (low_voltage_channel >= constants::LOW_VOLTAGE_CHANNEL_COUNT)
  {
    low_voltage_channel = 0;
  }
  return constants::low_voltage_channels[low_voltage_channel];
}

uint32_t BacklightController::getLowVoltageDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t low_voltage_channel=0; low_voltage_channel<constants::LOW_VOLTAGE_CHANNEL_COUNT; ++low_voltage_channel)
  {
    channel = lowVoltageChannelToDigitalChannel(low_voltage_channel);
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

void BacklightController::setIrBacklightPowerMaxHandler(size_t ir_backlight_channel)
{
  long power_max;
  modular_server::Property & ir_backlight_power_max_property = modular_server_.property(constants::ir_backlight_power_max_property_name);
  ir_backlight_power_max_property.getElementValue(ir_backlight_channel,power_max);

  size_t digital_channel = irBacklightChannelToDigitalChannel(ir_backlight_channel);

  modular_server::Property & power_max_property = modular_server_.property(digital_controller::constants::power_max_property_name);
  power_max_property.setElementValue(digital_channel,power_max);
}

void BacklightController::setVisibleBacklightPowerMaxHandler(size_t visible_backlight_channel)
{
  long power_max;
  modular_server::Property & visible_backlight_power_max_property = modular_server_.property(constants::visible_backlight_power_max_property_name);
  visible_backlight_power_max_property.getElementValue(visible_backlight_channel,power_max);

  size_t digital_channel = visibleBacklightChannelToDigitalChannel(visible_backlight_channel);

  modular_server::Property & power_max_property = modular_server_.property(digital_controller::constants::power_max_property_name);
  power_max_property.setElementValue(digital_channel,power_max);
}

void BacklightController::setHighVoltagePowerMaxHandler(size_t high_voltage_channel)
{
  long power_max;
  modular_server::Property & high_voltage_power_max_property = modular_server_.property(constants::high_voltage_power_max_property_name);
  high_voltage_power_max_property.getElementValue(high_voltage_channel,power_max);

  size_t digital_channel = highVoltageChannelToDigitalChannel(high_voltage_channel);

  modular_server::Property & power_max_property = modular_server_.property(digital_controller::constants::power_max_property_name);
  power_max_property.setElementValue(digital_channel,power_max);
}

void BacklightController::setLowVoltagePowerMaxHandler(size_t low_voltage_channel)
{
  long power_max;
  modular_server::Property & low_voltage_power_max_property = modular_server_.property(constants::low_voltage_power_max_property_name);
  low_voltage_power_max_property.getElementValue(low_voltage_channel,power_max);

  size_t digital_channel = lowVoltageChannelToDigitalChannel(low_voltage_channel);

  modular_server::Property & power_max_property = modular_server_.property(digital_controller::constants::power_max_property_name);
  power_max_property.setElementValue(digital_channel,power_max);
}

void BacklightController::setAllIrBacklightChannelsOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setAllIrBacklightChannelsOnAtPower(power);
}

void BacklightController::setAllIrBacklightChannelsOnHandler(modular_server::Pin * pin_ptr)
{
  setAllIrBacklightChannelsOn();
}

void BacklightController::setAllIrBacklightChannelsOffHandler(modular_server::Pin * pin_ptr)
{
  setAllIrBacklightChannelsOff();
}

void BacklightController::setIrBacklightChannelOnHandler()
{
  long ir_backlight_channel;
  modular_server_.parameter(constants::ir_backlight_channel_parameter_name).getValue(ir_backlight_channel);

  setIrBacklightChannelOn(ir_backlight_channel);
}

void BacklightController::setIrBacklightChannelOnAtPowerHandler()
{
  long ir_backlight_channel;
  modular_server_.parameter(constants::ir_backlight_channel_parameter_name).getValue(ir_backlight_channel);

  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setIrBacklightChannelOnAtPower(ir_backlight_channel,power);
}

void BacklightController::setIrBacklightChannelOffHandler()
{
  long ir_backlight_channel;
  modular_server_.parameter(constants::ir_backlight_channel_parameter_name).getValue(ir_backlight_channel);

  setIrBacklightChannelOff(ir_backlight_channel);
}

void BacklightController::setAllVisibleBacklightChannelsOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setAllVisibleBacklightChannelsOnAtPower(power);
}

void BacklightController::setAllVisibleBacklightChannelsOnHandler(modular_server::Pin * pin_ptr)
{
  setAllVisibleBacklightChannelsOn();
}

void BacklightController::setAllVisibleBacklightChannelsOffHandler(modular_server::Pin * pin_ptr)
{
  setAllVisibleBacklightChannelsOff();
}

void BacklightController::setVisibleBacklightChannelOnHandler()
{
  long visible_backlight_channel;
  modular_server_.parameter(constants::visible_backlight_channel_parameter_name).getValue(visible_backlight_channel);

  setVisibleBacklightChannelOn(visible_backlight_channel);
}

void BacklightController::setVisibleBacklightChannelOnAtPowerHandler()
{
  long visible_backlight_channel;
  modular_server_.parameter(constants::visible_backlight_channel_parameter_name).getValue(visible_backlight_channel);

  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setVisibleBacklightChannelOnAtPower(visible_backlight_channel,power);
}

void BacklightController::setVisibleBacklightChannelOffHandler()
{
  long visible_backlight_channel;
  modular_server_.parameter(constants::visible_backlight_channel_parameter_name).getValue(visible_backlight_channel);

  setVisibleBacklightChannelOff(visible_backlight_channel);
}

void BacklightController::setAllHighVoltageChannelsOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setAllHighVoltageChannelsOnAtPower(power);
}

void BacklightController::setAllHighVoltageChannelsOnHandler(modular_server::Pin * pin_ptr)
{
  setAllHighVoltageChannelsOn();
}

void BacklightController::setAllHighVoltageChannelsOffHandler(modular_server::Pin * pin_ptr)
{
  setAllHighVoltageChannelsOff();
}

void BacklightController::setHighVoltageChannelOnHandler()
{
  long high_voltage_channel;
  modular_server_.parameter(constants::high_voltage_channel_parameter_name).getValue(high_voltage_channel);

  setHighVoltageChannelOn(high_voltage_channel);
}

void BacklightController::setHighVoltageChannelOnAtPowerHandler()
{
  long high_voltage_channel;
  modular_server_.parameter(constants::high_voltage_channel_parameter_name).getValue(high_voltage_channel);

  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setHighVoltageChannelOnAtPower(high_voltage_channel,power);
}

void BacklightController::setHighVoltageChannelOffHandler()
{
  long high_voltage_channel;
  modular_server_.parameter(constants::high_voltage_channel_parameter_name).getValue(high_voltage_channel);

  setHighVoltageChannelOff(high_voltage_channel);
}

void BacklightController::setAllLowVoltageChannelsOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setAllLowVoltageChannelsOnAtPower(power);
}

void BacklightController::setAllLowVoltageChannelsOnHandler(modular_server::Pin * pin_ptr)
{
  setAllLowVoltageChannelsOn();
}

void BacklightController::setAllLowVoltageChannelsOffHandler(modular_server::Pin * pin_ptr)
{
  setAllLowVoltageChannelsOff();
}

void BacklightController::setLowVoltageChannelOnHandler()
{
  long low_voltage_channel;
  modular_server_.parameter(constants::low_voltage_channel_parameter_name).getValue(low_voltage_channel);

  setLowVoltageChannelOn(low_voltage_channel);
}

void BacklightController::setLowVoltageChannelOnAtPowerHandler()
{
  long low_voltage_channel;
  modular_server_.parameter(constants::low_voltage_channel_parameter_name).getValue(low_voltage_channel);

  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setLowVoltageChannelOnAtPower(low_voltage_channel,power);
}

void BacklightController::setLowVoltageChannelOffHandler()
{
  long low_voltage_channel;
  modular_server_.parameter(constants::low_voltage_channel_parameter_name).getValue(low_voltage_channel);

  setLowVoltageChannelOff(low_voltage_channel);
}
