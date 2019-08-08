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
  .version_minor=2,
};

const long channel_count = CHANNEL_COUNT;

const size_t enable_all_pin = 0;

const size_t channel_pins[CHANNEL_COUNT] =
{
  2,
  7,
  8,
  14,
  35,
  36,
  37,
  38,
  5,
  6,
  9,
  10,
  20,
  21,
  22,
  23,
};

const bool analog_writeable[CHANNEL_COUNT] =
{
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
};

const size_t ir_backlight_channels[IR_BACKLIGHT_COUNT] =
{
  8,
  10,
  12,
  14,
};

const size_t visible_backlight_channels[VISIBLE_BACKLIGHT_COUNT] =
{
  9,
  11,
  13,
  15,
};

const size_t high_voltage_channels[HIGH_VOLTAGE_COUNT] =
{
  0,
  1,
  2,
  3,
};

const size_t low_voltage_channels[LOW_VOLTAGE_COUNT] =
{
  4,
  5,
  6,
  7,
};

// Pins

// Units

// Properties
const double ir_backlight_power_to_intensity_ratio_default[IR_BACKLIGHT_COUNT] =
{
  ir_backlight_power_to_intensity_ratio_element_default,
  ir_backlight_power_to_intensity_ratio_element_default,
  ir_backlight_power_to_intensity_ratio_element_default,
  ir_backlight_power_to_intensity_ratio_element_default,
};

const double ir_backlight_intensity_max_default[IR_BACKLIGHT_COUNT] =
{
  ir_backlight_intensity_max_element_default,
  ir_backlight_intensity_max_element_default,
  ir_backlight_intensity_max_element_default,
  ir_backlight_intensity_max_element_default,
};

const double visible_backlight_power_to_intensity_ratio_default[VISIBLE_BACKLIGHT_COUNT] =
{
  visible_backlight_power_to_intensity_ratio_element_default,
  visible_backlight_power_to_intensity_ratio_element_default,
  visible_backlight_power_to_intensity_ratio_element_default,
  visible_backlight_power_to_intensity_ratio_element_default,
};

const double visible_backlight_intensity_max_default[VISIBLE_BACKLIGHT_COUNT] =
{
  visible_backlight_intensity_max_element_default,
  visible_backlight_intensity_max_element_default,
  visible_backlight_intensity_max_element_default,
  visible_backlight_intensity_max_element_default,
};

const double high_voltage_power_max_default[HIGH_VOLTAGE_COUNT] =
{
  high_voltage_power_max_element_default,
  high_voltage_power_max_element_default,
  high_voltage_power_max_element_default,
  high_voltage_power_max_element_default,
};

const double low_voltage_power_max_default[LOW_VOLTAGE_COUNT] =
{
  low_voltage_power_max_element_default,
  low_voltage_power_max_element_default,
  low_voltage_power_max_element_default,
  low_voltage_power_max_element_default,
};

const long ir_backlight_switching_frequency_max_default[IR_BACKLIGHT_COUNT] =
{
  ir_backlight_switching_frequency_max_element_default,
  ir_backlight_switching_frequency_max_element_default,
  ir_backlight_switching_frequency_max_element_default,
  ir_backlight_switching_frequency_max_element_default,
};

const long visible_backlight_switching_frequency_max_default[VISIBLE_BACKLIGHT_COUNT] =
{
  visible_backlight_switching_frequency_max_element_default,
  visible_backlight_switching_frequency_max_element_default,
  visible_backlight_switching_frequency_max_element_default,
  visible_backlight_switching_frequency_max_element_default,
};

const long high_voltage_switching_frequency_max_default[HIGH_VOLTAGE_COUNT] =
{
  high_voltage_switching_frequency_max_element_default,
  high_voltage_switching_frequency_max_element_default,
  high_voltage_switching_frequency_max_element_default,
  high_voltage_switching_frequency_max_element_default,
};

const long low_voltage_switching_frequency_max_default[LOW_VOLTAGE_COUNT] =
{
  low_voltage_switching_frequency_max_element_default,
  low_voltage_switching_frequency_max_element_default,
  low_voltage_switching_frequency_max_element_default,
  low_voltage_switching_frequency_max_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
