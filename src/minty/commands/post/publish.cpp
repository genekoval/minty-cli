#include "commands.h"

#include "../../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto publish(
            const app& app,
            const UUID::uuid& draft
        ) -> void {
            minty::cli::repo().create_post(draft);
        }
    }
}

namespace minty::subcommands::post {
    auto publish() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Make a post draft visible",
            options(),
            arguments(
                required<UUID::uuid>("draft")
            ),
            internal::publish
        );
    }
}
