#include "commands.h"

#include "../../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto rm(
            const app& app,
            const UUID::uuid& id,
            const std::vector<UUID::uuid>& posts
        ) -> void {
            minty::cli::api([&id, &posts](minty::api& api) -> ext::task<> {
                for (const auto& post : posts) {
                    co_await api.delete_related_post(id, post);
                }
            });
        }
    }
}

namespace minty::subcommands::post_related {
    auto rm() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Remove related posts from a post",
            options(),
            arguments(
                required<UUID::uuid>("id"),
                variadic<UUID::uuid>("posts")
            ),
            internal::rm
        );
    }
}
