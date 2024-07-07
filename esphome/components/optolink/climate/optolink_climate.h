#pragma once

#ifdef USE_ARDUINO

#include "esphome/components/climate/climate.h"
#include "esphome/components/climate/climate_traits.h"
#include "../optolink.h"
#include "../datapoint_component.h"

namespace esphome {
namespace optolink {

class OptolinkClimate : public esphome::climate::Climate, public esphome::PollingComponent {
 public:
  OptolinkClimate(Optolink *optolink) {}

 protected:
  void setup() override;
  void update() override;
  climate::ClimateTraits traits() override;
  virtual void control(const esphome::climate::ClimateCall &call);

 private:
};

}  // namespace optolink
}  // namespace esphome

#endif
