#include "commands.h"
#include "../commands.h"
#include "../../client.h"
#include "../../options/opts.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto comment(
            const app& app,
            bool json,
            bool quiet,
            const UUID::uuid& id
        ) -> void {
            minty::cli::client([
                json,
                quiet,
                &id
            ](auto& api) -> ext::task<> {
                const auto comment = co_await api.get_comment(id);
                minty::cli::output::entity(comment, json, !quiet);
            });
        }
    }
}

namespace minty::commands {
    auto comment() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "Read a comment",
            options(
                cli::opts::json(),
                cli::opts::quiet()
            ),
            arguments(
                required<UUID::uuid>("id")
            ),
            internal::comment
        );

        cmd->subcommand(subcommands::comment::add());
        cmd->subcommand(subcommands::comment::edit());

        return cmd;
    }
}
