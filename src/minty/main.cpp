#include "client.h"
#include "commands/commands.h"
#include "settings/settings.h"

#include <detail/env.h>

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
        auto connect(
            std::function<ext::task<>(minty::client&)>&& action
        ) -> void {
            const auto task = [action = std::move(action)]() -> ext::task<> {
                auto client = minty::client(
                    config().server.host,
                    config().server.objects
                );

                co_await action(client);
            };

            netcore::async(task());
        }

        auto main(const commline::app& app, bool version) -> void {
            if (!version) {
                fmt::print("{}: {}\n", app.name, app.description);
                return;
            }

            commline::print_version(std::cout, app);

            minty::cli::client([](auto& api) -> ext::task<> {
                const auto info = co_await api.get_server_info();
                fmt::print("server version: {}\n", info.version);
            });
        }
    }
}

namespace minty::cli {
    auto bucket(std::function<ext::task<>(fstore::bucket&)>&& action) -> void {
        internal::connect([action = std::move(action)](
            auto& client
        ) -> ext::task<> {
            auto object_store = co_await client.object_store();
            auto bucket = co_await client.bucket(object_store.value());
            co_await action(bucket);
        });
    }

    auto client(std::function<ext::task<>(api&)>&& action) -> void {
        internal::connect([action = std::move(action)](
            auto& client
        ) -> ext::task<> {
            auto api = co_await client.connect();
            co_await action(api.value());
        });
    }
}

auto main(int argc, const char** argv) -> int {
    using namespace commline;

    std::locale::global(std::locale(""));

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
    app.subcommand(minty::commands::comments());
    app.subcommand(minty::commands::obj());
    app.subcommand(minty::commands::post());
    app.subcommand(minty::commands::reply());
    app.subcommand(minty::commands::tag());

    return app.run(argc, argv);
}
