#pragma once

#include <detail/settings.hpp>

#include <minty/minty>

namespace minty::cli {
    using client = sync::http::repo;

    auto repo() -> client;

    auto repo(const settings& config) -> client;
}
