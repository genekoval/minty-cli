#pragma once

#include <fstore/client.h>
#include <minty/minty>
#include <yaml-cpp/yaml.h>

namespace minty::cli {
    auto bucket(std::function<ext::task<>(fstore::bucket&)>&& action) -> void;

    auto client(std::function<ext::task<>(api&)>&& action) -> void;

    auto print_yaml(
        const YAML::Emitter& emitter,
        std::optional<std::string_view> path
    ) -> void;

    template <typename T>
    auto print(
        T&& t,
        std::optional<std::string_view> path = {}
    ) -> void {
        auto out = YAML::Emitter();
        out << t;
        print_yaml(out, path);
    }
}
