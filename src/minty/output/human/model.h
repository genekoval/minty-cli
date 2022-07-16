#pragma once

#include "style.h"

#include <minty/core/model.h>

#include <ext/math.h>
#include <fmt/color.h>

#define MINTY_HUMAN_READABLE(Type) \
    template <> \
    struct human_readable<Type> { \
        static auto print(std::FILE* f, int indent, const Type& type) -> void; \
    };

namespace minty::cli::output {
    template <typename Container>
    auto ol(std::FILE* f, int indent, const Container& list) -> void;

    template <typename T>
    struct human_readable {};

    MINTY_HUMAN_READABLE(core::comment);

    MINTY_HUMAN_READABLE(core::comment_detail);

    MINTY_HUMAN_READABLE(std::vector<core::comment>);

    MINTY_HUMAN_READABLE(core::object_preview);

    MINTY_HUMAN_READABLE(core::object);

    MINTY_HUMAN_READABLE(core::post_preview)

    MINTY_HUMAN_READABLE(core::post)

    MINTY_HUMAN_READABLE(repo::db::tag_preview)

    MINTY_HUMAN_READABLE(core::tag)

    template <typename T>
    struct human_readable<core::search_result<T>> {
        static auto print(
            std::FILE* f,
            int indent,
            const core::search_result<T>& result
        ) -> void {
            if (result.total == 0) {
                fmt::print(f, "No matches found\n");
                return;
            }

            ol(f, indent, result.hits);

            fmt::print(f, style::result, "{}", result.hits.size());
            fmt::print(f, " of ");
            fmt::print(f, style::result, "{}", result.total);
            fmt::print(f, " results\n");
        }
    };

    template <typename T>
    auto print(std::FILE* f, int indent, const T& t) -> void {
        human_readable<T>::print(f, indent, t);
    }
}
