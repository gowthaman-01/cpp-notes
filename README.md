# C++ Knowledge Dump

- Each family of compatible CPUs (e.g. x86, Arm64) has its own machine language, and this machine language is not compatible with the machine language of other CPU families.

- Machine and assembly languages are CPU-specific, while high-level languages are more portable.

- [Intepreters vs Compilers](https://stackoverflow.com/questions/38491212/difference-between-compiled-and-interpreted-languages/38491646#38491646)

- Global and static variables are initialized prior to the execution of main. If the initializer for such a variable invokes a function, then that function will execute prior to main.

- In most cases, a declaration is sufficient to allow the compiler to ensure an identifier is being used properly. However, there are a few cases where the compiler must be able to see a full definition in order to use an identifier (such as for template definitions and type definitions).

- If the colliding identifiers are introduced into the same file, the result will be a compiler error. If the colliding identifiers are introduced into separate files belonging to the same program, the result will be a linker error.

- A translation unit is the result of the preprocessor expanding #include directives and macros. The compiler compiles the translation unit, not the original .cpp file directly.


### TODO
- [Revise all C++ keywords](https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/#:~:text=alignas,xor_eq)


