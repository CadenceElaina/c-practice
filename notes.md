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

The padding of 3 bytes x1005-x1007 makes the struct 8 bytes total - the padding is added for CPU alignment: modern CPUs dont read memory 1 byte at a time; they read memory in aligned chunks (multiples of 4 or 8 bytes).

A 4-byte int MUST start at a memory address that is a multiple of 4 x1000 x1004 x1008, ... etc.

A union is a type consisting of a sequence whose storage overlaps. (stacked on top of each other). The compiler only allocates enough memory for the single largest member. Every member in the union starts at the exact same memory address (offset 0) occupying the same physical bytes.

union ExampleUnion {
int i; // 4 bytes
char c; // 1 byte
}

If this union starts at memory address 0x1000, the memory looks like this:

Address: 0x1000 0x1001 0x1002 0x1003
+-------+-------+-------+-------+
View i: | i | (uses all 4 bytes)
+-------+-------+-------+-------+
View c: | c | (uses only the first byte!)
+-------+

- Variables dont actually exist in physical RAM only raw bytes (1s and 0s) exist in RAM

run d.num = 65; // writes across all 4 bytes starting at

Address: 0x1000 0x1001 0x1002 0x1003
+-----------+-----------+-----------+-----------+
Bytes: | 0100 0001 | 0000 0000 | 0000 0000 | 0000 0000 |
+-----------+-----------+-----------+-----------+
(65 / 'A') (0) (0) (0)

128 64 32 16 8 4 2 1
0 1 0 0 0 0 0 1
64+1 = 65 yep mhm thats binary for ya
'A' = 65 ASCII

if you read d.byte C goes to 0x1000 and reads 1 byte (0100 0001)

d.byte = 'B'; (66 in ASCII)... C goes to 0x1000 and overwrites only the first byte:

Address: 0x1000 0x1001 0x1002 0x1003
+-----------+-----------+-----------+-----------+
Bytes: | 0100 0010 | 0000 0000 | 0000 0000 | 0000 0000 |
+-----------+-----------+-----------+-----------+
(66 / 'B') (0) (0) (0)

d.num and d.byte can share the exact same memory address because they arent two physical objects fighting for space in RAM; theyre just two different compile-time instructions. One saying grab 4 bytes at 0x1000 and the other telling the CPU to grab 1 byte at 0x1000

Memory Address: 0x1000 0x1001 0x1002 0x1003
+-------------+-------------+-------------+-------------+
Step 1: | 0100 0001 | 0000 0000 | 0000 0000 | 0000 0000 |
d.num = 65; | (val: 65) | (val: 0) | (val: 0) | (val: 0) |
+-------------+-------------+-------------+-------------+
|<--------- d.num reads ALL 4 bytes (= 00000065) ------>|
|<- d.byte ->| (d.byte only looks at 0x1000 = 65 / 'A')

Memory Address: 0x1000 0x1001 0x1002 0x1003
+-------------+-------------+-------------+-------------+
Step 2: | 0100 0010 | 0000 0000 | 0000 0000 | 0000 0000 |
d.byte = 'B'; | (val: 66) | (val: 0) | (val: 0) | (val: 0) |
+-------------+-------------+-------------+-------------+
|<--------- d.num reads ALL 4 bytes (= 00000066) ------>|
|<- d.byte ->| (d.byte only looks at 0x1000 = 66 / 'B')

Uses for unions:

1. Mutually exclusive data (saving memory): packet that holds int or a float. Never both at the same time. Instead of wasting 8 bytes on a struct you use a 4-byte union. When its holding an int you only ever read/write the int field. When you switch to storing a float you overwrite it to use the float field instead
2. Low-level byte inspection: Like the example above, where you put a 4-byte integer in and read individual bytes out.

bit is a single binary (0 or 1)
byte is a group of 8 bits (0100 0001)
x86_64 is a cpu hardware architecture. These chips are "Little-Endian" meaning they store the lowest byte of a multi-byte number at the first memory address (0x1000) which is why d.byte overlapped with the 65 instead of the 0s

(void*)&d.num has nothing to do with the union being empty or uninitialized
&d.num has type int* a pointer to an int
&d.byte has the type char\* a pointer to a char

- in C, printf's %p format specifier (prints a memory address in hexadecimal) is strictly defined by the C standard to expect a generic pointer type which is called void\*
- In C, void* is not an "empty pointer" or "no value" (which is NULL). Instead, void* means "a raw memory address with no specific data type attached to it". Compiling with strict flags will have the compiler complain if you used int* to %p without casting it to (void*) first.

In older C standards (prior to C23) empty parentheses for int func() meant this function takes an unknown number of arguments. Whereas int func(void) explicitly means this function takes zero arguments.

- So writing int main(void) is the classic C best practice to tell the compiler strictly no parameters are allowed here.

1. CPU registers & cache (L1/L2/L3) are built directly onto the CPU silicon - very fast near instant with tiny capacity and are wiped on a power off.
2. Physical RAM (Primary Memory): The RAM sticks on the motherboard. Billions of microscopic capacitors/transistors holding charges (1 or 0). Very fast not as fast as registers/cache. Gigabytes in size and also volatile (wiped on reboot/power off)
3. Secondary Storage (SSD/ NVMe): Flash memory where files and compiled binary live. Much slower than RAM but non-volatile (persists across reboots).

Example A: Quant / Market Data Feed (Order Book Packets)

Imagine an exchange sending millions of messages per second to a trading engine. Every message starts with a header (ticker and message_type), followed by a payload.
An incoming packet can be one of three mutually exclusive events:

    A Trade Execution (needs double execution_price + int shares_traded)

    An Order Cancel (only needs long order_id—no price needed!)

    A Trading Halt (only needs char halt_reason_code—no price or order ID needed!)

struct MarketPacket {
char ticker[4]; // Always needed: e.g., 'M','S','F','T'
char packet_type; // Tag: 'T' = Trade, 'C' = Cancel, 'H' = Halt

    // Mutually exclusive payload: shares the same memory!
    union {
        struct { double price; int shares; } trade; // Used ONLY if packet_type == 'T'
        long canceled_order_id;                     // Used ONLY if packet_type == 'C'
        char halt_reason;                           // Used ONLY if packet_type == 'H'
    } payload;

};
If you didn't use a union for payload, every single packet in memory would waste bytes carrying empty fields for canceled_order_id and halt_reason even when it's a trade.
