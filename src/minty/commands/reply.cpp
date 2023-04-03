#include "commands.h"

#include "../output.h"
#include "../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto reply(
            const app& app,
            const UUID::uuid& comment,
            std::string_view content
        ) -> void {
            minty::cli::repo([
                &comment,
                content
            ](minty::repo& repo) -> ext::task<> {
                const auto result = co_await repo.add_reply(comment, content);
                fmt::print("{}\n", result.id);
            });
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
