// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace backlight_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1270,
  .version_major=1,
  .version_minor=0,
};

const long channel_count = CHANNEL_COUNT;

const size_t enable_all_pin = 52;

const size_t channel_pins[CHANNEL_COUNT] =
{
  2,
  6,
  29,
  30,
  35,
  36,
  22,
  23,
  14,
  15,
  16,
  17,
  18,
  19,
  20,
  21,
};

const size_t ir_backlight_channels[IR_BACKLIGHT_CHANNEL_COUNT] =
{
  8,
  10,
  12,
  14,
};

const size_t visible_backlight_channels[VISIBLE_BACKLIGHT_CHANNEL_COUNT] =
{
  9,
  11,
  13,
  15,
};

const size_t high_power_channels[HIGH_POWER_CHANNEL_COUNT] =
{
  0,
  1,
  2,
  3,
};

const size_t low_power_channels[LOW_POWER_CHANNEL_COUNT] =
{
  4,
  5,
  6,
  7,
};

// Pins

// Units

// Properties
const long ir_backlight_power_max_default[IR_BACKLIGHT_CHANNEL_COUNT] =
{
  ir_backlight_power_max_element_default,
  ir_backlight_power_max_element_default,
  ir_backlight_power_max_element_default,
  ir_backlight_power_max_element_default,
};

const long visible_backlight_power_max_default[VISIBLE_BACKLIGHT_CHANNEL_COUNT] =
{
  visible_backlight_power_max_element_default,
  visible_backlight_power_max_element_default,
  visible_backlight_power_max_element_default,
  visible_backlight_power_max_element_default,
};

const long high_power_power_max_default[HIGH_POWER_CHANNEL_COUNT] =
{
  high_power_power_max_element_default,
  high_power_power_max_element_default,
  high_power_power_max_element_default,
  high_power_power_max_element_default,
};

const long low_power_power_max_default[LOW_POWER_CHANNEL_COUNT] =
{
  low_power_power_max_element_default,
  low_power_power_max_element_default,
  low_power_power_max_element_default,
  low_power_power_max_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
