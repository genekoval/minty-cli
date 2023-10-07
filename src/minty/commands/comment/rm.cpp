#include "../../parser/parser.h"
#include "commands.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto rm(const app& app, bool recursive, const UUID::uuid& comment)
            -> void {
            if (minty::cli::repo().delete_comment(comment, recursive)) {
                return;
            }

            TIMBER_WARNING("Comment {} did not exist", comment);
        }
    }
}

namespace minty::subcommands::comment {
    auto rm() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Remove a comment",
            options(flag(
                {"r", "recursive"},
                "Remove comments and their replies recursively"
            )),
            arguments(required<UUID::uuid>("comment")),
            internal::rm
        );
    }
}
