#pragma once

#include <fmt/color.h>

namespace minty::cli::output::style {
    using fmt::color;
    using fmt::emphasis;
    using fmt::fg;

    constexpr auto interpunct = " · ";
    constexpr auto divider = "----------------------------------------\n";
    constexpr auto index = fg(color::orange_red);
    constexpr auto label = fg(color::plum);
    constexpr auto link = fg(color::steel_blue);
    constexpr auto result = fg(color::yellow_green);
    constexpr auto secondary = fg(color::dim_gray);
    constexpr auto title = emphasis::bold | fg(color::golden_rod);
}
