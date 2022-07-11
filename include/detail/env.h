#pragma once

#include <optional>
#include <filesystem>

namespace minty::env {
    auto config() -> std::optional<std::filesystem::path>;

    auto home() -> std::filesystem::path;
}
