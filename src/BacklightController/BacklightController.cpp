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

  // Callbacks
  modular_server::Callback & enable_all_callback = modular_server_.callback(digital_controller::constants::enable_all_callback_name);
  enable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::enableAllHandler));

  modular_server::Callback & disable_all_callback = modular_server_.callback(digital_controller::constants::disable_all_callback_name);
  disable_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::disableAllHandler));

  modular_server::Callback & set_all_ir_channels_on_callback = modular_server_.createCallback(digital_controller::constants::set_all_ir_channels_on_callback_name);
  set_all_ir_channels_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllIrChannelsOnHandler));

  modular_server::Callback & set_all_ir_channels_off_callback = modular_server_.createCallback(digital_controller::constants::set_all_ir_channels_off_callback_name);
  set_all_ir_channels_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&BacklightController::setAllIrChannelsOffHandler));

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

void BacklightController::setAllIrLightChannelsOn()
{
  setChannelsOn(getIrLightDigitalChannels());
}

void BacklightController::setAllIrLightChannelsOnAtPower(long power)
{
  setChannelsOnAtPower(getIrLightDigitalChannels(),power);
}

void BacklightController::setAllIrLightChannelsOff()
{
  setChannelsOff(getIrLightDigitalChannels());
}

void BacklightController::setChannelOnAtHighFrequency(size_t channel,
  long high_frequency_duty_cycle)
{
  analogWrite(constants::channel_pins[channel],high_frequency_duty_cycle);
}

size_t BacklightController::irLightChannelToDigitalChannel(size_t ir_light_channel)
{
  if (ir_light_channel >= constants::IR_LIGHT_CHANNEL_COUNT)
  {
    ir_light_channel = 0;
  }
  return constants::ir_light_channels[ir_light_channel];
}

uint32_t BacklightController::getIrLightDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t ir_light_channel=0; ir_light_channel<constants::IR_LIGHT_CHANNEL_COUNT; ++ir_light_channel)
  {
    channel = irLightChannelToDigitalChannel(ir_light_channel);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::visibleLightChannelToDigitalChannel(size_t visible_light_channel)
{
  if (visible_light_channel >= constants::VISIBLE_LIGHT_CHANNEL_COUNT)
  {
    visible_light_channel = 0;
  }
  return constants::visible_light_channels[visible_light_channel];
}

uint32_t BacklightController::getVisibleLightDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t visible_light_channel=0; visible_light_channel<constants::VISIBLE_LIGHT_CHANNEL_COUNT; ++visible_light_channel)
  {
    channel = visibleLightChannelToDigitalChannel(visible_light_channel);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::highPowerChannelToDigitalChannel(size_t high_power_channel)
{
  if (high_power_channel >= constants::HIGH_POWER_CHANNEL_COUNT)
  {
    high_power_channel = 0;
  }
  return constants::high_power_channels[high_power_channel];
}

uint32_t BacklightController::getHighPowerDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t high_power_channel=0; high_power_channel<constants::HIGH_POWER_CHANNEL_COUNT; ++high_power_channel)
  {
    channel = highPowerChannelToDigitalChannel(high_power_channel);
    channels |= (bit << channel);
  }
  return channels;
}

size_t BacklightController::lowPowerChannelToDigitalChannel(size_t low_power_channel)
{
  if (low_power_channel >= constants::LOW_POWER_CHANNEL_COUNT)
  {
    low_power_channel = 0;
  }
  return constants::low_power_channels[low_power_channel];
}

uint32_t BacklightController::getLowPowerDigitalChannels()
{
  uint32_t channels = 0;
  uint32_t bit = 1;
  size_t channel;
  for (size_t low_power_channel=0; low_power_channel<constants::LOW_POWER_CHANNEL_COUNT; ++low_power_channel)
  {
    channel = lowPowerChannelToDigitalChannel(low_power_channel);
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

void BacklightController::setAllIrChannelsOnHandler(modular_server::Pin * pin_ptr)
{
  setAllIrChannelsOn();
}

void BacklightController::setAllIrChannelsOffHandler(modular_server::Pin * pin_ptr)
{
  setAllIrChannelsOff();
}
