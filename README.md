# CArgs
A C/C++ argument parser library

## Requirements
* GCC
* Cmake
* make

## Installation
1. Inside project, make a directory named 'build': `mkdir build`
2. Change directory to 'build' folder: `cd build`
3. Execute cmake command: `cmake ..`
4. Make project: `make`
5. Install library: `make install`

## Usage
Create an array of `CargsMap_t` structure and define the arguments map:

````c
CargsMap_t *map = {
    {"first-name", 'f', true, "User first name"},
    {"last-name", 'l', true, "User last name"},
    {"email", 'e', false, "Email address"}
};
````

The `CargsMap_t` structure fields are:
* `w_key`: An string argument key and starts with two dashes (`--`) as input (Example: `--first-name`)
* `c_key`: A character argument key and starts with a dash (`-`) as input (Example: `-f`)
* `required`: If this flag be true, then it should include as input, Otherwise input is invalid
* `desc`: Description of argument that shows with `help` argument
* `value`: If value was provided in arguments input, the value of key will get copy in this field after parsing

Then declare a variable with type of `size_t` that contains length of map fields.

```c
size_t map_size = 3;
```

Then parse the arguments by passing **map array**, **map array length**, `int argc`, `char **argv` to `cargs_parse` function like this:

```c
cargs_parse(map, map_size, argc, argv);
```

Parsing will read fields from input and sets value of each map field from it.

You can validate the input after parsing by calling this function:

```c
bool is_valid = cargs_validate(map, map_size, true);
```

* First argument is array of map
* Second argument is length of map
* Third argument is boolean that determines after detecting an invalid argument exit from process or not 

Return value of this function is a boolean.

You can call `cargs_get` to get value of an argument:

```c
char* first_name = cargs_get(map, map_size, "first-name");
```

* First argument is array of map
* Second argument is length of map
* Third argument is `w_key` value of a map field. Then returns value of argument if exists. Otherwise returns `NULL` 

You can print help message by calling `cargs_help` function:

```c
cargs_help(map, map_size);
```

* First argument is array of map
* Second argument is length of map

Also, this message can display using `help` special argument:

```shell
./your_exe help
```

### Example

```c
#include <cargs/cargs.h>
#include <stdio.h>

int main(int argc, char **argv){
    CargsMap_t *map = {
        {"first-name", 'f', true, "User first name"},
        {"last-name", 'l', true, "User last name"},
        {"email", 'e', false, "Email address"}
    };
   size_t map_size = 3;
   cargs_parse(map, map_size, argc, argv);
   
   bool is_valid = cargs_validate(map, map_size, true);
   char* first_name = cargs_get(map, map_size, "first-name");
   char* last_name = cargs_get(map, map_size, "last-name");
   
   printf("User fullname: %s %s\n", first_name, last_name);
   return 0;
}
```

Execution:

```shell
./your_exe --first-name Pedram --last-name Dehghanpour
```