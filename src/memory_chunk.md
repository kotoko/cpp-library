## MemoryChunk
Wrapper for operators new & delete in RAII style. Class allows you to allocate some memory block. It gives you pointer to memory. Class call delete in destructor.

### Why not `std::array`?
`std::array` needs to know size of array at compile time. `MemoryChunk` allocates memory during runtime.

### Notes
* header-only
* uses GSL

### Example
```
#include <iostream>
#include "memory_chunk.hpp"

void f(MemoryChunk<char>& buff) {
	char letter = 'a';
	for(int i = 0; i < buff.length(); ++i) {
		// More verbose version.
		*(buff.ptr() + i) = letter;

		// Alternative version.
		*(buff + i) = letter;
	}
}

int main() {
	int n;
	std::cin >> n;

	MemoryChunk<char> buff(n);
	f(buff);

	return 0;
}

```
