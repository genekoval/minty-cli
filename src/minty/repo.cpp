#include "client.h"
#include "output.h"

#include <detail/repo.hpp>

#include <ext/string.h>
#include <iostream>

using client = minty::cli::client;

namespace minty::cli {
    auto repo() -> client { return repo(settings::load()); }

    auto repo(const settings& config) -> client {
        const auto& server = config.server;

        if (config.server.objects) return {server.host, *server.objects};
        return {server.host};
    }

    auto print_yaml(
        const YAML::Emitter& emitter,
        std::optional<std::string_view> path
    ) -> void {
        const auto* str = emitter.c_str();

        if (!path) {
            std::cout << str << std::endl;
            return;
        }

        auto node = YAML::Load(str);

        for (const auto key : ext::string_range(*path, ".")) {
            const auto k = std::string(key);
            node = node[k];

            if (!node) {
                throw std::runtime_error(
                    "key (" + k + ") does not exist in path"
                );
            }
        }

        const auto result = node.as<std::string>();
        std::cout << result;

        if (!result.ends_with("\n")) std::cout << std::endl;
    }
}
