# Trie (Prefix tree)
## Intoduction
Two implementations of trie:

1. Basic trie implementated as root node that hold onto its children in std::vector
1. Static trie that is the main goal of project. In essence, it is trie that is packed into one array for faster access of elements and, more importantly, being able to construct it in compile-time.

## Building
### Requirements
Versions on which project was originaly built and tested will be listed in parenthesis
- cmake (cmake 3.24)
- gcc, supporting c++20 concepts and ranges (gcc 12)
  - [google's gtest](https://github.com/google/googletest)
  - [google's benchmark](https://github.com/google/benchmark)
- python 3 (python 3.10)
  - numpy (numpy 1.23)
  - matplotlib (matplotlib 3.6)

### Installation of c++ libraries
##### Ubuntu
```
sudo apt-get install libgtest-dev libbenchmark-dev
```
##### Arch
```
sudo pacman -S gtest benchmark
```

### Setting up python virtual enviroment
```
python -m venv env
source env/bin/activate
pip install numpy matplotlib
```
### Building release version
```
cmake -DCMAKE_BUILD_TYPE=Release -B ./Release
make --directory=Release
```
**Note:** all binaries will be at ```bin/{build type}/```, replace ```{build type}``` with ```Release``` or ```Debug```.
## How to run
Precondition of this section that you already installed all dependencies and built project in Release version
### Tests
Project uses [google's gtest library](https://github.com/google/googletest) for testing.

To run tests use ```./bin/Release/tests```
### Demos
There are 2 demos, that shows how to use trie and static trie respectfully

To run them use ```./bin/Release/demo``` and ```./bin/Release/static_demo```.
### Benchmarks
Project uses [google's Benchmark library](https://github.com/google/benchmark) of benchmarking

To run benchmarks use ```./bin/Release/benchmarks```.

If you want to write benchmark results into json file (this is required by next step) use ```./bin/Release/benchmarks --benchmark_out=benchmark_results.json --benchmark_out_format=json```. You can replace ```benchmark_results.json``` by any filename you want.
### Graph
For drawing of graphs, project uses python's [matplotlib](https://matplotlib.org/).

First of all you need to activate virtual enviroment. If you had followed previous steps use ```source ./env/bin/activate```.

To draw graphs use ```python benchmark/py/graph.py benchmark_results.json``` or replace ```benchmark_results.json``` by filename you specified in previous step.

If you want to look at only one of the graphs use one of this as second arguments:
- creation
- contains
- get
- get_all

e.g. ```python benchmark/py/graph.py benchmark_results.json creation``` to see only creation comparison graph.
