#include "commands.h"
#include "../../client.h"
#include "../../parser/parser.h"

#include <fstream>

using namespace commline;

namespace fs = std::filesystem;

namespace {
    namespace internal {
        auto get(
            const app& app,
            bool no_clobber,
            const UUID::uuid& id,
            std::optional<std::string_view> file
        ) -> void {
            minty::cli::bucket([
                no_clobber,
                &id,
                file
            ](auto& bucket) -> ext::task<> {
                if (!file) {
                    co_await bucket.get(id, std::cout);
                    co_return;
                }

                auto path = fs::path(*file);

                if (fs::is_directory(path)) path = path / id.string();
                if (no_clobber && fs::exists(path)) co_return;

                auto out = std::ofstream(path);
                co_await bucket.get(id, out);
            });
        }
    }
}

namespace minty::subcommands::obj {
    auto get() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Download an object's data",
            options(
                flag({"n", "no-clobber"}, "Do not overwrite an existing file")
            ),
            arguments(
                required<UUID::uuid>("id"),
                optional<std::string_view>("file")
            ),
            internal::get
        );
    }
}
