import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate
from esphome.components.optolink.select import select
from esphome.const import (
    CONF_ID,
    CONF_MODE,
)
from .. import SENSOR_BASE_SCHEMA, optolink_ns, CONF_OPTOLINK_ID

DEPENDENCIES = ["optolink"]
CODEOWNERS = ["@j0ta29"]


OptolinkClimate = optolink_ns.class_(
    "OptolinkClimate", climate.Climate, cg.PollingComponent
)


CONFIG_SCHEMA = (
    climate.CLIMATE_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(OptolinkClimate),
            cv.Optional(CONF_MODE): cv.use_id(select.Select),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(SENSOR_BASE_SCHEMA)
)


async def to_code(config):
    component = await cg.get_variable(config[CONF_OPTOLINK_ID])
    var = cg.new_Pvariable(config[CONF_ID], component)

    await cg.register_component(var, config)
    await climate.register_climate(var, config)
