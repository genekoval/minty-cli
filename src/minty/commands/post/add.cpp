#include "commands.h"

#include "../../options/opts.h"
#include "../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto add(
            const app& app,
            const std::string& title,
            const std::string& description,
            const std::vector<UUID::uuid>& tags,
            const std::vector<std::string_view>& objects
        ) -> void {
            minty::cli::api([&](minty::api& api) -> ext::task<> {
                const auto id = co_await api.create_post_draft();

                if (!title.empty()) {
                    co_await api.set_post_title(id, title);
                }

                if (!description.empty()) {
                    co_await api.set_post_description(id, description);
                }

                for (const auto& tag : tags) {
                    co_await api.add_post_tag(id, tag);
                }

                if (!objects.empty()) {
                    const auto previews = co_await api.add_objects(objects);

                    auto objs = std::vector<UUID::uuid>();
                    objs.reserve(previews.size());

                    std::ranges::transform(
                        previews,
                        std::back_inserter(objs),
                        [](const auto& obj) -> UUID::uuid { return obj.id; }
                    );

                    co_await api.add_post_objects(id, objs, -1);
                }

                co_await api.create_post(id);
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
