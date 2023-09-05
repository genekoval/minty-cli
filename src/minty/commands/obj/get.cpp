#include "commands.h"
#include "../../parser/parser.h"

#include <detail/repo.hpp>

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
            auto client = minty::cli::repo();

            if (!file) {
                client.get_object_data(id, stdout);
                return;
            }

            auto path = fs::path(*file);

            if (fs::is_directory(path)) path /= id.string();
            if (no_clobber && fs::exists(path)) return;

            client.download_object(id, path);
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
