#pragma once

#include <detail/settings.hpp>

#include <minty/minty>

namespace minty::cli {
    auto client() -> minty::client;

    auto client(const settings& config) -> minty::client;

    template <typename F>
    requires requires(const F& f, minty::client& client) {
        { f(client) } -> std::same_as<ext::task<>>;
    }
    auto client(const F& f) -> void {
        auto client = cli::client();

        netcore::run([&]() -> ext::task<> {
            co_await f(client);
        }());
    }

    template <typename F>
    requires requires(const F& f, minty::repo& repo) {
        { f(repo) } -> std::same_as<ext::task<>>;
    }
    auto repo(const F& f) -> void {
        client([&](minty::client& client) -> ext::task<> {
            auto repo = co_await client.connect();
            co_await f(*repo);
        });
    }
}
