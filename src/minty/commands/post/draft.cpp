#include "commands.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto draft(const app& app) -> void {
            const auto id = minty::cli::repo().create_post_draft();
            fmt::print("{}\n", id);
        }
    }
}

namespace minty::subcommands::post {
    auto draft() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Create a post draft",
            options(),
            arguments(),
            internal::draft
        );
    }
}
