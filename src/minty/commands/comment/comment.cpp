#include "../../options/opts.h"
#include "../../parser/parser.h"
#include "../commands.h"
#include "commands.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto comment(
            const app& app,
            bool json,
            bool quiet,
            const UUID::uuid& id
        ) -> void {
            const auto comment = minty::cli::get_comment(id);
            minty::cli::output::entity(comment, json, !quiet);
        }
    }
}

namespace minty::commands {
    auto comment() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "Read a comment",
            options(cli::opts::json(), cli::opts::quiet()),
            arguments(required<UUID::uuid>("id")),
            internal::comment
        );

        cmd->subcommand(subcommands::comment::add());
        cmd->subcommand(subcommands::comment::edit());
        cmd->subcommand(subcommands::comment::rm());

        return cmd;
    }
}
