#include <detail/env.h>

#include <minty/error.h>

namespace {
    auto get(const char* name) -> std::optional<std::string_view> {
        const auto* value = std::getenv(name);

        if (value) return {value};
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
    auto config() -> std::optional<std::filesystem::path> {
        return get("MINTY_CONFIG");
    }

    auto home() -> std::filesystem::path {
        return require("HOME");
    }
}
