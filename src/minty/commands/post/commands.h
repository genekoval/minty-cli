#pragma once

#include <commline/commline>

namespace minty::subcommands::post {
    auto add() -> std::unique_ptr<commline::command_node>;

    auto desc() -> std::unique_ptr<commline::command_node>;

    auto draft() -> std::unique_ptr<commline::command_node>;

    auto find() -> std::unique_ptr<commline::command_node>;

    auto objects() -> std::unique_ptr<commline::command_node>;

    auto publish() -> std::unique_ptr<commline::command_node>;

    auto related() -> std::unique_ptr<commline::command_node>;

    auto rm() -> std::unique_ptr<commline::command_node>;

    auto tags() -> std::unique_ptr<commline::command_node>;

    auto title() -> std::unique_ptr<commline::command_node>;
}
