#pragma once

#include <filesystem>
#include <optional>

namespace minty::env {
    auto config() -> std::filesystem::path;

    auto home() -> std::filesystem::path;

    auto width() -> unsigned long;
}
