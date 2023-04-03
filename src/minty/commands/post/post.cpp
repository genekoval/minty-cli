#include "commands.h"

#include "../commands.h"
#include "../../options/opts.h"
#include "../../output/output.h"
#include "../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto post(
            const app& app,
            bool json,
            bool quiet,
            const UUID::uuid& id
        ) -> void {
            minty::cli::repo([
                json,
                quiet,
                &id
            ](minty::repo& repo) -> ext::task<> {
                const auto post = co_await repo.get_post(id);
                minty::cli::output::entity(post, json, !quiet);
            });
        }
    }
}

namespace minty::commands {
    auto post() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "View or edit a post",
            options(
                cli::opts::json(),
                cli::opts::quiet()
            ),
            arguments(
                required<UUID::uuid>("id")
            ),
            internal::post
        );

        cmd->subcommand(subcommands::post::add());
        cmd->subcommand(subcommands::post::desc());
        cmd->subcommand(subcommands::post::find());
        cmd->subcommand(subcommands::post::objects());
        cmd->subcommand(subcommands::post::related());
        cmd->subcommand(subcommands::post::rm());
        cmd->subcommand(subcommands::post::tags());
        cmd->subcommand(subcommands::post::title());

        return cmd;
    }
}
