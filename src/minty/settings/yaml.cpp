#include "yaml.hpp"

namespace c = conftools;

using namespace minty::cli;

namespace YAML {
    DECODE(
        settings::log_config,
        c::optional("level", &settings::log_config::level)
    );

    DECODE(
        settings::server_config,
        c::required("host", &settings::server_config::host),
        c::optional("objects", &settings::server_config::objects)
    );

    DECODE(
        settings,
        c::optional("log", &settings::log),
        c::required("server", &settings::server)
    );
}
