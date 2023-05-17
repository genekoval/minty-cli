#pragma once

#include <detail/settings.hpp>

#include <minty/minty>

namespace minty::cli {
    auto object_store(const settings& config) -> fstore::client;

    class bucket {
        UUID::uuid bucket_id;
        fstore::client::pool::item object_store;

        bucket(
            fstore::client::pool::item&& object_store,
            const UUID::uuid& bucket_id
        );
    public:
        static auto connect(
            repo& repo,
            fstore::client& object_store
        ) -> ext::task<bucket>;

        auto get(const UUID::uuid& object_id, std::ostream& out) -> ext::task<>;
    };
}
