#include "output.h"

#include <date/date.h>
#include <date/tz.h>
#include <fmt/format.h>

namespace YAML {
    auto operator<<(Emitter& out, const minty::comment& comment) -> Emitter& {
        out << BeginMap << Key << "id" << Value << comment.id << Key << "post"
            << Value << comment.post_id;

        if (comment.parent_id) {
            out << Key << "parent" << Value << *comment.parent_id;
        }

        out << Key << "created" << Value << comment.date_created << Key
            << "content" << Value << comment.content << EndMap;

        return out;
    }

    auto operator<<(Emitter& out, const minty::comment_data& comment)
        -> Emitter& {
        out << BeginMap << Key << "id" << Value << comment.id << Key
            << "content" << Value << comment.content << Key << "date posted"
            << Value << comment.date_created << EndMap;

        return out;
    }

    auto operator<<(Emitter& out, const minty::data_size& data_size)
        -> Emitter& {
        out << BeginMap << Key << "formatted" << Value << data_size.formatted
            << Key << "bytes" << Value << data_size.bytes << EndMap;

        return out;
    }

    auto operator<<(Emitter& out, const minty::tag& tag) -> Emitter& {
        out << BeginMap;

        out << Key << "id" << Value << tag.id

            << Key << "name" << Value << tag.name;

        if (!tag.aliases.empty()) {
            out << Key << "aliases" << Value << tag.aliases;
        }

        if (!tag.description.empty()) {
            const auto& description = tag.description;
            out << Key << "description" << Value;

            if (description.find("\n") != std::string::npos) { out << Literal; }

            out << description;
        }

        if (!tag.sources.empty()) {
            out << Key << "links" << Value << BeginSeq;

            for (const auto& source : tag.sources) { out << source.url; }

            out << EndSeq;
        }

        out << Key << "created" << Value << tag.date_created;

        out << EndMap;
        return out;
    }

    auto operator<<(Emitter& out, const minty::tag_preview& tag) -> Emitter& {
        out << BeginMap << Key << "id" << Value << tag.id << Key << "name"
            << Value << tag.name << EndMap;

        return out;
    }

    auto operator<<(Emitter& out, const minty::object& object) -> Emitter& {
        out << BeginMap << Key << "id" << Value << object.id << Key << "hash"
            << Value << object.hash << Key << "size" << Value << object.size
            << Key << "type" << Value << object.type << Key << "subtype"
            << Value << object.subtype << Key << "added" << Value
            << object.date_added;

        if (object.preview_id) {
            out << Key << "preview" << Value << *object.preview_id;
        }

        if (object.src) {
            out << Key << "source" << Value << object.src.value().url;
        }

        if (!object.posts.empty()) {
            out << Key << "posts" << Value << BeginSeq;
            for (const auto& post : object.posts) out << post;
            out << EndSeq;
        }

        out << EndMap;
        return out;
    }

    auto operator<<(Emitter& out, const minty::object_preview& object)
        -> Emitter& {
        out << BeginMap << Key << "id" << Value << object.id << Key << "type"
            << Value << object.type << Key << "subtype" << Value
            << object.subtype << EndMap;

        return out;
    }

    auto operator<<(Emitter& out, const minty::post& post) -> Emitter& {
        out << BeginMap;

        out << Key << "id" << Value << post.id;

        if (!post.title.empty()) out << Key << "title" << Value << post.title;

        if (!post.description.empty())
            out << Key << "description" << Value << post.description;

        out << Key << "created" << Value << post.date_created;

        if (post.date_modified != post.date_created)
            out << Key << "modified" << Value << post.date_modified;

        if (!post.tags.empty()) {
            out << Key << "tags" << Value << BeginSeq;
            for (const auto& tag : post.tags) out << tag;
            out << EndSeq;
        }

        if (!post.objects.empty()) {
            out << "objects" << Value << BeginSeq;
            for (const auto& object : post.objects) out << object;
            out << EndSeq;
        }

        out << EndMap;
        return out;
    }

    auto operator<<(Emitter& out, const minty::post_preview& post) -> Emitter& {
        out << BeginMap;

        out << Key << "id" << Value << post.id;
        if (!post.title.empty()) out << Key << "title" << Value << post.title;
        out << Key << "objects" << Value << post.object_count;
        out << Key << "comments" << Value << post.comment_count;
        out << Key << "created" << Value << post.date_created;

        out << EndMap;

        return out;
    }

    auto operator<<(Emitter& out, const minty::time_point& time_point)
        -> Emitter& {
        const auto* zone = date::current_zone();
        const auto zoned = date::make_zoned(zone, time_point);

        auto stream = std::ostringstream();
        stream << date::format("%F %T%z", zoned);

        return out << stream.str();
    }

    auto operator<<(Emitter& out, const UUID::uuid& uuid) -> Emitter& {
        return out << uuid.string().data();
    }
}
