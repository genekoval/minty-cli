#include "commands.h"

#include "../commands.h"
#include "../../../client.h"
#include "../../../output.h"
#include "../../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto tags(
            const app& app,
            const UUID::uuid& id
        ) -> void {
            minty::cli::client([&id](auto& api) -> ext::task<> {
                const auto post = co_await api.get_post(id);

                minty::cli::print(post.tags);
            });
        }
    }
}

namespace minty::subcommands::post {
    auto tags() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "Get a post's tags",
            options(),
            arguments(
                required<UUID::uuid>("id")
            ),
            internal::tags
        );

        cmd->subcommand(post_tags::add());
        cmd->subcommand(post_tags::rm());

        return cmd;
    }
}
