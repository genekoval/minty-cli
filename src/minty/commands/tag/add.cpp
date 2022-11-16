#include "commands.h"

#include "../../client.h"

#include <iostream>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            std::string_view name
        ) -> void {
            minty::cli::client([name](auto& api) -> ext::task<> {
                const auto id = co_await api.add_tag(name);
                fmt::print("{}\n", id);
            });
        }
    }
}

namespace minty::subcommands::tag {
    auto add() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Add a tag",
            options(),
            arguments(
                required<std::string_view>("name")
            ),
            internal::add
        );
    }
}
