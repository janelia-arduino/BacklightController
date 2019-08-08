// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef BACKLIGHT_CONTROLLER_CONSTANTS_H
#define BACKLIGHT_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <DigitalController.h>


namespace backlight_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=10};
enum{PARAMETER_COUNT_MAX=5};
enum{FUNCTION_COUNT_MAX=46};
enum{CALLBACK_COUNT_MAX=14};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const long channel_count;

extern const size_t enable_all_pin;

extern const double analog_write_frequency;
extern const long analog_write_resolution;
extern const long analog_value_min;
extern const long analog_value_max;
extern const long power_resolution;
extern const double switching_frequency_max;
extern const double intensity_min;
extern const double intensity_max;

extern ConstantString intensity_lower_bound_string;
extern ConstantString intensity_upper_bound_string;

// Pins
extern ConstantString btn_enable_pin_name;
extern const size_t btn_enable_pin_number;

extern ConstantString btn_test_pin_name;
extern const size_t btn_test_pin_number;

// Units
extern ConstantString hz_units;
extern ConstantString intensity_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString ir_backlight_power_to_intensity_ratio_property_name;
extern const double power_to_intensity_ratio_min;
extern const double power_to_intensity_ratio_max;
extern const double ir_backlight_power_to_intensity_ratio_element_default;

extern ConstantString ir_backlight_intensity_max_property_name;
extern const double ir_backlight_intensity_max_element_default;

extern ConstantString visible_backlight_power_to_intensity_ratio_property_name;
extern const double visible_backlight_power_to_intensity_ratio_element_default;

extern ConstantString visible_backlight_intensity_max_property_name;
extern const double visible_backlight_intensity_max_element_default;

extern ConstantString high_voltage_power_max_property_name;
extern const double high_voltage_power_max_element_default;

extern ConstantString low_voltage_power_max_property_name;
extern const double low_voltage_power_max_element_default;

extern ConstantString ir_backlight_switching_frequency_max_property_name;
extern const long ir_backlight_switching_frequency_max_element_min;
extern const long ir_backlight_switching_frequency_max_element_max;
extern const long ir_backlight_switching_frequency_max_element_default;

extern ConstantString visible_backlight_switching_frequency_max_property_name;
extern const long visible_backlight_switching_frequency_max_element_min;
extern const long visible_backlight_switching_frequency_max_element_max;
extern const long visible_backlight_switching_frequency_max_element_default;

extern ConstantString high_voltage_switching_frequency_max_property_name;
extern const long high_voltage_switching_frequency_max_element_min;
extern const long high_voltage_switching_frequency_max_element_max;
extern const long high_voltage_switching_frequency_max_element_default;

extern ConstantString low_voltage_switching_frequency_max_property_name;
extern const long low_voltage_switching_frequency_max_element_min;
extern const long low_voltage_switching_frequency_max_element_max;
extern const long low_voltage_switching_frequency_max_element_default;

// Parameters
extern ConstantString intensity_parameter_name;

extern ConstantString ir_backlight_parameter_name;

extern ConstantString visible_backlight_parameter_name;

extern ConstantString high_voltage_parameter_name;

extern ConstantString low_voltage_parameter_name;

// Functions
extern ConstantString set_all_ir_backlights_on_at_power_function_name;
extern ConstantString set_all_ir_backlights_on_at_intensity_function_name;
extern ConstantString set_ir_backlight_on_function_name;
extern ConstantString set_ir_backlight_on_at_power_function_name;
extern ConstantString set_ir_backlight_on_at_intensity_function_name;
extern ConstantString set_ir_backlight_off_function_name;
extern ConstantString toggle_ir_backlight_function_name;
extern ConstantString get_ir_backlight_powers_when_on_function_name;
extern ConstantString get_ir_backlight_intensities_when_on_function_name;
extern ConstantString get_ir_backlight_powers_function_name;
extern ConstantString get_ir_backlight_intensities_function_name;
extern ConstantString get_ir_backlight_power_bounds_function_name;
extern ConstantString get_ir_backlight_intensity_bounds_function_name;
extern ConstantString ir_backlight_power_to_intensities_function_name;
extern ConstantString ir_backlight_intensity_to_powers_function_name;

extern ConstantString set_all_visible_backlights_on_at_power_function_name;
extern ConstantString set_all_visible_backlights_on_at_intensity_function_name;
extern ConstantString set_visible_backlight_on_function_name;
extern ConstantString set_visible_backlight_on_at_power_function_name;
extern ConstantString set_visible_backlight_on_at_intensity_function_name;
extern ConstantString set_visible_backlight_off_function_name;
extern ConstantString toggle_visible_backlight_function_name;
extern ConstantString get_visible_backlight_powers_when_on_function_name;
extern ConstantString get_visible_backlight_intensities_when_on_function_name;
extern ConstantString get_visible_backlight_powers_function_name;
extern ConstantString get_visible_backlight_intensities_function_name;
extern ConstantString get_visible_backlight_power_bounds_function_name;
extern ConstantString get_visible_backlight_intensity_bounds_function_name;
extern ConstantString visible_backlight_power_to_intensities_function_name;
extern ConstantString visible_backlight_intensity_to_powers_function_name;

extern ConstantString set_all_high_voltages_on_at_power_function_name;
extern ConstantString set_high_voltage_on_function_name;
extern ConstantString set_high_voltage_on_at_power_function_name;
extern ConstantString set_high_voltage_off_function_name;
extern ConstantString toggle_high_voltage_function_name;
extern ConstantString get_high_voltage_powers_when_on_function_name;
extern ConstantString get_high_voltage_powers_function_name;
extern ConstantString get_high_voltage_power_bounds_function_name;

extern ConstantString set_all_low_voltages_on_at_power_function_name;
extern ConstantString set_low_voltage_on_function_name;
extern ConstantString set_low_voltage_on_at_power_function_name;
extern ConstantString set_low_voltage_off_function_name;
extern ConstantString toggle_low_voltage_function_name;
extern ConstantString get_low_voltage_powers_when_on_function_name;
extern ConstantString get_low_voltage_powers_function_name;
extern ConstantString get_low_voltage_power_bounds_function_name;

// Callbacks
extern ConstantString set_all_ir_backlights_on_callback_name;
extern ConstantString set_all_ir_backlights_off_callback_name;
extern ConstantString toggle_all_ir_backlights_callback_name;
extern ConstantString set_all_visible_backlights_on_callback_name;
extern ConstantString set_all_visible_backlights_off_callback_name;
extern ConstantString toggle_all_visible_backlights_callback_name;
extern ConstantString set_all_high_voltages_on_callback_name;
extern ConstantString set_all_high_voltages_off_callback_name;
extern ConstantString toggle_all_high_voltages_callback_name;
extern ConstantString set_all_low_voltages_on_callback_name;
extern ConstantString set_all_low_voltages_off_callback_name;
extern ConstantString toggle_all_low_voltages_callback_name;
extern ConstantString toggle_enable_all_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
