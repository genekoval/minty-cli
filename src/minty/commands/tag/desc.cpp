#include "commands.h"

#include "../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto desc(
            const app& app,
            bool clear,
            const UUID::uuid& id,
            std::optional<std::string_view> description
        ) -> void {
            minty::cli::api([
                clear,
                &id,
                description
            ](minty::api& api) -> ext::task<> {
                if (clear) {
                    co_await api.set_tag_description(id, "");
                    co_return;
                }

                if (!description) {
                    throw cli_error("no description given");
                }

                const auto result =
                    co_await api.set_tag_description(id, *description);

                if (result) fmt::print("{}\n", *result);
            });
        }
    }
}

namespace minty::subcommands::tag {
    auto desc() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Set a tag's description",
            options(
                flag(
                    {"c", "clear"},
                    "Erase the description"
                )
            ),
            arguments(
                required<UUID::uuid>("id"),
                optional<std::string_view>("description")
            ),
            internal::desc
        );
    }
}
