#pragma once

#include <detail/settings.hpp>

#include <minty/minty>

namespace minty::cli {
    using client = sync::http::repo;

    auto get_comment(const UUID::uuid& id) -> comment;

    auto get_comment(client& repo, const UUID::uuid& id) -> comment;

    auto get_object(const UUID::uuid& id) -> object;

    auto get_object(client& repo, const UUID::uuid& id) -> object;

    auto get_post(const UUID::uuid& id) -> post;

    auto get_post(client& repo, const UUID::uuid& id) -> post;

    auto get_tag(const UUID::uuid& id) -> tag;

    auto get_tag(client& repo, const UUID::uuid& id) -> tag;

    auto repo() -> client;

    auto repo(const settings& config) -> client;
}
