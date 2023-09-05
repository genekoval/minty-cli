#include "commands.h"

#include "../output.h"
#include "../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto reply(
            const app& app,
            const UUID::uuid& comment,
            std::string_view content
        ) -> void {
            const auto result = minty::cli::repo().reply(comment, content);
            fmt::print("{}\n", result.id);
        }
    }
}

namespace minty::commands {
    auto reply() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Create a reply to a comment",
            options(),
            arguments(
                required<UUID::uuid>("comment"),
                required<std::string_view>("content")
            ),
            internal::reply
        );
    }
}
