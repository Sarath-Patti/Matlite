# Matlite

Matlite is a MATLAB-inspired interpreter written in modern C++20.

This is Version 0.2. The current release provides the project skeleton, a simple REPL loop, and a standalone lexer. Parser, AST, evaluator, matrix support, runtime behavior, and built-in functions are planned subsystems, but they are not implemented yet.

## Project Structure

```text
src/
    lexer/      Token and lexer implementation.
    parser/     Future parser implementation.
    ast/        Future abstract syntax tree nodes.
    runtime/    Future runtime environment and values.
    evaluator/  Future AST evaluation logic.
    matrix/     Future matrix data structures and operations.
    builtin/    Future built-in functions.
    main.cpp    Version 0.1 REPL entry point.

include/       Public headers for reusable Matlite components.
tests/         Automated tests.
examples/      Example Matlite programs and usage notes.
docs/          Design notes and project documentation.
```

## Build Requirements

- A C++20-capable compiler
- CMake 3.20 or newer

## Build

From the repository root:

```sh
cmake -S . -B build
cmake --build build
```

## Run

```sh
./build/matlite
```

The REPL displays:

```text
>>
```

Type a line and Matlite echoes it back:

```text
>> hello
You entered: hello
```

Type `exit` or `quit` to leave the REPL.

## Test

```sh
ctest --test-dir build
```

## Version 0.2 Scope

Version 0.2 includes:

- CMake-based C++20 project setup
- Production-oriented compiler warnings
- Modular directory layout for future interpreter components
- A minimal REPL that reads one line at a time
- Token and lexer classes
- Lexer unit tests

Version 0.2 does not include:

- Parser
- AST
- Evaluator
- Matrix operations
- Built-in functions
