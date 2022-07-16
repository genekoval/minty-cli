#include "../commands.h"
#include "../../client.h"
#include "../../options/opts.h"
#include "../../output/output.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto comments(
            const app& app,
            bool json,
            bool quiet,
            const UUID::uuid& post
        ) -> void {
            auto api = minty::cli::client();

            const auto comment_list = api.get_comments(post);

            minty::cli::output::entity(comment_list, json, !quiet);
        }
    }
}

namespace minty::commands {
    auto comments() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Get a post's comments",
            options(
                cli::opts::json(),
                cli::opts::quiet()
            ),
            arguments(
                required<UUID::uuid>("post")
            ),
            internal::comments
        );
    }
}
