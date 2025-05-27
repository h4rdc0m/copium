# Copium Language Specification

## Introduction
Copium is a modern programming language designed to balance performance with developer ergonomics. This specification document defines the syntax, semantics, and standard library of the Copium language.

The language aims to provide:
- A clean, expressive syntax
- Strong static typing with inference
- Memory safety without garbage collection
- First-class support for concurrent programming
- Interoperability with existing systems

This document serves as the authoritative reference for compiler implementers and developers working with the Copium language.

## Comments
```copium
# This is a line comment

## This is a documentation comment
## @param value The value param for the method
## @returns i64
## @example The example usage
```

## Types
### Primitive Types
Copium provides the following primitive types:

| Type | Description | Size |
|------|-------------|------|
| `i8` | 8-bit signed integer | 1 byte |
| `i16` | 16-bit signed integer | 2 bytes |
| `i32` | 32-bit signed integer | 4 bytes |
| `i64` | 64-bit signed integer | 8 bytes |
| `u8` | 8-bit unsigned integer | 1 byte |
| `u16` | 16-bit unsigned integer | 2 bytes |
| `u32` | 32-bit unsigned integer | 4 bytes |
| `u64` | 64-bit unsigned integer | 8 bytes |
| `f32` | 32-bit floating point | 4 bytes |
| `f64` | 64-bit floating point | 8 bytes |
| `bool` | Boolean value (true/false) | 1 byte |
| `char` | Unicode character | 4 bytes |

### Composite Types

#### Arrays
Fixed-size collections of elements of the same type:
```copium
i32[5] // An array of 5 32-bit integers
```

#### Slices
Dynamically-sized views into arrays:
```copium
i32[] // A slice of 32-bit integers
```

#### Strings
Copium strings are UTF-8 encoded and come in two varieties:
- String literals: Immutable string values
- String slices: Views into string data

```copium
"Hello, world!" // A string literal
```

### User-Defined Types

#### Data classes
Custom data structures with named fields:

```copium
data Point {
    x: i32,
    y: i32,
}
```

#### Enums
Tagged unions that can hold different types of values:

```copium
enum Result<T, E> {
    Ok(T),
    Err(E),
}
```

#### Tuples
Fixed-size collections of values that can have different types:

```copium
(i32, f64, bool) // A tuple with an integer, a float, and a boolean
```

#### Aliases
```copium
use MyInt = i64
```

### Reference Types

#### References
Non-owning pointers to values:

```copium
*i32 // A reference to an i32, every reference is mutable by default
```

#### Optional Types
Types that may or may not contain a value:

```copium
?i32 // An optional i32 that might be null
```

## Modules

```copium
module main; # This declares that the file belongs to the `main` module

import math; # This imports the math module, or errors if not existing
```

## Variables

Variables are declared with the `var` keyword. Type inference is supported, but explicit types can be provided.

```copium
var x = 42           # Type inferred as i32
var y: f64 = 3.14    # Explicit type
var point = Point{ x = 1, y = 2 }
```

Variables are mutable by default. To declare an immutable variable, use `let`:

```copium
let pi = 3.14159     # Immutable variable
```

## Functions

Functions are declared with the `fun` keyword. Parameters and return types are required unless type inference is possible.

```copium
fun add(a: i32, b: i32) -> i32 {
    a + b
}

fun printHello() {
    print("Hello, world!")
}
```

Functions can return multiple values using tuples:

```copium
fun minmax(a: i32, b: i32) -> (i32, i32) {
    if a < b {
        (a, b)
    } else {
        (b, a)
    }
}
```

## Data class methods

Methods can be defined for data classes. Methods that mutate the instance should take a reference (pointer) to `self`:

```copium
data Counter {
    value: i32,
}

fun Counter.inc(self: *Counter) {
    self.value += 1
}

fun Counter.get(self: &Counter) -> i32 {
    self.value
}
```

Methods can be public using the `pub` keyword:

```copium
pub fun Counter.reset(self: *Counter) {
    self.value = 0
}
 
## Control Flow

Copium supports standard control flow constructs:

```copium
if x > 0 {
    print("Positive")
} else if x < 0 {
    print("Negative")
} else {
    print("Zero")
}

for i: i32 = 0; i < 10; i += 1 {
    print(i)
}

for *item in items {
    item.doSomething()
}

while condition {
    doWork()
}

match result {
    Ok(value) => { print("Success: ", value) }
    Err(e)    => { print("Error: ", e) }
}
```

## Example

```copium
module main;

data DataObject {
    fValue: f64,
    iValue: i64,
    uValue: u64,
    bValue: bool,
}

fun DataObject.addToFValue(self: *DataObject, valueToAdd: f64) {
    self.fValue += valueToAdd
}

pub fun DataObject.incFValue(self: *DataObject) {
    self.fValue += 1.0
}

enum Result<T, E> {
    Ok(T),
    Err(E),
}

fun main() -> Result<_, i64> {
    var do = DataObject {
        fValue = 0.0,
        uValue = 0,
        iValue = 0,
        bValue = false,
    }

    var dos: DataObject[]
    dos[] = do

    for *d in dos {
        d.incFValue()
    }

    for i: i64 = 0; i < dos.size(); i += 1 {
        *dos[i].uValue += 1
    }

    for d in dos {
        if d.fValue > 0.0 && d.uValue > 0 {
            break
        }
        if d.fValue == 0.0 || d.iValue == 0 {
            break
        }
    }

    Result.Ok(42)
}
```

