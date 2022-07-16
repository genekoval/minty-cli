#pragma once

#include "../date.h"
#include "indent.h"

namespace minty::cli::output {
    template <typename T>
    struct row {
        const std::string_view label;
        const T& value;

        auto label_size() const -> std::size_t {
            return label.size();
        }
    };

    template <typename T>
    struct row<std::optional<T>> {
        const std::string_view label;
        const std::optional<T>& value;

        auto label_size() const -> std::size_t {
            if (value) return label.size();
            return 0;
        }
    };

    template <typename... Rows>
    class metadata {
    public:
        int indent = 0;
    private:
        using row_container = std::tuple<Rows...>;

        template <std::size_t... I>
        static auto compute_alignment(
            const row_container& rows,
            std::index_sequence<I...>
        ) -> int {
            auto result = static_cast<std::size_t>(0);

            ((result = std::max(result, std::get<I>(rows).label_size())), ...);

            return result;
        }

        const row_container rows;
        const int alignment;

        auto print_label(std::FILE* f, std::string_view label) -> void {
            print_indent(f, indent);

            fmt::print(
                f,
                style::label,
                "{:{}}",
                label,
                alignment
            );

            fmt::print(f, "{}", style::interpunct);
        }

        template <typename T>
        auto print_value(std::FILE* f, const T& value) -> void {
            fmt::print(f, style::secondary, "{}\n", value);
        }

        template <typename T>
        auto print_row(
            std::FILE* f,
            std::string_view label,
            const T& value
        ) -> void {
            print_label(f, label);
            print_value(f, value);
        }

        template <typename T>
        auto print_row(
            std::FILE* f,
            std::string_view label,
            const std::vector<T>& value
        ) -> void {
            if (value.empty()) return;

            print_row(f, label, value.front());

            for (auto i = 1ul; i < value.size(); ++i) {
                print_indent(f, indent + alignment + 3);
                print_value(f, value[i]);
            }
        }

        template <typename T>
        auto print_row(
            std::FILE* f,
            std::string_view label,
            const std::optional<T>& value
        ) -> void {
            if (value) print_row(f, label, *value);
        }

        template <typename Clock, typename Duration>
        auto print_row(
            std::FILE* f,
            std::string_view label,
            const std::chrono::time_point<Clock, Duration>& value
        ) -> void {
            const auto duration = format_duration(value);
            const auto formatted = format_date(value);
            const auto date = std::vector<std::string_view> {
                duration,
                formatted
            };

            print_row(f, label, date);
        }

        template <typename Row>
        auto print_row(std::FILE* f, const Row& row) -> void {
            print_row(f, row.label, row.value);
        }

        template <std::size_t... I>
        auto print(std::FILE* f, std::index_sequence<I...>) -> void {
            (print_row(f, std::get<I>(rows)), ...);
        }
    public:
        metadata(Rows&&... rows) :
            rows(std::forward<Rows>(rows)...),
            alignment(compute_alignment(
                this->rows,
                std::index_sequence_for<Rows...>{}
            ))
        {}

        auto print(std::FILE* f) -> void {
            print(f, std::index_sequence_for<Rows...>{});
        }
    };
}
