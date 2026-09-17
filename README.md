C++ Modules

My implementation of the C++ modules from 42 School, covering the fundamentals of modern C++ from Module 00 through Module 09.

The modules progressively introduce object-oriented programming, memory management, inheritance, polymorphism, templates, exceptions, and the Standard Template Library (STL).

Modules
Module	Topics
CPP 00	Namespaces, classes, member functions, stdio streams, initialization lists, static members
CPP 01	Memory allocation, references, pointers to members, file streams, switch
CPP 02	Ad-hoc polymorphism, operator overloading, Orthodox Canonical Form, fixed-point numbers
CPP 03	Inheritance, base and derived classes
CPP 04	Subtype polymorphism, abstract classes, interfaces
CPP 05	Exceptions, exception handling, custom exception classes
CPP 06	C++ casts: static_cast, dynamic_cast, reinterpret_cast, const_cast
CPP 07	Templates and generic programming
CPP 08	Templated containers, iterators, algorithms
CPP 09	STL containers, iterators, algorithms, practical data structures
Structure
cpp_modules/
│
├── CPP00/
│   ├── ex00/
│   ├── ex01/
│   ├── ex02/
│   └── ...
│
├── CPP01/
│   ├── ex00/
│   ├── ex01/
│   └── ...
│
├── CPP02/
├── CPP03/
├── CPP04/
├── CPP05/
├── CPP06/
├── CPP07/
├── CPP08/
└── CPP09/


The exact exercise structure follows the 42 School subject requirements for each module.

What I Learned
Object-Oriented Programming

Classes and objects

Encapsulation

Constructors and destructors

Copy constructors

Assignment operators

Inheritance

Polymorphism

Abstract classes

Interfaces

C++ Language Features

References

Pointers

Static members

Namespaces

Operator overloading

Function overloading

Exceptions

Type casting

Templates

Standard Template Library

Containers

Iterators

Algorithms

Generic programming

Practical use of STL data structures

Compilation

The projects are designed to compile with a C++ compiler supporting the required C++ standard.

Typical compilation:

c++ -Wall -Wextra -Werror -std=c++98 *.cpp


Individual exercises may use their own Makefile and compilation rules.

Requirements

C++ compiler

make

Unix-like environment

C++98 standard

42 School

These exercises are part of the C++ Piscine / C++ modules curriculum at 42 School.

The goal is to progressively transition from C to C++ and develop a solid understanding of object-oriented and generic programming.

Language: C++
Modules: 00 → 09
School: 42
