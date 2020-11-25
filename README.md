# String
Some methods to manage strings using C (and if you want using C++).

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

int (*fcmp)(char, char) is a pointer to a function you can passed to
some methods to compare two charcters. So changing this function you
can have a sensitive or insensitive comparing.
