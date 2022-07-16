#include "commands.h"

#include "../commands.h"
#include "../../client.h"
#include "../../options/opts.h"
#include "../../output/output.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto post(
            const app& app,
            bool json,
            bool quiet,
            const UUID::uuid& id
        ) -> void {
            auto api = minty::cli::client();

            const auto post = api.get_post(id);

            minty::cli::output::entity(post, json, !quiet);
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
        cmd->subcommand(subcommands::post::description());
        cmd->subcommand(subcommands::post::find());
        cmd->subcommand(subcommands::post::objects());
        cmd->subcommand(subcommands::post::related());
        cmd->subcommand(subcommands::post::rm());
        cmd->subcommand(subcommands::post::tags());
        cmd->subcommand(subcommands::post::title());

        return cmd;
    }
}
