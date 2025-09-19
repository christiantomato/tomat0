# tomat0 Compiler
Compiler for my own language, tomat0. tomat0 focuses on increasing readibility and removing unecessary syntax. Currently the compiler can output the abstract syntax tree representation of the code, working on generating ARM64 assembly instructions.

### Road Map
- [x] Lexical Analysis
  - [x] tokenizing integers
  - [x] tokenizing identifiers
  - [x] tokenizing strings
  - [x] tokenizing symbols
      
- [x] Syntactic Analysis
  - [x] AST representation
  - [x] parsing variable declarations
  - [x] parsing print statements
  - [x] parsing expressions, terms, and factors
  - [ ] parsing functions

### TODO
- [ ] Create Symbol Table to store variables
- [ ] Translating to ARM64 Assembly
  - [x] print integers

