# AlgoViz

An interactive sorting algorithm visualizer written in **C++17** with **raylib**. It shows each comparison, swap, and write as it happens, so you can see how different algorithms work and compare how efficient they are.

<!-- Add a demo GIF here once recorded: ![AlgoViz demo](docs/demo.gif) -->

## Features

- **Four sorting algorithms:** Bubble Sort, Insertion Sort, Merge Sort, Quick Sort
- **Step-by-step playback:** play, pause, step forward and backward, and adjust speed
- **Color-coded operations** so you can see what the algorithm is doing at every step
- **Live counters** for comparisons and swaps/writes, so you can compare O(n²) and O(n log n) directly
- **Same-array comparison:** switch algorithms without reshuffling to compare them on identical input

## Color Legend

| Color  | Meaning                                  |
|--------|------------------------------------------|
| Blue   | Unsorted element                         |
| Yellow | Elements being compared (Quick Sort: pivot) |
| Red    | Elements being swapped or written        |
| Green  | Element in its sorted position           |

## Controls

| Key             | Action                   |
|-----------------|--------------------------|
| `Space`         | Play / pause             |
| `←` / `→`       | Step backward / forward  |
| `↑` / `↓`       | Increase / decrease speed |
| `R`             | Shuffle a new array      |
| `Tab`           | Switch to next algorithm |

## How It Works

Each algorithm is a plain function that takes an array and returns a **recording** of every operation it performed:

```cpp
struct Step {
    std::vector<int> array;      // array state at this moment
    int cmpA, cmpB;              // indices being compared
    int swapA, swapB;            // indices being swapped/written
    std::vector<bool> sorted;    // which positions are finalized
};

using AlgorithmFn = std::vector<Step> (*)(std::vector<int>);
```

Because the algorithm runs to completion first and produces a list of `Step`s, the rest of the program is simpler:

- The **algorithms** know nothing about rendering, timing, or input. Each is ordinary sorting code that records its steps.
- The **Player** moves through the recorded steps at a controllable speed. Stepping backward is just moving an index.
- The **Renderer** draws a single `Step` and has no knowledge of which algorithm produced it.
- Adding a new algorithm means writing one file and adding one line to `Registry.cpp`.

## Project Structure

```
AlgoViz/
├── CMakeLists.txt            # build config; fetches raylib automatically
├── src/
│   ├── main.cpp              # window, main loop, input handling
│   ├── Step.h                # the Step data structure
│   ├── Player.h / .cpp       # playback: play, pause, step, speed
│   ├── Renderer.h / .cpp     # draws the bars and highlights
│   ├── UI.h / .cpp           # title, stats, controls text
│   └── algorithms/
│       ├── Algorithm.h       # AlgorithmInfo + function declarations
│       ├── Registry.cpp      # list of available algorithms
│       ├── BubbleSort.cpp
│       ├── InsertionSort.cpp
│       ├── MergeSort.cpp
│       └── QuickSort.cpp
└── web/
    └── shell.html            # page template for the web build (planned)
```

## Building

### Requirements

- CMake 3.20+
- A C++17 compiler (Visual Studio 2022+ Build Tools, GCC, or Clang)
- Git (CMake uses it to download raylib)

raylib is downloaded and built automatically the first time you build, so you don't need to install it separately.

### Windows (Visual Studio)

```cmd
cmake -S . -B build
cmake --build build
build\Debug\algoviz.exe
```

### macOS / Linux

```bash
cmake -S . -B build
cmake --build build
./build/algoviz
```

## Algorithms

| Algorithm      | Best       | Average    | Worst      | Space    | Stable |
|----------------|------------|------------|------------|----------|--------|
| Bubble Sort    | O(n)       | O(n²)      | O(n²)      | O(1)     | Yes    |
| Insertion Sort | O(n)       | O(n²)      | O(n²)      | O(1)     | Yes    |
| Merge Sort     | O(n log n) | O(n log n) | O(n log n) | O(n)     | Yes    |
| Quick Sort     | O(n log n) | O(n log n) | O(n²)      | O(log n) | No     |

## Roadmap

- [ ] Clickable on-screen controls (buttons, speed slider, algorithm picker)
- [ ] Web build with Emscripten, hosted on GitHub Pages
- [ ] Additional sorts: Selection, Heap, Shell
- [ ] Pathfinding visualizer (BFS, DFS, Dijkstra, A*) on a grid

## Author

**Alyssa Baker**, software developer
GitHub: [@A-Bak-tech](https://github.com/A-Bak-tech)