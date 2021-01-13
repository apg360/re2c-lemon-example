#pragma once

// https://data-flair.training/blogs/union-in-c-language/
// union means only one member can be accessed at a time in a union.
// Only one data member of a union can be accessed at one time.
// Not a struct with many members but a struct with one single member, that can be one of those.
// A union prohibits the initialization of all its data members. The first member of the union can only be initialized through an object.
// ll the data members of a union share the same memory location. Hence, changes made in one data member inevitably affects the other.
union Token {
    double   number;
    char     string[255];
};

