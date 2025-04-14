#pragma once

/*
 * It’s legal to declare namespace blocks in multiple locations.
 * All declarations within the namespace are considered part of the namespace.
 */
namespace Foo {
    // If Foo::doSomething() had not been found, the compiler would have checked the containing namespace,
    // (in this case, the global namespace), to see if it could match a doSomething() there.
    int doSomethingElse(int x, int y) {
        return ::doSomething(x, y)      // Calls the global
            + doSomething(x, y);        // Calls the one inside Foo
    }
}
