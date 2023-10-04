#include <detail/env.hpp>

#include <minty/minty>
#include <timber/timber>

namespace fs = std::filesystem;

namespace {
    namespace defaults {
        constexpr auto width = 80ul;
    }

    auto get(const char* name) -> std::optional<std::string_view> {
        const auto* value = std::getenv(name);

        if (value) return value;
        return {};
    }

    auto require(const char* name) -> std::string_view {
        const auto value = get(name);

        if (value) return *value;

        throw minty::minty_error(
            "required environment variable '{}' not set",
            name
        );
    }
}

namespace minty::env {
    auto config() -> fs::path {
        constexpr auto name = "MINTY_CONFIG";

        const auto value = std::optional<fs::path>(get(name));

        return value.value_or(home() / ".config" / "minty");
    }

    auto home() -> fs::path { return require("HOME"); }

    auto width() -> unsigned long {
        constexpr auto name = "MINTY_WIDTH";
        const auto value = get(name);

        if (value) {
            try {
                return std::stoul(value->data());
            }
            catch (const std::invalid_argument& ex) {
                TIMBER_ERROR(
                    "invalid value for environment variable '{}'",
                    name
                );
            }
        }

        return defaults::width;
    }
}
