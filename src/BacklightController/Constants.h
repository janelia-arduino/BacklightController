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
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=4};
enum{FUNCTION_COUNT_MAX=7};
enum{CALLBACK_COUNT_MAX=8};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const long channel_count;

extern const size_t enable_all_pin;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters
extern ConstantString ir_backlight_channel_parameter_name;

extern ConstantString visible_backlight_channel_parameter_name;

extern ConstantString high_power_channel_parameter_name;

extern ConstantString low_power_channel_parameter_name;

// Functions
extern ConstantString set_all_ir_backlight_channels_on_at_power_function_name;
extern ConstantString set_ir_backlight_channel_on_function_name;
extern ConstantString set_ir_backlight_channel_on_at_power_function_name;
extern ConstantString set_ir_backlight_channel_off_function_name;
extern ConstantString set_all_visible_backlight_channels_on_at_power_function_name;
extern ConstantString set_all_high_power_channels_on_at_power_function_name;
extern ConstantString set_all_low_power_channels_on_at_power_function_name;

// Callbacks
extern ConstantString set_all_ir_backlight_channels_on_callback_name;
extern ConstantString set_all_ir_backlight_channels_off_callback_name;
extern ConstantString set_all_visible_backlight_channels_on_callback_name;
extern ConstantString set_all_visible_backlight_channels_off_callback_name;
extern ConstantString set_all_high_power_channels_on_callback_name;
extern ConstantString set_all_high_power_channels_off_callback_name;
extern ConstantString set_all_low_power_channels_on_callback_name;
extern ConstantString set_all_low_power_channels_off_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
