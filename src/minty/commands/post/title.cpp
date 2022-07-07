#include "commands.h"

#include "../../client.h"
#include "../../parser/parser.h"

using namespace commline;

namespace {
    namespace internal {
        auto title(
            const app& app,
            const UUID::uuid& id,
            std::optional<std::string_view> title
        ) -> void {
            auto api = minty::cli::client();

            if (title) api.set_post_title(id, *title);

            const auto post = api.get_post(id);
            if (post.title) std::cout << *post.title << std::endl;
        }
    }
}

namespace minty::subcommands::post {
    auto title() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Get or set a post's title",
            options(),
            arguments(
                required<UUID::uuid>("id"),
                optional<std::string_view>("title")
            ),
            internal::title
        );
    }
}