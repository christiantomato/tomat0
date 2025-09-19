# tomat0 Compiler
Compiler for my own language, tomat0. tomat0 focuses on increasing readibility and removing unecessary syntax. At its current state, it can compile print statements for integers and arithmetic expressions (see example in main.tmt). 

### Road Map
Lexical Analysis
  - [x] tokenize punctuation characaters
  - [x] tokenize integers
  - [x] tokenize identifiers
  - [x] tokenize strings
      
Syntactic Analysis
  - [x] abstract syntax tree representation
  - [x] store symbols in symbol table
  - [x] parse variable declarations
  - [x] parse print statements
  - [x] parse expressions, terms, and factors
  - [ ] parse functions

ARM64 Assembly Generation
  - [x] compute values of binary operations
  - [x] print integer values to terminal
  - [ ] print string literals to terminal
  - [x] use and load variable values
  - [ ] loops
  - [ ] functions
  - [ ] if statements

### TODO
- use symbol table to store variables in memory during arm assembly code generation phase

