#include "commands.h"

#include "../../client.h"
#include "../../options/opts.h"
#include "../../output/output.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto tag(
            const app& app,
            bool json,
            bool quiet,
            const UUID::uuid& id
        ) -> void {
            minty::cli::client([json, quiet, &id](auto& api) -> ext::task<> {
                const auto tag = co_await api.get_tag(id);
                minty::cli::output::entity(tag, json, !quiet);
            });
        }
    }
}

namespace minty::commands {
    auto tag() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "View a tag",
            options(
                cli::opts::json(),
                cli::opts::quiet()
            ),
            arguments(
                required<UUID::uuid>("id")
            ),
            internal::tag
        );

        cmd->subcommand(subcommands::tag::add());
        cmd->subcommand(subcommands::tag::aka());
        cmd->subcommand(subcommands::tag::desc());
        cmd->subcommand(subcommands::tag::find());
        cmd->subcommand(subcommands::tag::ln());
        cmd->subcommand(subcommands::tag::rename());
        cmd->subcommand(subcommands::tag::rm());

        return cmd;
    }
}
