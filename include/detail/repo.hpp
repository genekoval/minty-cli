#pragma once

#include <detail/settings.hpp>

#include <minty/minty>

namespace minty::cli {
    auto repo() -> minty::sync::http::repo;

    auto repo(const settings& config) -> minty::sync::http::repo;
}
