#pragma once

#include <commline/commline>

namespace minty::subcommands::obj {
    auto get() -> std::unique_ptr<commline::command_node>;
}
