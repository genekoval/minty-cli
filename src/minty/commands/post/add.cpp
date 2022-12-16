#include "commands.h"

#include "../../options/opts.h"
#include "../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            std::string title,
            std::string description,
            const std::vector<UUID::uuid>& tags,
            const std::vector<std::string_view>& objects
        ) -> void {
            minty::cli::api([
                &title,
                &description,
                &tags,
                &objects
            ](minty::api& api) -> ext::task<> {
                auto parts = minty::core::post_parts {
                    .title = title,
                    .description = description,
                    .tags = tags
                };

                const auto object_previews = co_await api.add_objects(objects);
                std::ranges::transform(
                    object_previews,
                    std::back_inserter(parts.objects),
                    [](const auto& obj) -> UUID::uuid { return obj.id; }
                );

                const auto id = co_await api.add_post(parts);
                fmt::print("{}\n", id);
            });
        }
    }
}

namespace minty::subcommands::post {
    auto add() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Add a post",
            options(
                cli::opts::title(),
                cli::opts::description(),
                cli::opts::tags()
            ),
            arguments(
                variadic<std::string_view>("objects")
            ),
            internal::add
        );
    }
}
