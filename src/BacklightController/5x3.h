// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef BACKLIGHT_CONTROLLER_5X3_CONSTANTS_H
#define BACKLIGHT_CONTROLLER_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace backlight_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PIN_COUNT_MAX=1};

enum {CHANNEL_COUNT=16};
enum {IR_BACKLIGHT_CHANNEL_COUNT=4};
enum {VISIBLE_BACKLIGHT_CHANNEL_COUNT=4};
enum {HIGH_POWER_CHANNEL_COUNT=4};
enum {LOW_POWER_CHANNEL_COUNT=4};

extern const size_t channel_pins[CHANNEL_COUNT];
extern const size_t ir_backlight_channels[IR_BACKLIGHT_CHANNEL_COUNT];
extern const size_t visible_backlight_channels[VISIBLE_BACKLIGHT_CHANNEL_COUNT];
extern const size_t high_power_channels[HIGH_POWER_CHANNEL_COUNT];
extern const size_t low_power_channels[LOW_POWER_CHANNEL_COUNT];


// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long ir_backlight_power_max_default[IR_BACKLIGHT_CHANNEL_COUNT];

extern const long visible_backlight_power_max_default[VISIBLE_BACKLIGHT_CHANNEL_COUNT];

extern const long high_power_power_max_default[HIGH_POWER_CHANNEL_COUNT];

extern const long low_power_power_max_default[LOW_POWER_CHANNEL_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
