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
  .version_major=3,
  .version_minor=0,
  .version_patch=1,
};

CONSTANT_STRING(hardware_name,"backlight_controller");

const double analog_write_frequency = 600.0;
const long analog_write_resolution = 8;
const long analog_value_min = 0;
const long analog_value_max = 256;
const long power_resolution = 100;
const double switching_frequency_max = analog_write_frequency * power_resolution;

// Pins

// Units
CONSTANT_STRING(hz_units,"Hz");

// Properties
CONSTANT_STRING(ir_backlight_power_max_property_name,"irBacklightPowerMax");
const double ir_backlight_power_max_element_default = 100.0;

CONSTANT_STRING(visible_backlight_power_max_property_name,"visibleBacklightPowerMax");
const double visible_backlight_power_max_element_default = 100.0;

CONSTANT_STRING(high_voltage_power_max_property_name,"highVoltagePowerMax");
const double high_voltage_power_max_element_default = 100.0;

CONSTANT_STRING(low_voltage_power_max_property_name,"lowVoltagePowerMax");
const double low_voltage_power_max_element_default = 100.0;

CONSTANT_STRING(ir_backlight_switching_frequency_max_property_name,"irBacklightSwitchingFrequencyMax");
const long ir_backlight_switching_frequency_max_element_min = switching_frequency_max;
const long ir_backlight_switching_frequency_max_element_max = switching_frequency_max;
const long ir_backlight_switching_frequency_max_element_default = switching_frequency_max;

CONSTANT_STRING(visible_backlight_switching_frequency_max_property_name,"visibleBacklightSwitchingFrequencyMax");
const long visible_backlight_switching_frequency_max_element_min = switching_frequency_max;
const long visible_backlight_switching_frequency_max_element_max = switching_frequency_max;
const long visible_backlight_switching_frequency_max_element_default = switching_frequency_max;

CONSTANT_STRING(high_voltage_switching_frequency_max_property_name,"highVoltageSwitchingFrequencyMax");
const long high_voltage_switching_frequency_max_element_min = 1000;
const long high_voltage_switching_frequency_max_element_max = 12000;
const long high_voltage_switching_frequency_max_element_default = 12000;

CONSTANT_STRING(low_voltage_switching_frequency_max_property_name,"lowVoltageSwitchingFrequencyMax");
const long low_voltage_switching_frequency_max_element_min = 1000;
const long low_voltage_switching_frequency_max_element_max = switching_frequency_max;
const long low_voltage_switching_frequency_max_element_default = switching_frequency_max;

// Parameters
CONSTANT_STRING(ir_backlight_parameter_name,"ir_backlight");

CONSTANT_STRING(visible_backlight_parameter_name,"visible_backlight");

CONSTANT_STRING(high_voltage_parameter_name,"high_voltage");

CONSTANT_STRING(low_voltage_parameter_name,"low_voltage");

// Functions
CONSTANT_STRING(set_all_ir_backlights_on_at_power_function_name,"setAllIrBacklightsOnAtPower");
CONSTANT_STRING(set_ir_backlight_on_function_name,"setIrBacklightOn");
CONSTANT_STRING(set_ir_backlight_on_at_power_function_name,"setIrBacklightOnAtPower");
CONSTANT_STRING(set_ir_backlight_off_function_name,"setIrBacklightOff");
CONSTANT_STRING(toggle_ir_backlight_function_name,"toggleIrBacklight");
CONSTANT_STRING(get_ir_backlight_powers_when_on_function_name,"getIrBacklightPowersWhenOn");
CONSTANT_STRING(get_ir_backlight_powers_function_name,"getIrBacklightPowers");
CONSTANT_STRING(get_ir_backlight_power_bounds_function_name,"getIrBacklightPowerBounds");

CONSTANT_STRING(set_all_visible_backlights_on_at_power_function_name,"setAllVisibleBacklightsOnAtPower");
CONSTANT_STRING(set_visible_backlight_on_function_name,"setVisibleBacklightOn");
CONSTANT_STRING(set_visible_backlight_on_at_power_function_name,"setVisibleBacklightOnAtPower");
CONSTANT_STRING(set_visible_backlight_off_function_name,"setVisibleBacklightOff");
CONSTANT_STRING(toggle_visible_backlight_function_name,"toggleVisibleBacklight");
CONSTANT_STRING(get_visible_backlight_powers_when_on_function_name,"getVisibleBacklightPowersWhenOn");
CONSTANT_STRING(get_visible_backlight_powers_function_name,"getVisibleBacklightPowers");
CONSTANT_STRING(get_visible_backlight_power_bounds_function_name,"getVisibleBacklightPowerBounds");

CONSTANT_STRING(set_all_high_voltages_on_at_power_function_name,"setAllHighVoltagesOnAtPower");
CONSTANT_STRING(set_high_voltage_on_function_name,"setHighVoltageOn");
CONSTANT_STRING(set_high_voltage_on_at_power_function_name,"setHighVoltageOnAtPower");
CONSTANT_STRING(set_high_voltage_off_function_name,"setHighVoltageOff");
CONSTANT_STRING(toggle_high_voltage_function_name,"toggleHighVoltage");
CONSTANT_STRING(get_high_voltage_powers_when_on_function_name,"getHighVoltagePowersWhenOn");
CONSTANT_STRING(get_high_voltage_powers_function_name,"getHighVoltagePowers");
CONSTANT_STRING(get_high_voltage_power_bounds_function_name,"getHighVoltagePowerBounds");

CONSTANT_STRING(set_all_low_voltages_on_at_power_function_name,"setAllLowVoltagesOnAtPower");
CONSTANT_STRING(set_low_voltage_on_function_name,"setLowVoltageOn");
CONSTANT_STRING(set_low_voltage_on_at_power_function_name,"setLowVoltageOnAtPower");
CONSTANT_STRING(set_low_voltage_off_function_name,"setLowVoltageOff");
CONSTANT_STRING(toggle_low_voltage_function_name,"toggleLowVoltage");
CONSTANT_STRING(get_low_voltage_powers_when_on_function_name,"getLowVoltagePowersWhenOn");
CONSTANT_STRING(get_low_voltage_powers_function_name,"getLowVoltagePowers");
CONSTANT_STRING(get_low_voltage_power_bounds_function_name,"getLowVoltagePowerBounds");

// Callbacks
CONSTANT_STRING(set_all_ir_backlights_on_callback_name,"setAllIrBacklightsOn");
CONSTANT_STRING(set_all_ir_backlights_off_callback_name,"setAllIrBacklightsOff");
CONSTANT_STRING(toggle_all_ir_backlights_callback_name,"toggleAllIrBacklights");
CONSTANT_STRING(set_all_visible_backlights_on_callback_name,"setAllVisibleBacklightsOn");
CONSTANT_STRING(set_all_visible_backlights_off_callback_name,"setAllVisibleBacklightsOff");
CONSTANT_STRING(toggle_all_visible_backlights_callback_name,"toggleAllVisibleBacklights");
CONSTANT_STRING(set_all_high_voltages_on_callback_name,"setAllHighVoltagesOn");
CONSTANT_STRING(set_all_high_voltages_off_callback_name,"setAllHighVoltagesOff");
CONSTANT_STRING(toggle_all_high_voltages_callback_name,"toggleAllHighVoltages");
CONSTANT_STRING(set_all_low_voltages_on_callback_name,"setAllLowVoltagesOn");
CONSTANT_STRING(set_all_low_voltages_off_callback_name,"setAllLowVoltagesOff");
CONSTANT_STRING(toggle_all_low_voltages_callback_name,"toggleAllLowVoltages");

// Errors
}
}
