# Project Structure

Matlite is organized around the major subsystems expected in an interpreter.
Version 0.2 implements the lexer and keeps later interpreter phases as placeholders.

- `src/lexer`: token definitions and source tokenization.
- `src/parser`: future syntax parsing code.
- `src/ast`: future abstract syntax tree types.
- `src/runtime`: future runtime values, scopes, and execution state.
- `src/evaluator`: future expression and statement evaluation.
- `src/matrix`: future matrix storage and operations.
- `src/builtin`: future built-in functions.
- `include`: future public headers shared across subsystems.
- `tests`: future automated tests.
- `examples`: future Matlite scripts and usage examples.
- `docs`: design and development documentation.
