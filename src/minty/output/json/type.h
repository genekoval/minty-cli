#pragma once

#include <chrono>
#include <date/date.h>
#include <date/tz.h>
#include <nlohmann/json.hpp>
#include <uuid++/uuid++>

namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::optional<T>> {
        static auto from_json(const json& j, std::optional<T>& opt) -> void {
            if (j.is_null()) opt.reset();
            else opt = j.get<T>();
        }

        static auto to_json(json& j, const std::optional<T>& opt) -> void {
            if (!opt) j = nullptr;
            else j = opt.value();
        }
    };

    template <typename Clock, typename Duration>
    class adl_serializer<std::chrono::time_point<Clock, Duration>> {
        using time_point = std::chrono::time_point<Clock, Duration>;

        static constexpr auto format = "%F %T%z";
    public:
        static auto from_json(const nlohmann::json& j, time_point& t) -> void {
            const auto string = j.get<std::string>();

            auto stream = std::istringstream(string);
            date::from_stream(stream, format, t);
        }

        static auto to_json(nlohmann::json& j, const time_point& t) -> void {
            const auto* zone = date::current_zone();
            const auto zoned = date::make_zoned(zone, t);

            auto stream = std::ostringstream();
            stream << date::format(format, zoned);

            j = stream.str();
        }
    };
}

namespace UUID {
    auto from_json(const nlohmann::json& j, uuid& u) -> void;

    auto to_json(nlohmann::json& j, const uuid& u) -> void;
}
