// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace backlight_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"backlight_controller");

CONSTANT_STRING(firmware_name,"BacklightController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"backlight_controller");

// Pins

// Units

// Properties
CONSTANT_STRING(ir_backlight_power_max_property_name,"irBacklightPowerMax");
const long ir_backlight_power_max_element_default = 100;

CONSTANT_STRING(visible_backlight_power_max_property_name,"visibleBacklightPowerMax");
const long visible_backlight_power_max_element_default = 100;

CONSTANT_STRING(high_voltage_power_max_property_name,"highVoltagePowerMax");
const long high_voltage_power_max_element_default = 100;

CONSTANT_STRING(low_voltage_power_max_property_name,"lowVoltagePowerMax");
const long low_voltage_power_max_element_default = 100;

// Parameters
CONSTANT_STRING(ir_backlight_channel_parameter_name,"ir_backlight_channel");

CONSTANT_STRING(visible_backlight_channel_parameter_name,"visible_backlight_channel");

CONSTANT_STRING(high_voltage_channel_parameter_name,"high_voltage_channel");

CONSTANT_STRING(low_voltage_channel_parameter_name,"low_voltage_channel");

// Functions
CONSTANT_STRING(set_all_ir_backlight_channels_on_at_power_function_name,"setAllIrBacklightChannelsOnAtPower");
CONSTANT_STRING(set_ir_backlight_channel_on_function_name,"setIrBacklightChannelOn");
CONSTANT_STRING(set_ir_backlight_channel_on_at_power_function_name,"setIrBacklightChannelOnAtPower");
CONSTANT_STRING(set_ir_backlight_channel_off_function_name,"setIrBacklightChannelOff");
CONSTANT_STRING(set_all_visible_backlight_channels_on_at_power_function_name,"setAllVisibleBacklightChannelsOnAtPower");
CONSTANT_STRING(set_visible_backlight_channel_on_function_name,"setVisibleBacklightChannelOn");
CONSTANT_STRING(set_visible_backlight_channel_on_at_power_function_name,"setVisibleBacklightChannelOnAtPower");
CONSTANT_STRING(set_visible_backlight_channel_off_function_name,"setVisibleBacklightChannelOff");
CONSTANT_STRING(set_all_high_voltage_channels_on_at_power_function_name,"setAllHighVoltageChannelsOnAtPower");
CONSTANT_STRING(set_high_voltage_channel_on_function_name,"setHighVoltageChannelOn");
CONSTANT_STRING(set_high_voltage_channel_on_at_power_function_name,"setHighVoltageChannelOnAtPower");
CONSTANT_STRING(set_high_voltage_channel_off_function_name,"setHighVoltageChannelOff");
CONSTANT_STRING(set_all_low_voltage_channels_on_at_power_function_name,"setAllLowVoltageChannelsOnAtPower");
CONSTANT_STRING(set_low_voltage_channel_on_function_name,"setLowVoltageChannelOn");
CONSTANT_STRING(set_low_voltage_channel_on_at_power_function_name,"setLowVoltageChannelOnAtPower");
CONSTANT_STRING(set_low_voltage_channel_off_function_name,"setLowVoltageChannelOff");

// Callbacks
CONSTANT_STRING(set_all_ir_backlight_channels_on_callback_name,"setAllIrBacklightChannelsOn");
CONSTANT_STRING(set_all_ir_backlight_channels_off_callback_name,"setAllIrBacklightChannelsOff");
CONSTANT_STRING(set_all_visible_backlight_channels_on_callback_name,"setAllVisibleBacklightChannelsOn");
CONSTANT_STRING(set_all_visible_backlight_channels_off_callback_name,"setAllVisibleBacklightChannelsOff");
CONSTANT_STRING(set_all_high_voltage_channels_on_callback_name,"setAllHighVoltageChannelsOn");
CONSTANT_STRING(set_all_high_voltage_channels_off_callback_name,"setAllHighVoltageChannelsOff");
CONSTANT_STRING(set_all_low_voltage_channels_on_callback_name,"setAllLowVoltageChannelsOn");
CONSTANT_STRING(set_all_low_voltage_channels_off_callback_name,"setAllLowVoltageChannelsOff");

// Errors
}
}
