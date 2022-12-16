#include "commands.h"

#include "../../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            const UUID::uuid& id,
            const std::vector<UUID::uuid>& tags
        ) -> void {
            minty::cli::api([&id, &tags](minty::api& api) -> ext::task<> {
                for (const auto& tag : tags) {
                    co_await api.add_post_tag(id, tag);
                }
            });
        }
    }
}

namespace minty::subcommands::post_tags {
    auto add() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Add tags to a post",
            options(),
            arguments(
                required<UUID::uuid>("id"),
                variadic<UUID::uuid>("tags")
            ),
            internal::add
        );
    }
}
