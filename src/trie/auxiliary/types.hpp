#pragma once

#include <string_view>
#include <array>

namespace trie::static_trie_auxiliary::types {

    using key_t = std::string_view;

    template<std::size_t N>
    using keys_t = std::array<key_t, N>;

    template<typename Node, std::size_t N>
    using storage_t = std::array<Node, N>;

    template<typename T, std::size_t N>
    using values_t = std::array<T, N>;

}
