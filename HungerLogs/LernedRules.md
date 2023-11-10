1. One Definition Rule
    in c++ it deals with classes/structs only having one definition in the entire program
    a translation unit is the ultimate input into a C/C++ compiler from which object file is generated
2. If you're going to define a class in a header file (.h), then you probably want to put an inclusion guard 
    to avoid redifinition. that looks like this:
        #ifndef TRANSACTION_H
        #define TRANSACTION_H
    this ensures that it is defined only in one translation unit.