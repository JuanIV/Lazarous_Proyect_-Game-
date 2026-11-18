# Lazarous Project

**A terminal-based survival and exploration game developed in C.**

Lazarous Project is a text-based game set in an abandoned underground laboratory. Players must explore its different areas, uncover what happened in the facility and find a way to escape.

The game features an ASCII-based terminal interface and a command-driven interaction system, combining exploration, puzzles, inventory management, combat and cooperation between characters.

Originally developed as a first-year university programming project, Lazarous was a collaborative effort focused on learning C and building a game with multiple interacting systems.

## Gameplay

The player wakes up inside an abandoned research facility with little knowledge of their identity or surroundings. As they explore the laboratory, they encounter locked areas, mysterious objects, hostile creatures and fragments of the story behind the facility.

Main gameplay features include:

- **Exploration:** Navigate through different rooms and floors of the laboratory.
- **Command-based interaction:** Move, inspect objects, open doors and interact with the environment through text commands.
- **Puzzles:** Solve environmental challenges involving keys, terminals and interconnected doors.
- **Inventory management:** Collect, use and drop objects, with a maximum inventory capacity of 10 items.
- **Combat:** Fight hostile creatures and other characters, with potentially unpredictable outcomes.
- **Character interaction:** Recruit followers, cooperate with other players or characters, and make decisions that can lead to betrayal.
- **Game management:** Save and load progress, inspect the map and access an in-game help system.

## Technical Overview

The project is written in **C** and organized into separate modules, each responsible for a specific part of the game.

Some of the main components include:

- Game state and game loop management.
- Players and character management.
- Inventory and object handling.
- Spaces, connections and environment representation.
- Command parsing and game actions.
- Game rules and combat mechanics.
- Terminal-based graphical interface.

The project also includes a collection of component tests and Doxygen documentation.

## Technologies

- **Language:** C (ANSI C)
- **Compiler:** GCC
- **Build system:** Make
- **Interface:** ASCII-based terminal graphics
- **Documentation:** Doxygen

## Building and Running

The project uses a Makefile to compile the game.

### Requirements

- GCC
- GNU Make
- A compatible terminal environment
- The `libscreen` library included in the repository

### Compile

```bash
make
```

### Run

```bash
make run
```

### Build and run tests

```bash
make tests
make run_tests
```

### Clean generated files

```bash
make clean
```

## Project Documentation

The repository includes a user guide (`GUIA_USUARIO.pdf`) describing the game's story, commands, objectives and mechanics, as well as Doxygen documentation for the codebase.

## Contributors

Developed collaboratively by:

- Tiago Oselka Conrado
- Juan Ibáñez Villanueva
- Lucas Manuel Blanco Rodríguez
- Alina Datsko Yaskerska

**Lazarous Project — First-year C programming project.**
