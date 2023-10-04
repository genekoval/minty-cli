#include "commands.h"

#include "../../options/opts.h"
#include "../../output/output.h"
#include "../../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace output = minty::cli::output;

using minty::post_query;
using minty::post_sort;
using minty::visibility;

namespace {
    namespace internal {
        auto find(
            const app& app,
            unsigned int from,
            unsigned int size,
            const std::vector<UUID::uuid>& tags,
            bool drafts,
            post_sort sort,
            std::optional<output::format> format,
            bool quiet,
            const std::optional<std::string>& text
        ) -> void {
            const auto query = post_query {
                .from = from,
                .size = size,
                .text = text,
                .tags = tags,
                .visibility = drafts ? visibility::draft : visibility::pub,
                .sort = sort};

            const auto result = minty::cli::repo().get_posts(query);

            output::result(result, format, quiet);
        }
    }
}

namespace minty::subcommands::post {
    auto find() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Search for posts",
            options(
                cli::opts::from(),
                cli::opts::size(),
                cli::opts::tags(),
                flag({"d", "drafts"}, "Search for drafts"),
                option<post_sort>(
                    {"s", "sort-by"},
                    "Result sort",
                    "",
                    post_sort::created()
                ),
                cli::opts::output(),
                cli::opts::quiet()
            ),
            arguments(optional<std::string>("text")),
            internal::find
        );
    }
}
