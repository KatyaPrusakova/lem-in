# WORK IN PROGRESS

# Lem_in

Lem_in is a School 42 project.

The purpose of this project is to find paths from start room to end room and to move ants by these paths with the least amount of steps.

[`lem-in.en.pdf`](/lem-in.en.pdf) is the task file.

_**You can check [wiki-page](../../wiki/Algorithm) if you want to read description of created algorithm.**_

### Features

* Find all best paths in most cases
* Move ants by found paths in an optimal way
* Extended error messages

### How to run program?

```
./lem-in < MAP_FILE
```

### Input

The software reads standard entry. It is expecting the description of a farm, which must contains :

* Ant's number (a number)
* Rooms (syntax : [Name Y X] - where X and Y are coordonates)
* Links (Syntax : [room(A)-room(B)])
* Start command (to indicate the ant's spawnig room)
* End command (to indicate the ant's goal)

In addition :

* Start and end are commands, they starts with "##".
* All lines starting with "#" are comments.
* All lines starting with "##" are commands.

[`img/input_lem_in.png`]

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
