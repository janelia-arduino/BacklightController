// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef BACKLIGHT_CONTROLLER_3X2_CONSTANTS_H
#define BACKLIGHT_CONTROLLER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace backlight_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PIN_COUNT_MAX=1};

enum {CHANNEL_COUNT=10};
enum {IR_BACKLIGHT_COUNT=1};
enum {VISIBLE_BACKLIGHT_COUNT=1};
enum {HIGH_VOLTAGE_COUNT=4};
enum {LOW_VOLTAGE_COUNT=4};

extern const size_t channel_pins[CHANNEL_COUNT];
extern const bool analog_writeable[CHANNEL_COUNT];

extern const size_t ir_backlight_channels[IR_BACKLIGHT_COUNT];
extern const size_t visible_backlight_channels[VISIBLE_BACKLIGHT_COUNT];
extern const size_t high_voltage_channels[HIGH_VOLTAGE_COUNT];
extern const size_t low_voltage_channels[LOW_VOLTAGE_COUNT];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const double ir_backlight_power_to_intensity_ratio_default[IR_BACKLIGHT_COUNT];

extern const double ir_backlight_intensity_max_default[IR_BACKLIGHT_COUNT];

extern const double visible_backlight_power_to_intensity_ratio_default[VISIBLE_BACKLIGHT_COUNT];

extern const double visible_backlight_intensity_max_default[VISIBLE_BACKLIGHT_COUNT];

extern const double high_voltage_power_max_default[HIGH_VOLTAGE_COUNT];

extern const double low_voltage_power_max_default[LOW_VOLTAGE_COUNT];

extern const long ir_backlight_switching_frequency_max_default[IR_BACKLIGHT_COUNT];

extern const long visible_backlight_switching_frequency_max_default[VISIBLE_BACKLIGHT_COUNT];

extern const long high_voltage_switching_frequency_max_default[HIGH_VOLTAGE_COUNT];

extern const long low_voltage_switching_frequency_max_default[LOW_VOLTAGE_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
