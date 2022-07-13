#include "commands.h"

#include "../../client.h"
#include "../../options/opts.h"
#include "../../output/output.h"
#include "../../parser/parser.h"

using namespace commline;

namespace output = minty::cli::output;

namespace {
    namespace internal {
        auto find(
            const app& app,
            unsigned int from,
            unsigned int size,
            const std::vector<UUID::uuid>& tags,
            const minty::core::post_query::sort_type sort,
            const std::optional<output::format>& format,
            bool quiet,
            std::optional<std::string> text
        ) -> void {
            auto api = minty::cli::client();

            const auto query = minty::core::post_query {
                .from = from,
                .size = size,
                .text = text,
                .tags = tags,
                .sort = sort
            };

            const auto result = api.get_posts(query);

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
                option<core::post_query::sort_type>(
                    {"s", "sort-by"},
                    "Result sort",
                    "",
                    {
                        .value = core::post_sort_value::date_created,
                        .order = core::sort_order::descending
                    }
                ),
                cli::opts::output(),
                cli::opts::quiet()
            ),
            arguments(
                optional<std::string>("text")
            ),
            internal::find
        );
    }
}
