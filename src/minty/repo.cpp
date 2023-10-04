#include "client.h"
#include "output.h"

#include <detail/repo.hpp>

#include <ext/string.h>
#include <iostream>

using client = minty::cli::client;

namespace {
    template <typename Entity, typename ID = decltype(Entity::id)>
    auto get_entity(
        client& repo,
        const ID& id,
        std::string_view description,
        auto (client::* fn)(const ID&) -> std::optional<Entity>
    ) -> Entity {
        if (auto entity = (repo.*fn)(id)) { return std::move(*entity); }

        throw std::system_error(
            std::make_error_code(std::errc::no_such_file_or_directory),
            fmt::format("{}: No such {}", id, description)
        );
    }
}

namespace minty::cli {
    auto get_comment(const UUID::uuid& id) -> comment {
        auto repo = cli::repo();
        return get_comment(repo, id);
    }

    auto get_comment(client& repo, const UUID::uuid& id) -> comment {
        return get_entity(repo, id, "comment", &client::get_comment);
    }

    auto get_object(const UUID::uuid& id) -> object {
        auto repo = cli::repo();
        return get_object(repo, id);
    }

    auto get_object(client& repo, const UUID::uuid& id) -> object {
        return get_entity(repo, id, "object", &client::get_object);
    }

    auto get_post(const UUID::uuid& id) -> post {
        auto repo = cli::repo();
        return get_post(repo, id);
    }

    auto get_post(client& repo, const UUID::uuid& id) -> post {
        return get_entity(repo, id, "post", &client::get_post);
    }

    auto get_tag(const UUID::uuid& id) -> tag {
        auto repo = cli::repo();
        return get_tag(repo, id);
    }

    auto get_tag(client& repo, const UUID::uuid& id) -> tag {
        return get_entity(repo, id, "tag", &client::get_tag);
    }

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
