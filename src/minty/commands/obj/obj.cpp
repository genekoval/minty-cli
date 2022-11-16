#include "commands.h"

#include "../commands.h"
#include "../../client.h"
#include "../../options/opts.h"
#include "../../output/output.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto obj(
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
                const auto obj = co_await api.get_object(id);
                minty::cli::output::entity(obj, json, !quiet);
            });
        }
    }
}

namespace minty::commands {
    auto obj() -> std::unique_ptr<command_node> {
        auto cmd = command(
            __FUNCTION__,
            "Get information about an object",
            options(
                cli::opts::json(),
                cli::opts::quiet()
            ),
            arguments(
                required<UUID::uuid>("id")
            ),
            internal::obj
        );

        cmd->subcommand(subcommands::obj::get());

        return cmd;
    }
}
