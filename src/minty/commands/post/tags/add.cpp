#include "commands.h"

#include "../../../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            const UUID::uuid& id,
            const std::vector<UUID::uuid>& tags
        ) -> void {
            auto repo = minty::cli::repo();

            for (const auto& tag : tags) {
                repo.add_post_tag(id, tag);
            }
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
