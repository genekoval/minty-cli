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
            minty::cli::repo([&id, &posts](minty::repo& repo) -> ext::task<> {
                for (const auto& post : posts) {
                    co_await repo.delete_related_post(id, post);
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
