#include "commands.h"

#include "../../client.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto desc(
            const app& app,
            bool clear,
            const UUID::uuid& id,
            std::optional<std::string_view> description
        ) -> void {
            minty::cli::client([
                clear,
                &id,
                description
            ](auto& api) -> ext::task<> {
                if (clear) {
                    co_await api.set_post_description(id, "");
                    co_return;
                }

                if (!description) {
                    throw cli_error("no description given");
                }

                const auto [modified, result] =
                    co_await api.set_post_description(id, *description);

                if (result) fmt::print("{}\n", *result);
            });
        }
    }
}

namespace minty::subcommands::post {
    auto desc() -> std::unique_ptr<commline::command_node> {
        return command(
            __FUNCTION__,
            "Set a post's description",
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
