#ifdef USE_ARDUINO

#include "optolink_climate.h"
#include "../optolink.h"

namespace esphome {
namespace optolink {

static const char *const TAG = "optolink.climate";

void OptolinkClimate::setup() {
  ESP_LOGE(TAG, "setup");

  this->current_temperature = 20.0;
  this->target_temperature = 21.0;
  this->mode = climate::CLIMATE_MODE_HEAT;
  this->action = climate::CLIMATE_ACTION_HEATING;
  this->preset = climate::CLIMATE_PRESET_COMFORT;

  this->publish_state();
}

void OptolinkClimate::update() {
  ESP_LOGE(TAG, "update");
  ESP_LOGE(TAG, "this mode: %d", this->mode);
  ESP_LOGE(TAG, "this preset: %d", *this->preset);
}

climate::ClimateTraits OptolinkClimate::traits() {
  auto traits = climate::ClimateTraits();
  traits.set_supports_current_temperature(true);
  traits.set_supported_modes({climate::CLIMATE_MODE_OFF, climate::ClimateMode::CLIMATE_MODE_HEAT});
  traits.set_supported_presets(
      {climate::CLIMATE_PRESET_NONE, climate::CLIMATE_PRESET_COMFORT, climate::CLIMATE_PRESET_ECO});
  traits.set_supports_action(true);
  traits.set_visual_min_temperature(10.0);
  traits.set_visual_max_temperature(30.0);
  traits.set_visual_temperature_step(1);
  return traits;
}

void OptolinkClimate::control(const esphome::climate::ClimateCall &call) {
  ESP_LOGE(TAG, "control");
  if (call.get_mode().has_value()) {
    ESP_LOGE(TAG, "call mode: %d", *call.get_mode());
    this->mode = *call.get_mode();
  }
  if (call.get_preset().has_value()) {
    ESP_LOGE(TAG, "call preset: %d", *call.get_preset());
    this->preset = call.get_preset();
    this->custom_preset.reset();
  }
  if (call.get_target_temperature().has_value()) {
    ESP_LOGE(TAG, "call target_temperature: %f", *call.get_target_temperature());
    this->target_temperature = *call.get_target_temperature();
  }
  this->publish_state();
};

}  // namespace optolink
}  // namespace esphome

#endif
