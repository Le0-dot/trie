''' Predicates for get_data function '''

def static_trie_constexpr(benchmark: dict) -> bool:
    return 'StaticTrieConstexpr' in benchmark['name'] 

def static_trie(benchmark: dict) -> bool:
    return 'StaticTrie' in benchmark['name'] and not 'StaticTrieConstexpr' in benchmark['name']

def trie(benchmark: dict) -> bool:
    return 'Trie' in benchmark['name'] and not 'StaticTrie' in benchmark['name']

def creation(benchmark: dict) -> bool:
    return 'Creation' in benchmark['name']

def contains(benchmark: dict) -> bool:
    return 'Contains' in benchmark['name']

def get(benchmark: dict) -> bool:
    return 'Get' in benchmark['name'] and not 'GetAll' in benchmark['name']

def get_all(benchmark: dict) -> bool:
    return 'GetAll' in benchmark['name']

def static_trie_constexpr_creation(benchmark: dict) -> bool:
    return static_trie_constexpr(benchmark) and creation(benchmark)

def static_trie_creation(benchmark: dict) -> bool:
    return static_trie(benchmark) and creation(benchmark)

def trie_creation(benchmark: dict) -> bool:
    return trie(benchmark) and creation(benchmark)

def static_trie_constexpr_contains(benchmark: dict) -> bool:
    return static_trie_constexpr(benchmark) and contains(benchmark)

def static_trie_contains(benchmark: dict) -> bool:
    return static_trie(benchmark) and contains(benchmark)

def trie_contains(benchmark: dict) -> bool:
    return trie(benchmark) and contains(benchmark)

def static_trie_constexpr_get(benchmark: dict) -> bool:
    return static_trie_constexpr(benchmark) and get(benchmark)

def static_trie_get(benchmark: dict) -> bool:
    return static_trie(benchmark) and get(benchmark)

def trie_get(benchmark: dict) -> bool:
    return trie(benchmark) and get(benchmark)

def static_trie_constexpr_get_all(benchmark: dict) -> bool:
    return static_trie_constexpr(benchmark) and get_all(benchmark)

def static_trie_get_all(benchmark: dict) -> bool:
    return static_trie(benchmark) and get_all(benchmark)

def trie_get_all(benchmark: dict) -> bool:
    return trie(benchmark) and get_all(benchmark)
