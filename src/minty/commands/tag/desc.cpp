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
                const auto result = repo.set_tag_description(id, *description);

                if (!result.empty()) fmt::print("{}\n", result);
                return;
            }
            else {
                const auto tag = repo.get_tag(id);

                if (!tag.description.empty())
                    fmt::print("{}\n", tag.description);
                return;
            }

            throw std::runtime_error(fmt::format("{}: no such tag", id));
        }
    }
}

namespace minty::subcommands::tag {
    auto desc() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Set a tag's description",
            options(),
            arguments(
                required<UUID::uuid>("id"),
                optional<std::string_view>("description")
            ),
            internal::desc
        );
    }
}
