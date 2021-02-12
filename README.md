# lem-in
Elementary max flow algorithmic project.

# Lem_in

Lem_in is a School 42 project.

The purpose of this project is to find paths from start room to end room and to move ants by these paths with the least amount of steps.

[`lem-in.en.pdf`](/lem-in.en.pdf) is the task file.

_**You can check [wiki-page](../../wiki/Algorithm) if you want to read description of created algorithm.**_

### Features

* Find all best paths in most cases
* Move ants by found paths in an optimal way
* Extended error messages
* Verbose mode

### How to run program?

```
./lem-in < MAP_FILE
```
### Visualizer

It was written with **SDL2** library.

**Prerequisites**

* `brew install SDL2`
* `brew install SDL2_ttf`
* `brew install SDL2_image`
* `brew install SDL2_gfx`

**How to run visualizer?**

```
./lem-in < MAP_FILE -v
```
