#include "commands.h"

#include "../../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto mv(
            const app& app,
            const std::optional<UUID::uuid>& destination,
            const UUID::uuid& id,
            const std::vector<UUID::uuid>& objects
        ) -> void {
            if (objects.empty()) return;

            minty::cli::api([
                &destination,
                &id,
                &objects
            ](minty::api& api) -> ext::task<> {
                co_await api.move_post_objects(id, objects, destination);
            });
        }
    }
}

namespace minty::subcommands::post_objects {
    auto mv() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Reorder objects within a post.",
            options(
                option<std::optional<UUID::uuid>>(
                    {"d", "destination"},
                    "Move OBJECTS in front of this object",
                    "object"
                )
            ),
            arguments(
                required<UUID::uuid>("id"),
                variadic<UUID::uuid>("objects")
            ),
            internal::mv
        );
    }
}
