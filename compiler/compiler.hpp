#ifndef COMPILER_HPP
// Code below this line will only be compiled if compiler_hpp is not defined before.
// This is to prevent multiple inclusions of the same file.

// Here we define COMPILER_HPP, so subsequent includes will be ignored.
#define COMPILER_HPP

// C++ like syntax:
// #if defined(COMPILER_HPP)
// #if !defined(COMPILER_HPP)

// Note: Header guards prevent multiple inclusions by defining a macro,
// so they work even if the same file is copied to multiple locations.
// #pragma once relies on file paths, so it can fail if the same header file
// is copied to different locations and included from both.
#pragma once

}

#endif /* compiler_hpp */
