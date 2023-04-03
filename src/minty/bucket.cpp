#include <detail/bucket.hpp>

namespace minty::cli {
    auto object_store(const settings& config) -> fstore::client {
        return fstore::client(config.server.objects);
    }

    bucket::bucket(
        ext::pool_item<fstore::object_store>&& object_store,
        const UUID::uuid& bucket_id
    ) :
        bucket_id(bucket_id),
        object_store(
            std::forward<ext::pool_item<fstore::object_store>>(object_store)
        )
    {}

    auto bucket::connect(
        repo& repo,
        fstore::client& object_store
    ) -> ext::task<bucket> {
        const auto server = co_await repo.get_server_info();
        auto connection = co_await object_store.connect();

        co_return bucket(std::move(connection), server.object_source.bucket_id);
    }

    auto bucket::get(
        const UUID::uuid& object_id,
        std::ostream& out
    ) -> ext::task<> {
        return object_store->get_object(bucket_id, object_id, out);
    }
}
