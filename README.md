# Sheets

Command-line tool for work with spread sheets. Implemented in C++. Done as a homework project for the course on Object-Oriented Programming at SU "Kliment Ohridski" FMI.

## Usage

### Prerequisites

- **CMake**: version 3.13 or higher

### Building the project

Run these commands while in the project directory:

```bash
cmake .
make
```

After that a **Cli** executable should be available in the Cli project folder.

### General Architecture

The project is separated in 3 different modules:

1. **Core** - Table related functionality such as the editing cells, calculating formulas.
2. **Serialization** - Serialization and Deserialization of tables.
3. **Cli** - User Interface related functionality.

A UML diagram of the different modules:

1. Core
2. Serialization
3. Cli

## Used libraries

- Catch 2 Testing framework - [Go to Github page](https://github.com/catchorg/catch2)
