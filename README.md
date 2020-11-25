# String
Some methods to manage strings using C (and if you want using C++).

## Methods

| Method | Description |
|:----|:----|
sc_strnew | create a new empty String
sc_strdel | delete a String
sc_strcpy | copy a zero-ending string into a String
sc_strapp | append a zero-ending string to a String
sc_strins | insert a zero-ending string into a String at an offset
sc_strrep | replace a section of a String with a zero-ending string
sc_strpop | pop a section of a String
sc_strcmp | compare a zero-ending string to a String
sc_str2uc | String to uppercase String
sc_str2lc | String to lowercase String 
sc_strchr | search a character in a String
sc_strsch | search a zero-ending string in a String
sc_strsub | make a sub-string of a String

*_Note: `int (*fcmp)(char, char)` is a pointer to a function you can passed to
some methods to compare two charcters. So changing this function you
can have a sensitive or insensitive comparing._*

## Usage
To use String you have to include `string.h` into your C or C++ project and add `string.c` for compilation.
```C++
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

int main(int argc, char** argv) {
  if (argc == 3) {
    struct String* str = sc_strnew(NULL);
    if (str = sc_strcpy("Hello World! Hello World!", NULL)) {
      printf("cpy: {%s} [%d-%d]\n", str->data, str->used, str->size);
      if (str = sc_strrep(-1, argv[2], argv[1], str, &sc_chicmp)) {
        printf("rep: {%s} [%d-%d]\n", str->data, str->used, str->size);
        sc_strdel(str);
      }
    }
  }
  return 0;
}
```
