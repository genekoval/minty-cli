#include "commands.h"

#include "../../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto desc(
            const app& app,
            const UUID::uuid& id,
            std::optional<std::string_view> description
        ) -> void {
            auto repo = minty::cli::repo();

            if (description) {
                const auto result = repo.set_post_description(id, *description);

                if (!result.new_value.empty())
                    fmt::print("{}\n", result.new_value);
                return;
            }
            else {
                const auto post = repo.get_post(id);

                if (!post.description.empty())
                    fmt::print("{}\n", post.description);
                return;
            }

            throw std::runtime_error(fmt::format("{}: no such post", id));
        }
    }
}

namespace minty::subcommands::post {
    auto desc() -> std::unique_ptr<commline::command_node> {
        return command(
            __FUNCTION__,
            "Set a post's description",
            options(),
            arguments(
                required<UUID::uuid>("id"),
                optional<std::string_view>("description")
            ),
            internal::desc
        );
    }
}
