''' Module with functions to proccess data '''
import json
from typing import Optional
import numpy as np

def read_data(filename: str) -> dict:
    ''' Read data from json file enconded with utf-8 '''
    data = None
    with open(filename, encoding='UTF-8') as file:
        data = json.load(file)
    return data

def size_map(name: str) -> Optional[int]:
    ''' Map name to size of data '''
    if 'Big' in name:
        return 100
    if 'Medium' in name:
        return 50
    if 'Small' in name:
        return 7
    return None

def get_data(json_data, label, pred=None):
    ''' Get data from json according to predicate '''
    data_size = []
    time = []
    pred = pred if not pred is None else lambda x: x
    for benchmark in json_data['benchmarks']:
        if pred(benchmark):
            data_size.append(size_map(benchmark['name']))
            time.append(benchmark['cpu_time'])
    return np.array(data_size), np.array(time), label
