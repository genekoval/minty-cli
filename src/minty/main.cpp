#include "client.h"
#include "commands/commands.h"
#include "settings/settings.h"

#include <detail/env.h>

#include <iostream>
#include <filesystem>
#include <minty/minty>
#include <minty/error.h>
#include <timber/timber>

namespace fs = std::filesystem;

namespace {
    auto get_config() -> fs::path {
        const auto confdir = minty::env::config()
            .value_or(minty::env::home() / ".config" / NAME);

        return confdir / NAME".yml";
    }

    auto load_config() -> minty::cli::settings {
        const auto confpath = get_config();
        const auto config = minty::cli::settings::load(confpath);

        timber::reporting_level = config.log.level;
        TIMBER_DEBUG(R"(Loaded configuration from: "{}")", confpath.native());

        return config;
    }

    auto config() -> const minty::cli::settings& {
        static const auto instance = load_config();
        return instance;
    }

    namespace internal {
        auto main(const commline::app& app, bool version) -> void {
            if (!version) {
                std::cout << app.name << ": " << app.description << std::endl;
                return;
            }

            commline::print_version(std::cout, app);

            auto api = minty::cli::client();
            const auto server_info = api.get_server_info();
            std::cout << "server version: " << server_info.version << std::endl;
        }
    }
}

namespace minty::cli {
    auto bucket() -> fstore::bucket {
        static auto object_store = fstore::object_store(
            config().server.objects
        );

        const auto source = client().get_server_info().object_source;

        return fstore::bucket(object_store, source.bucket_id);
    }

    auto client() -> api {
        return api(config().server.host);
    }
}

auto main(int argc, const char** argv) -> int {
    using namespace commline;

    timber::reporting_level = timber::level::info;
    timber::log_handler = &timber::console_logger;

    auto app = application(
        NAME,
        VERSION,
        DESCRIPTION,
        options(
            flag(
                {"v", "version"},
                "Print version information"
            )
        ),
        arguments(),
        internal::main
    );

    app.subcommand(minty::commands::comment());
    app.subcommand(minty::commands::object());
    app.subcommand(minty::commands::post());
    app.subcommand(minty::commands::reply());
    app.subcommand(minty::commands::tag());

    return app.run(argc, argv);
}
