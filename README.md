# Common Algorithms

![Build Status](https://github.com/matteopolak/algorithms/actions/workflows/clang.yml/badge.svg)
[![License:MIT](https://img.shields.io/badge/license-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This repository contains a collection of common algorithms implemented in C++.

## Input format for `astar`

```bash
gcc *.cpp -lstdc++ -o astar.exe
```

Mazes have the following characters:
| Char | Meaning                         |
| ---- | ------------------------------- |
| `#`  | Wall                            |
| `.`  | Path                            |
| `S`  | Start                           |
| `G`  | Goal (you can specify multiple) |

The output will provide the input maze with `*` characters denoting
the shortest path from `S` to any `G`.

For the following maze:

```cmd
#######
S..####
##.##.G
...#..#
.#...##
```

The output will be:

```cmd
#######
***####
##*##**
..*#**#
.#***##
```
