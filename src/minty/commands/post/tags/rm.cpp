#include "commands.h"

#include "../../../client.h"
#include "../../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto rm(
            const app& app,
            const UUID::uuid& id,
            const std::vector<UUID::uuid>& tags
        ) -> void {
            minty::cli::client([&id, &tags](auto& api) -> ext::task<> {
                for (const auto& tag : tags) {
                    co_await api.delete_post_tag(id, tag);
                }
            });
        }
    }
}

namespace minty::subcommands::post_tags {
    auto rm() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Remove tags from a post",
            options(),
            arguments(
                required<UUID::uuid>("id"),
                variadic<UUID::uuid>("tags")
            ),
            internal::rm
        );
    }
}
