#include "client.h"
#include "commands/commands.h"

#include <detail/repo.hpp>

namespace {
    namespace internal {
        auto main(const commline::app& app, bool version) -> void {
            if (!version) {
                fmt::print("{}: {}\n", app.name, app.description);
                return;
            }

            commline::print_version(std::cout, app);

            const auto info = minty::cli::repo().get_server_info();
            fmt::print("server version: {}\n", info.version);
        }
    }
}

auto main(int argc, char** argv) -> int {
    using namespace commline;

    std::locale::global(std::locale(""));

    timber::reporting_level = timber::level::info;
    timber::log_handler = &timber::console::logger;

    auto app = application(
        NAME,
        VERSION,
        DESCRIPTION,
        options(flag({"v", "version"}, "Print version information")),
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
