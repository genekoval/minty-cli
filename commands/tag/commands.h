#pragma once

#include <commline/commline>

namespace minty::subcommands::tag {
    auto add() -> std::unique_ptr<commline::command_node>;

    auto find() -> std::unique_ptr<commline::command_node>;

    auto rm() -> std::unique_ptr<commline::command_node>;
}