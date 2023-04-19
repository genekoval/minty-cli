#include "commands.h"
#include "../../parser/parser.h"

#include <detail/bucket.hpp>
#include <detail/client.hpp>

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
            netcore::run([
                no_clobber,
                &id,
                file
            ]() -> ext::task<> {
                const auto config = minty::cli::settings::load();

                auto client = minty::cli::client(config);
                auto repo = co_await client.connect();

                auto objects = minty::cli::object_store(config);
                auto bucket =
                    co_await minty::cli::bucket::connect(*repo, objects);

                if (!file) {
                    co_await bucket.get(id, std::cout);
                    co_return;
                }

                auto path = fs::path(*file);

                if (fs::is_directory(path)) path = path / id.string();
                if (no_clobber && fs::exists(path)) co_return;

                auto out = std::ofstream(path);
                co_await bucket.get(id, out);
            }());
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
