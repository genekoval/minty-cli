#include "commands.h"

#include "../../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            const std::optional<UUID::uuid>& insert,
            const UUID::uuid& id,
            const std::vector<std::string_view>& objects
        ) -> void {
            if (objects.empty()) return;

            minty::cli::repo([&](minty::repo& repo) -> ext::task<> {
                auto uploaded = std::vector<UUID::uuid>();
                const auto object_previews = co_await repo.add_objects(objects);
                std::ranges::transform(
                    object_previews,
                    std::back_inserter(uploaded),
                    [](const auto& obj) -> UUID::uuid { return obj.id; }
                );

                if (!uploaded.empty()) {
                    co_await repo.add_post_objects(id, uploaded, insert);
                }
            });
        }
    }
}

namespace minty::subcommands::post_objects {
    auto add() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Add objects to a post",
            options(
                option<std::optional<UUID::uuid>>(
                    {"i", "insert"},
                    "Object to insert in front of",
                    "ID"
                )
            ),
            arguments(
                required<UUID::uuid>("id"),
                variadic<std::string_view>("objects")
            ),
            internal::add
        );
    }
}
