structs similar to objects/classes in other languages but no inheritance or class methods or static variables

Structs

- group multiple fields/data points -> into one object
- only data no methods/behaviors
- access with dot or with a pointer using car->model | car.model

order matters
memory 0001 0002 0003 0004
[ , age, name, is_alive, ]
| | |
-struct------
stored side by side in memory

https://en.cppreference.com/c/language/struct_initialization

struct is a type consisting of a sequence of members whose storage is allocated in an ordered sequence.

struct Example Struct {
int i; // 4 bytes
char c; // 1 byte
}
if stuct stars at mem address 0x1000

Address: 0x1000 0x1001 0x1002 0x1003 0x1004 (0x1005 - 0x1007)
+-------+-------+-------+-------+-------+-------------------+
Memory: | i | c | padding (3 bytes)|
+-------+-------+-------+-------+-------+-------------------+

A union is a type consisting of a sequence whose storage overlaps. (stacked on top of each other). The compiler only allocates enough memory for the single largest member. Every member in the union starts at the exact same memory address (offset 0) occupying the same physical bytes.

union ExampleUnion {
int i; // 4 bytes
char c; // 1 byte
}

If this union starts at memory address 0x1000, the memory looks like this:\

Address: 0x1000 0x1001 0x1002 0x1003
+-------+-------+-------+-------+
View i: | i | (uses all 4 bytes)
+-------+-------+-------+-------+
View c: | c | (uses only the first byte!)
+-------+
