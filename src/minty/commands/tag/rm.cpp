#include "commands.h"

#include "../../client.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto rm(
            const app& app,
            const UUID::uuid& id
        ) -> void {
            minty::cli::client([&id](auto& api) -> ext::task<> {
                co_await api.delete_tag(id);
            });
        }
    }
}

namespace minty::subcommands::tag {
    auto rm() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Remove a tag",
            options(),
            arguments(
                required<UUID::uuid>("id")
            ),
            internal::rm
        );
    }
}
