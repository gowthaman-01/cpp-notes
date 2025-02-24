# Functions

- Variables are created and destroyed at runtime.
- The lifetime of a variable (how long it exists in memory) is a runtime property.
- Variable scope (where it can be accessed) is primarily determined at compile time and enforced by the compiler.

## Declaration  
Tells the compiler about an identifier and its associated type information.  
```cpp
void foo();     // Function forward declaration (no body)
void goo() {};  // Function definition (has body)
int x;          // Variable definition
```

## Definition
Definitions are also declarations.
```cpp
void foo() {}  // Function definition (has body)
int x;          // Variable definition
```

## Pure Declaration
A declaration that isn’t a definition.
```cpp
void foo();     // Function forward declaration (no body)
``` 

## Initialization
Provides an initial value for a defined object.
```cpp
int x { 2 };    // x is initialized to value 2
```


