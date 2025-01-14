#include "commands.h"

#include "../../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto rm(const app& app, const UUID::uuid& id) -> void {
            minty::cli::repo().delete_tag(id);
        }
    }
}

namespace minty::subcommands::tag {
    auto rm() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Remove a tag",
            options(),
            arguments(required<UUID::uuid>("id")),
            internal::rm
        );
    }
}
