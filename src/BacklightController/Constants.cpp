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

CONSTANT_STRING(high_power_power_max_property_name,"highPowerPowerMax");
const long high_power_power_max_element_default = 100;

CONSTANT_STRING(low_power_power_max_property_name,"lowPowerPowerMax");
const long low_power_power_max_element_default = 100;

// Parameters
CONSTANT_STRING(ir_backlight_channel_parameter_name,"ir_backlight_channel");

CONSTANT_STRING(visible_backlight_channel_parameter_name,"visible_backlight_channel");

CONSTANT_STRING(high_power_channel_parameter_name,"high_power_channel");

CONSTANT_STRING(low_power_channel_parameter_name,"low_power_channel");

// Functions
CONSTANT_STRING(set_all_ir_backlight_channels_on_at_power_function_name,"setAllIrBacklightChannelsOnAtPower");
CONSTANT_STRING(set_ir_backlight_channel_on_function_name,"setIrBacklightChannelOn");
CONSTANT_STRING(set_ir_backlight_channel_on_at_power_function_name,"setIrBacklightChannelOnAtPower");
CONSTANT_STRING(set_ir_backlight_channel_off_function_name,"setIrBacklightChannelOff");
CONSTANT_STRING(set_all_visible_backlight_channels_on_at_power_function_name,"setAllVisibleBacklightChannelsOnAtPower");
CONSTANT_STRING(set_visible_backlight_channel_on_function_name,"setVisibleBacklightChannelOn");
CONSTANT_STRING(set_visible_backlight_channel_on_at_power_function_name,"setVisibleBacklightChannelOnAtPower");
CONSTANT_STRING(set_visible_backlight_channel_off_function_name,"setVisibleBacklightChannelOff");
CONSTANT_STRING(set_all_high_power_channels_on_at_power_function_name,"setAllHighPowerChannelsOnAtPower");
CONSTANT_STRING(set_high_power_channel_on_function_name,"setHighPowerChannelOn");
CONSTANT_STRING(set_high_power_channel_on_at_power_function_name,"setHighPowerChannelOnAtPower");
CONSTANT_STRING(set_high_power_channel_off_function_name,"setHighPowerChannelOff");
CONSTANT_STRING(set_all_low_power_channels_on_at_power_function_name,"setAllLowPowerChannelsOnAtPower");
CONSTANT_STRING(set_low_power_channel_on_function_name,"setLowPowerChannelOn");
CONSTANT_STRING(set_low_power_channel_on_at_power_function_name,"setLowPowerChannelOnAtPower");
CONSTANT_STRING(set_low_power_channel_off_function_name,"setLowPowerChannelOff");

// Callbacks
CONSTANT_STRING(set_all_ir_backlight_channels_on_callback_name,"setAllIrBacklightChannelsOn");
CONSTANT_STRING(set_all_ir_backlight_channels_off_callback_name,"setAllIrBacklightChannelsOff");
CONSTANT_STRING(set_all_visible_backlight_channels_on_callback_name,"setAllVisibleBacklightChannelsOn");
CONSTANT_STRING(set_all_visible_backlight_channels_off_callback_name,"setAllVisibleBacklightChannelsOff");
CONSTANT_STRING(set_all_high_power_channels_on_callback_name,"setAllHighPowerChannelsOn");
CONSTANT_STRING(set_all_high_power_channels_off_callback_name,"setAllHighPowerChannelsOff");
CONSTANT_STRING(set_all_low_power_channels_on_callback_name,"setAllLowPowerChannelsOn");
CONSTANT_STRING(set_all_low_power_channels_off_callback_name,"setAllLowPowerChannelsOff");

// Errors
}
}
