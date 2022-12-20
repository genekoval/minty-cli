#pragma once

#include <minty/minty>
#include <yaml-cpp/yaml.h>

namespace YAML {
    auto operator<<(
        Emitter& out,
        const minty::comment& comment
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const minty::comment_data& comment
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const minty::data_size& data_size
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const minty::object& object
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const minty::object_preview& object
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const minty::post& post
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const minty::post_preview& post
    ) -> Emitter&;

    template <typename T>
    auto operator<<(
        Emitter& out,
        const minty::search_result<T> result
    ) -> Emitter& {
        out << BeginMap;

        out << Key << "total" << Value << result.total;

        out << Key << "hits" << Value << BeginSeq;
        for (const auto& hit : result.hits) out << hit;
        out << EndSeq;

        out << EndMap;
        return out;
    }

    auto operator<<(
        Emitter& out,
        const minty::tag& tag
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const minty::tag_preview& tag
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const minty::time_point& time_point
    ) -> Emitter&;

    auto operator<<(
        Emitter& out,
        const UUID::uuid& uuid
    ) -> Emitter&;
}
