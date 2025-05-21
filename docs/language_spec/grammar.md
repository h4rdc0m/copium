# Copium Language Grammar Reference

This document defines the formal grammar for the Copium programming language.

## Notation

This grammar uses a modified Extended Backus-Naur Form (EBNF):

- `|` denotes alternatives
- `[ ... ]` denotes optional elements
- `{ ... }` denotes elements repeated zero or more times
- Terminal symbols are in `"quotes"` or shown in `code font`
- Non-terminal symbols are in *italics*

## Lexical Grammar

### Whitespace and Comments

```
WhiteSpace ::= " " | "\t" | "\r" | "\n"
LineComment ::= "//" {any character except newline}
BlockComment ::= "/*" {any character} "*/"
```

### Keywords

```
Keyword ::= "let" | "const" | "if" | "else" | "while" | "for" | "fn" | "alias"
          | "return" | "true" | "false" | "null" | "class" | "import" | "export"
```

### Identifiers

```
Identifier ::= Letter {Letter | Digit | "_"}
Letter ::= "a"..."z" | "A"..."Z"
Digit ::= "0"..."9"
```

### Literals

```
Literal ::= NumberLiteral | StringLiteral | BooleanLiteral | NullLiteral
NumberLiteral ::= IntegerLiteral | FloatLiteral
IntegerLiteral ::= Digit {Digit}
FloatLiteral ::= IntegerLiteral "." IntegerLiteral
StringLiteral ::= "\"" {any character except "\"" unless escaped} "\""
BooleanLiteral ::= "true" | "false"
NullLiteral ::= "null"
```

## Syntax Grammar

### Program Structure

```
Program ::= {Statement}
```

### Statements

```
Statement ::= ExpressionStatement
            | VariableDeclaration
            | BlockStatement
            | IfStatement
            | WhileStatement
            | ForStatement
            | FunctionDeclaration
            | ReturnStatement
            | ClassDeclaration
            | ImportStatement
            | ExportStatement
