# Matlite

> A MATLAB-inspired interpreter written in modern C++20.

Matlite is an educational and extensible interpreter that aims to implement a subset of MATLAB's language features from scratch. The project is designed to explore how interpreters and programming languages work internally, including lexical analysis, parsing, abstract syntax trees, expression evaluation, matrix operations, and script execution.

The long-term goal is to build a clean, modular interpreter that demonstrates compiler and interpreter design principles using modern C++.

---

## Features

### Version 0.1
- Interactive REPL (Read-Eval-Print Loop)
- Modern C++20 project structure
- CMake build system
- Modular project layout

### Version 0.2
- Lexical Analyzer (Lexer)
- Token generation
- Line and column tracking
- Support for:
  - Identifiers
  - Integer literals
  - Floating-point literals
  - Arithmetic operators
    - `+`
    - `-`
    - `*`
    - `/`
    - `^`
    - `=`
  - Parentheses
  - Brackets
  - Comma
  - Semicolon
- Unit tests for lexer

### Version 0.3
- Recursive descent parser
- Abstract Syntax Tree (AST)
- Expression parsing with operator precedence
- Support for:
  - Assignment expressions
  - Binary expressions
  - Literal expressions
  - Identifier expressions
  - Parenthesized expressions
- Unit tests for parser

---

## Project Architecture

```
               Source Code
                     │
                     ▼
              Lexical Analysis
                  (Lexer)
                     │
                     ▼
              Sequence of Tokens
                     │
                     ▼
                  Parser
                     │
                     ▼
          Abstract Syntax Tree
                     │
                     ▼
             Expression Evaluator
                     │
                     ▼
                 Runtime System
```

Current Progress

```
REPL
  │
  ▼
Lexer ✅

Parser ✅

AST ✅

Interpreter ⏳
```

---

## Project Structure

```
Matlite/
│
├── src/
│   ├── lexer/
│   ├── parser/
│   ├── ast/
│   ├── evaluator/
│   ├── runtime/
│   ├── matrix/
│   ├── builtin/
│   └── main.cpp
│
├── include/
├── tests/
├── examples/
├── docs/
├── CMakeLists.txt
└── README.md
```

---

## Build Instructions

### Clone

```bash
git clone https://github.com/Sarath-Patti/Matlite.git
cd Matlite
```

### Configure

```bash
mkdir build
cd build
cmake ..
```

### Build

```bash
cmake --build .
```

---

## Run

```bash
./matlite
```

Example

```
>> hello
You entered: hello

>> exit
```

---

## Run Tests

```bash
cd build
ctest --output-on-failure
```

---

## Development Roadmap

- [x] v0.1 Project setup and REPL
- [x] v0.2 Lexer
- [x] v0.3 Recursive Descent Parser and AST
- [ ] v0.4 Expression Evaluation
- [ ] v0.5 Variables and Symbol Table
- [ ] v0.6 Matrix Support
- [ ] v0.7 Built-in Mathematical Functions
- [ ] v0.8 Script Execution (.m files)
- [ ] v0.9 User-defined Functions
- [ ] v1.0 Plotting Support
- [ ] v1.1 Error Recovery and Diagnostics

---

## Technologies

- C++20
- CMake
- GoogleTest
- Git
- VS Code
- OpenAI Codex (development assistant)

---

## Learning Objectives

This project is being built to gain hands-on experience with:

- Compiler construction
- Interpreter design
- Lexical analysis
- Recursive descent parsing
- Abstract Syntax Trees
- Symbol tables
- Runtime environments
- Matrix computation
- Modern C++ software architecture
- Unit testing

---

## Future Work

- MATLAB-style matrix operations
- Control flow (`if`, `for`, `while`)
- User-defined functions
- Built-in numerical library
- Script execution
- Error diagnostics
- Interactive workspace
- Basic plotting support

---

## License

This project is released under the MIT License.

---

## Author

**Sarath Patti**

M.Tech Computer Science  
National Institute of Technology Rourkela

GitHub: https://github.com/Sarath-Patti
