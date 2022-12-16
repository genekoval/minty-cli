#pragma once

#include <optional>
#include <filesystem>

namespace minty::env {
    auto config() -> std::filesystem::path;

    auto home() -> std::filesystem::path;

    auto width() -> unsigned long;
}
