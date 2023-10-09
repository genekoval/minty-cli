#include "commands.h"

#include "../../options/opts.h"
#include "../../output/output.h"
#include "../../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto aka(
            const app& app,
            bool json,
            bool quiet,
            const UUID::uuid& id,
            std::string_view alias
        ) -> void {
            auto repo = minty::cli::repo();
            auto tag = minty::cli::repo().get_tag(id);

            const auto end = tag.aliases.end();
            const auto result =
                std::ranges::find(tag.aliases.begin(), end, alias);

            if (result != end) {
                repo.delete_tag_alias(id, alias);
                tag.aliases.erase(result);
            }
            else {
                repo.add_tag_alias(id, alias);
                tag.aliases.emplace_back(alias);
                std::sort(tag.aliases.begin(), tag.aliases.end());
            }

            minty::cli::output::entity(tag, json, !quiet);
        }
    }
}

namespace minty::subcommands::tag {
    auto aka() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Add or remove a tag's alias",
            options(cli::opts::json(), cli::opts::quiet()),
            arguments(
                required<UUID::uuid>("id"),
                required<std::string_view>("alias")
            ),
            internal::aka
        );
    }
}
