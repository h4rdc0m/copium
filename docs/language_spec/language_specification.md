# Copium Language Specification

## 1. Introduction

Copium is a modern programming language designed for performance, safety, and developer productivity. This document outlines the formal specification of the Copium language.

## 2. Design Goals

- **Performance**: Compile to efficient machine code with predictable performance
- **Safety**: Prevent common programming errors through strong typing and memory safety
- **Interoperability**: Seamless integration with existing codebases
- **Readability**: Clear, consistent syntax that prioritizes maintainability
- **Modularity**: Strong support for component-based design

## 3. Syntax Fundamentals

### 3.1 Lexical Elements

```
// Single-line comment
/* Multi-line
     comment */

// Keywords
fn var let const if else while for return class interface impl alias
```

### 3.2 Basic Types

```
// Primitive types
i32, i64      // Signed integers
u32, u64      // Unsigned integers
f32, f64      // Floating point
bool          // Boolean (true/false)
String        // UTF-8 string
```

### 3.3 Type Aliases

```
// Type alias declaration
alias IntArray = [i32];
alias StringMap = HashMap<String, String>;
alias Callback = fn(i32) -> bool;

// Usage
var numbers: IntArray = [1, 2, 3];
var mapper: StringMap = HashMap::new();
var validator: Callback = fn(x) { return x > 0; };
```

## 4. Variables and Bindings

```
// Variable declaration
var x: i32 = 42;
let y: f64 = 3.14;  // Immutable binding

// Type inference
var name = "Copium";  // String type inferred
```

## 5. Functions

```
fn add(a: i32, b: i32) -> i32 {
      return a + b;
}

// Functions with no return
fn log(message: String) {
      // Implementation
}

// Default parameters
fn greet(name: String = "World") -> String {
      return "Hello, " + name;
}
```

## 6. Control Flow

```
if condition {
      // Code
} else if other_condition {
      // Code
} else {
      // Code
}

while condition {
      // Code
}

for i in 0..10 {
      // Code
}
```

## 7. Object-Oriented Programming

```
class Person {
      var name: String;
      var age: i32;
      
      fn new(name: String, age: i32) -> Self {
            return Self{name: name, age: age};
      }
      
      fn greet(self) -> String {
            return "Hello, my name is " + self.name;
      }
}
```

## 8. Memory Management

Copium uses a deterministic memory management model with ownership semantics:

```
fn example() {
      var data = create_resource();  // Ownership acquired
      process(data);                 // Ownership temporarily transferred
      // data is still available here
} // Resource automatically freed
```

## 9. Error Handling

```
fn divide(a: i32, b: i32) -> Result<i32, String> {
      if b == 0 {
            return Err("Division by zero");
      }
      return Ok(a / b);
}

// Usage
match divide(10, 2) {
      Ok(result) => print("Result: " + result),
      Err(error) => print("Error: " + error),
}
```

## 10. Libraries and Modules

### 10.1 Module Definition

```
// Declare a module
module geometry {
      fn calculate_area(width: f64, height: f64) -> f64 {
            return width * height;
      }
}

// Using a module
let area = geometry.calculate_area(10.0, 5.0);
```

### 10.2 Library Declaration

```
// File: math_lib.cop
library math_lib;

// Public exports are accessible when importing the library
pub fn add(a: i32, b: i32) -> i32 {
     return a + b;
}

// Private functions are only accessible within the library
fn internal_helper() {
     // Implementation
}
```

### 10.3 Library Imports

```
// Import a library
import math_lib;
import collections.{Vector, HashMap};

// Using imported libraries
let sum = math_lib.add(5, 10);
let vec = Vector::new();
```

## 11. Generics

```
fn max<T: Comparable>(a: T, b: T) -> T {
      if a > b {
            return a;
      }
      return b;
}
```

## 12. Concurrency

```
async fn fetch_data(url: String) -> Result<String, Error> {
      // Implementation
}

// Await an async function
let result = await fetch_data("https://example.com");
```

## 13. Interoperability

Copium provides foreign function interfaces for interoperability with existing code:

```
extern "C" fn c_function(arg: i32) -> i32;

fn call_external() {
      let result = c_function(42);
}
```

## 14. Standard Library

The standard library includes modules for:
- Core data structures and algorithms
- Input/output operations
- Networking and web
- Concurrency primitives
- System integration

## 15. Future Considerations

- Metaprogramming capabilities
- Additional safety features
- Extended platform support
- Performance optimizations