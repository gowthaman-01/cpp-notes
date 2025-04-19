#include <iostream>

/*
 * 1. Namespaces
 * - Small personal applications usually don't need namespaces.
 * - For larger personal projects with third-party libraries, use your own namespace to avoid naming collisions.
 *
 * - Any code intended for reuse or distribution should always be placed in a namespace.
 * - A single top-level namespace (e.g., Foologger) is often enough.
 * - This also enables autocomplete and suggestions in IDEs (e.g., Foologger::).
 *
 * - In multi-team or enterprise environments, use multi-level namespaces:
 *      Project::Module               (e.g., Foologger::Lang)
 *      Company::Library              (e.g., Foosoft::Foologger)
 *      Company::Library::Module      (e.g., Foosoft::Foologger::Lang)
 *
 * - Use module-level namespaces to separate reusable code (e.g., Math::, Lang::) from application-specific code.
 * - You can also separate reusable and app-specific code using directory structure.
 *
 * - Avoid deeply nested namespaces (more than 3 levels), as they reduce readability.
 *
 * 2. inline and unnamed namespaces
 * - Prefer unnamed namespaces when you have content you want to keep local to a translation unit.
 * - Avoid unnamed namespaces in header files.
 *
 * - Use inline namespaces to manage versioning of APIs while maintaining backward compatibility.
 * - Only one inline namespace should be active (unqualified) at a time; others must be explicitly referenced.
 * - Avoid mixing inline and unnamed namespaces at the same level — it can lead to ambiguous symbol resolution.
 *
 * 3. using-statements
 * - Prefer explicit namespace qualifiers over using-statements.
 * - Avoid using-directives altogether (except `using namespace std::literals` to access the s and sv literal suffixes).
 * - Using-declarations (e.g, using std::cout` are okay in .cpp files, after the #include directives.
 * - Do not use using-statements in header files (especially in the global namespace of header files).
 */

namespace {
    int doSomething(int x, int y) {
        return x + y;
    }
}

namespace Foo {
    // This doSomething() belongs to namespace Foo.
    int doSomething(int x, int y) {
        return x - y;
    }
}

namespace Goo {
    // This doSomething() belongs to namespace Goo.
    int doSomething(int x, int y) {
        return x * y;
    }
}; // Semicolon optional unlike structs, enums and classes.

/*
 * Foo must be defined before using Foo::Goo.
 * Even though there's already a global namespace named Goo,
 * this Goo is nested inside Foo and is completely independent.
*/
namespace Foo::Goo {
    int doSomething(int x, int y) {
        return x / y;
    }
}

void Bar() {
    int boo = ::doSomething(6, 3);              // 9
    int foo = Foo::doSomething(6, 3);           // 3
    int goo = Goo::doSomething(6, 3);           // 18
    
    namespace FooGoo = Foo::Goo;                // Namespace alias
    int fooGoo = FooGoo::doSomething(6, 3);     // 2
}
