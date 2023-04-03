#include "commands.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            std::string_view name
        ) -> void {
            minty::cli::repo([name](minty::repo& repo) -> ext::task<> {
                const auto id = co_await repo.add_tag(name);
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
