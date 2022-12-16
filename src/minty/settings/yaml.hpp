#pragma once

#include <detail/settings.hpp>

#include <conftools/yaml.h>

namespace YAML {
    CONVERT(minty::cli::settings::log_config);
    CONVERT(minty::cli::settings::server_config);
    CONVERT(minty::cli::settings);
}
