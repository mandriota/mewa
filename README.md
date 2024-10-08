# (=​｀ω´=) MEWA
A simple Math EWAluator written on C.

## Installation
```sh
git clone https://github.com/mandriota/mewa
cd mewa
make build
sudo ln -n ./bin/mewa /usr/local/bin
```

## Featchers
- [x] Basic arithmetic operators
- [x] Basic logical operators 
- [x] Operators priority and associativity
- [x] Type inference
- [ ] Functions
- [ ] Function specialization
- [ ] Function ranged specialization
- [x] Command-line arguments and redirects handling
- [x] REPL
- [ ] REPL: multiline input
- [x] REPL: history
- [x] REPL: escape handling
- [ ] Calculation of maximal relative error

## Naming Conventions
### Constants, Enums, Defines
All caps, snake case.

### Structs
Title, camel case.

### Functions, local variables
All script, snake case.

### Methods
Same as functions. First word is an abbreviation of struct name.

### Names abbreviations list
| Name          | Abbreviation |
|:--------------|:-------------|
| `Primitive`   | `PM`/`PRIM`  |
| `Reader`      | `RD`         |
| `Token`       | `TK`         |
| `TokenType`   | `TT`         |
| `Lexer`       | `LX`         |
| `Node`        | `ND`         |
| `NodeType`    | `NT`         |
| `Parser`      | `PR`         |
| `Priority`    | `PT`         |
| `Interpreter` | `IR`         |

## Acknowledgements
- Thanks to [Shiney](https://github.com/ItzShiney) for helping with some math formulas.
- Thanks to [Giovanni Crisalfi](https://github.com/gicrisf) for [the kaomoji collection](https://github.com/gicrisf/kaomel) used in this file.
