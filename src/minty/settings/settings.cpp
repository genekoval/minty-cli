#include "yaml.hpp"

#include <detail/env.hpp>

namespace fs = std::filesystem;

namespace minty::cli {
    auto settings::load() -> settings {
        const auto path = env::config() / "minty.yml";
        const auto config = load(path);

        timber::reporting_level = config.log.level;
        TIMBER_DEBUG(R"(Loaded configuration from: "{}")", path.native());

        return config;
    }

    auto settings::load(std::string_view text) -> settings {
        return YAML::Load(text.data()).as<settings>();
    }

    auto settings::load(const fs::path& path) -> settings {
        return YAML::LoadFile(path.c_str()).as<settings>();
    }
}
