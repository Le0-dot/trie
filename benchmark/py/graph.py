import sys
import os.path
import matplotlib.pyplot as plt

from data import *
from predicates import *
        
def draw(title, *data) -> None:
    fig, ax = plt.subplots()
    ax.set_title(title)
    for x, y, label in data:
        ax.plot(x, y, label=label, marker='o')
    ax.set_xlabel('Data size')
    ax.set_ylabel('nanoseconds')
    ax.legend()
    ax.grid(True)
    plt.show()

def draw_creation_graph(json_data: dict) -> None:
    data1 = get_data(json_data, 'Static Trie Constexpr', static_trie_constexpr_creation)
    data2 = get_data(json_data, 'Static Trie', static_trie_creation)
    data3 = get_data(json_data, 'Trie', trie_creation)
    draw('Trie Creation', data1, data2, data3)

def draw_cotains_graph(json_data: dict) -> None:
    data1 = get_data(json_data, 'Static Trie Constexpr', static_trie_constexpr_contains)
    data2 = get_data(json_data, 'Static Trie', static_trie_contains)
    data3 = get_data(json_data, 'Trie', trie_contains)
    draw('Trie Contains', data1, data2, data3)

def draw_get_graph(json_data: dict) -> None:
    data1 = get_data(json_data, 'Static Trie Constexpr', static_trie_constexpr_get)
    data2 = get_data(json_data, 'Static Trie', static_trie_get)
    data3 = get_data(json_data, 'Trie', trie_get)
    draw('Trie Get', data1, data2, data3)

def draw_get_all_graph(json_data: dict) -> None:
    data1 = get_data(json_data, 'Static Trie Constexpr', static_trie_constexpr_get_all)
    data2 = get_data(json_data, 'Static Trie', static_trie_get_all)
    data3 = get_data(json_data, 'Trie', trie_get_all)
    draw('Trie Get All', data1, data2, data3)

def main(args: list[str]) -> None:
    if len(args) == 0:
        print('Please, pass file to read from as argument', file=sys.stderr)
        return
    if not os.path.isfile(args[0]):
        print(f'{args[0]} does not exists', file=sys.stderr)
        return
    if len(args) == 2 and not args[1] in ('creation', 'contains', 'get', 'get_all'):
        print(f'{args[1]} is not a valid command please use one of: creation, contains, get, get_all',
              file=sys.stderr)
        return

    json_data = read_data(args[0])
    if len(args) == 1:
        draw_creation_graph(json_data)
        draw_cotains_graph(json_data)
        draw_get_graph(json_data)
        draw_get_all_graph(json_data)
    else:
        if args[1] == 'creation':
            draw_creation_graph(json_data)
        elif args[1] == 'contains':
            draw_cotains_graph(json_data)
        elif args[1] == 'get':
            draw_get_graph(json_data)
        elif args[1] == 'get_all':
            draw_get_all_graph(json_data)



if __name__ == '__main__':
    main(sys.argv[1:])
