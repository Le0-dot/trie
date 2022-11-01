#pragma once

#include <string_view>
#include <array>
#include <utility>

namespace static_trie_types {

    using key_t = std::string_view;

    template<typename T>
    using pair_t = std::pair<key_t, T>;

    template<typename Node, size_t size>
    using storage_t = std::array<Node, size>;

    template<typename T, size_t size>
    using value_storage_t = std::array<T, size>;

}
