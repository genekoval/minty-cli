#include "commands.h"

#include "../commands.h"
#include "../../../client.h"
#include "../../../output.h"
#include "../../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto related(
            const app& app,
            const UUID::uuid& id
        ) -> void {
            minty::cli::api([&id](minty::api& api) -> ext::task<> {
                const auto post = co_await api.get_post(id);

                minty::cli::print(post.posts);
            });
        }
    }
}

namespace minty::subcommands::post {
    auto related() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "Get a post's related posts",
            options(),
            arguments(
                required<UUID::uuid>("id")
            ),
            internal::related
        );

        cmd->subcommand(post_related::add());
        cmd->subcommand(post_related::rm());

        return cmd;
    }
}
