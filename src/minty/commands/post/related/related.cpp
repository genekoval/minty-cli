#include "commands.h"

#include "../../../client.h"
#include "../../../output.h"
#include "../../../parser/parser.h"
#include "../commands.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto related(const app& app, const UUID::uuid& id) -> void {
            const auto post = minty::cli::repo().get_post(id);
            minty::cli::print(post.posts);
        }
    }
}

namespace minty::subcommands::post {
    auto related() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "Get a post's related posts",
            options(),
            arguments(required<UUID::uuid>("id")),
            internal::related
        );

        cmd->subcommand(post_related::add());
        cmd->subcommand(post_related::rm());

        return cmd;
    }
}
