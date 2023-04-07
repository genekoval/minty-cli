#pragma once

#include "type.h"

#include <minty/minty>
#include <nlohmann/json.hpp>

namespace minty {
    NLOHMANN_JSON_SERIALIZE_ENUM(visibility, {
        {visibility::invalid, nullptr},
        {visibility::draft, "draft"},
        {visibility::pub, "public"}
    })

    template <typename T>
    auto from_json(const nlohmann::json& j, search_result<T>& r) -> void {
        j.get_to(r.hits);
        j.get_to(r.total);
    }

    template <typename T>
    auto to_json(nlohmann::json& j, const search_result<T>& r) -> void {
        j["hits"] = r.hits;
        j["total"] = r.total;
    }

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        comment,
        id,
        post_id,
        parent_id,
        indent,
        content,
        date_created
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        comment_data,
        id,
        content,
        indent,
        date_created
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        data_size,
        bytes,
        formatted
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        object_preview,
        id,
        preview_id,
        type,
        subtype
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        post_preview,
        id,
        title,
        preview,
        comment_count,
        object_count,
        date_created
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        tag_preview,
        id,
        name,
        avatar
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        post,
        id,
        title,
        description,
        visibility,
        date_created,
        date_modified,
        objects,
        posts,
        tags
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        source,
        id,
        url,
        icon
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        object,
        id,
        hash,
        size,
        type,
        subtype,
        date_added,
        preview_id,
        src,
        posts
    );

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
        tag,
        id,
        name,
        aliases,
        description,
        avatar,
        banner,
        sources,
        post_count,
        date_created
    );
}
