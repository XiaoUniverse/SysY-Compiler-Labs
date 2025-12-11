# SysY-Compiler-Labs

This project implements a SysY compiler for the Compiler Principles course labs. The repository contains three modules:

- Lexer — Performs lexical analysis on SysY source code and outputs a sequence of tokens.

- Parser — Builds an abstract syntax tree (AST) based on the lexical analysis results.

- Light IR Generator — Translates a SysY program into a three-address, simplified LLVM IR (Light IR).

After generating the Light IR, LLVM tools (lli) are used to test the result and verify the correctness of the intermediate code.


🔧 Tool (need to install)
- gcc
- lli
- Bison
- Flex


If you have any questions or suggestions, feel free to open an issue or ask me anytime.

