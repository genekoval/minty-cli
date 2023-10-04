#include "../../parser/parser.h"
#include "commands.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            const UUID::uuid& post,
            std::string_view content
        ) -> void {
            const auto result = minty::cli::repo().add_comment(post, content);
            fmt::print("{}\n", result.id);
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
