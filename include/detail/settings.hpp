#pragma once

#include <filesystem>
#include <timber/timber>

namespace minty::cli {
    struct settings {
        struct log_config {
            timber::level level = timber::level::info;
        };

        struct server_config {
            std::string objects;
            std::string host;
        };

        log_config log;
        server_config server;

        static auto load() -> settings;
        static auto load(std::string_view text) -> settings;
        static auto load(const std::filesystem::path& path) -> settings;
    };
}
