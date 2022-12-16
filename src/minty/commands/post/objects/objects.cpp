#include "commands.h"

#include "../commands.h"
#include "../../../client.h"
#include "../../../output.h"
#include "../../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto objects(
            const app& app,
            const UUID::uuid& id
        ) -> void {
            minty::cli::api([&id](minty::api& api) -> ext::task<> {
                const auto post = co_await api.get_post(id);

                minty::cli::print(post.objects);
            });
        }
    }
}

namespace minty::subcommands::post {
    auto objects() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "Get a post's objects",
            options(),
            arguments(
                required<UUID::uuid>("id")
            ),
            internal::objects
        );

        cmd->subcommand(post_objects::add());
        cmd->subcommand(post_objects::mv());
        cmd->subcommand(post_objects::rm());

        return cmd;
    }
}
