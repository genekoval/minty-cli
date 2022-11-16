#include "commands.h"

#include "../../client.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            const UUID::uuid& post,
            std::string_view content
        ) -> void {
            minty::cli::client([
                &post,
                content
            ](auto& api) -> ext::task<> {
                const auto result = co_await api.add_comment(post, content);
                fmt::print("{}\n", result.id);
            });
        }
    }
}

namespace minty::subcommands::comment {
    auto add() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Comment on a post",
            options(),
            arguments(
                required<UUID::uuid>("post"),
                required<std::string_view>("content")
            ),
            internal::add
        );
    }
}
