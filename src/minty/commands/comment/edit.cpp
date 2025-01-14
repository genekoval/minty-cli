#include "../../parser/parser.h"
#include "commands.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto edit(
            const app& app,
            const UUID::uuid& comment,
            std::string_view content
        ) -> void {
            minty::cli::repo().set_comment_content(comment, content);
        }
    }
}

namespace minty::subcommands::comment {
    auto edit() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Rewrite a comment",
            options(),
            arguments(
                required<UUID::uuid>("comment"),
                required<std::string_view>("content")
            ),
            internal::edit
        );
    }
}
