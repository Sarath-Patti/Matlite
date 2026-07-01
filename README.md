# Matlite

> A MATLAB-inspired interpreter written in modern C++20.

Matlite is an educational interpreter that implements the core components of a programming language from scratch using modern C++20. The project is designed to understand how MATLAB-like languages work internally by building every stage of the interpreter incrementally—from lexical analysis to parsing, abstract syntax trees, expression evaluation, and eventually matrix computation and script execution.

The project emphasizes clean software architecture, modular design, and production-quality C++.

---

# Features

## ✅ Version 0.1
- Interactive REPL (Read-Eval-Print Loop)
- Modern C++20 project setup
- CMake build system
- Modular project structure

---

## ✅ Version 0.2
### Lexer
- Lexical analysis
- Token generation
- Line and column tracking
- Supports:
  - Identifiers
  - Integer literals
  - Floating-point literals
  - Operators (`+`, `-`, `*`, `/`, `^`, `=`)
  - Parentheses
  - Brackets
  - Comma
  - Semicolon
- Unit tested

---

## ✅ Version 0.3
### Recursive Descent Parser
- Recursive descent parser
- Operator precedence parsing
- Right-associative assignment parsing
- Parenthesized expressions
- Abstract Syntax Tree (AST) generation

### AST Nodes
- Expression (base class)
- BinaryExpression
- LiteralExpression
- IdentifierExpression
- AssignmentExpression

- Parser unit tests

---

# Compiler Frontend Architecture

```
                Source Code
                     │
                     ▼
          ┌──────────────────┐
          │      Lexer       │
          └──────────────────┘
                     │
                     ▼
             Sequence of Tokens
                     │
                     ▼
          ┌──────────────────┐
          │      Parser      │
          └──────────────────┘
                     │
                     ▼
        Abstract Syntax Tree (AST)
                     │
                     ▼
             Expression Evaluator
                     │
                     ▼
               Runtime Environment
```

---

# Current Progress

```
REPL                     ✅

Lexer                    ✅

Parser                   ✅

Abstract Syntax Tree     ✅

Expression Evaluator     ⏳

Symbol Table             ⏳

Variables                ⏳

Built-in Functions       ⏳

Matrix Engine            ⏳

Script Execution         ⏳
```

---

# Project Structure

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
├── docs/
├── examples/
│
├── CMakeLists.txt
└── README.md
```

---

# Build

Clone the repository

```bash
git clone https://github.com/Sarath-Patti/Matlite.git
cd Matlite
```

Configure

```bash
mkdir build
cd build
cmake ..
```

Build

```bash
cmake --build .
```

---

# Run

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

# Run Tests

```bash
cd build

ctest --output-on-failure
```

---

# Development Roadmap

## Phase 1 — Frontend

- [x] v0.1 Project Setup + REPL
- [x] v0.2 Lexer
- [x] v0.3 Recursive Descent Parser
- [x] v0.3 Abstract Syntax Tree

## Phase 2 — Interpreter

- [ ] v0.4 Expression Evaluator
- [ ] v0.5 Symbol Table
- [ ] v0.6 Variables
- [ ] v0.7 Built-in Mathematical Functions

## Phase 3 — MATLAB Features

- [ ] Matrix Class
- [ ] Matrix Expressions
- [ ] Matrix Operations
- [ ] Function Calls
- [ ] User-defined Functions
- [ ] Script Execution (.m)

## Phase 4 — Advanced Features

- [ ] Visitor Pattern
- [ ] Pretty Printer
- [ ] Optimizer
- [ ] Error Recovery
- [ ] Diagnostics

---

# Technologies

- C++20
- CMake
- GoogleTest
- Git
- Visual Studio Code
- OpenAI Codex

---

# Learning Objectives

This project explores the implementation of modern programming languages by building:

- Lexical Analysis
- Recursive Descent Parsing
- Abstract Syntax Trees
- Expression Evaluation
- Symbol Tables
- Runtime Environments
- Matrix Computation
- Interpreter Design
- Compiler Frontend Architecture
- Modern C++ Software Engineering

---

# Future Work

Planned features include:

- MATLAB-compatible matrix literals
- Matrix multiplication
- Matrix indexing
- Built-in mathematical functions
- Variable scopes
- User-defined functions
- Script execution
- Error diagnostics
- Interactive workspace
- Pretty printer
- Optimization passes

---

# Author

**Sarath Patti**

M.Tech, Computer Science and Engineering

National Institute of Technology Rourkela

GitHub: https://github.com/Sarath-Patti

---

# License

This project is licensed under the MIT License.

## Author

**Sarath Patti**

M.Tech Computer Science  
National Institute of Technology Rourkela

GitHub: https://github.com/Sarath-Patti
