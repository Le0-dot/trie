#include "prefix_tree.hpp"

int main()
{
    constexpr prefix_tree<int> f{{"abc", 123}, {"bca", 431}, {"cba", 234}};
    return 0;
}
