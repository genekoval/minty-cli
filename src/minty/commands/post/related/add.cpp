#include "commands.h"

#include "../../../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            const UUID::uuid& id,
            const std::vector<UUID::uuid>& posts
        ) -> void {
            auto repo = minty::cli::repo();

            for (const auto& post : posts) { repo.add_related_post(id, post); }
        }
    }
}

namespace minty::subcommands::post_related {
    auto add() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Add related posts to a post",
            options(),
            arguments(
                required<UUID::uuid>("id"),
                variadic<UUID::uuid>("posts")
            ),
            internal::add
        );
    }
}
