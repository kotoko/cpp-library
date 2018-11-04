## MemoryChunk
Wrapper for operators new & delete in RAII style. Class allows you to allocate some memory block. It gives you pointer to memory. Class call delete in destructor.

### Why not std::array?
`std::array` needs to know size of array at compile time. `MemoryChunk` allocates memory during runtime.

### Notes
* header-only
* uses GSL
* you can't resize MemoryChunk, but you can construct new one and swap them

### Example
```
#include <iostream>
#include "memory_chunk.hpp"

void f(MemoryChunk<char>& buff) {
	for(int i = 0; i < buff.length(); ++i) {
		// More verbose version.
		*(buff.ptr() + i) = 'A';

		// Alternative version.
		*(buff + i) = 'A';
	}
}

int main() {
	int n;
	std::cin >> n;

	MemoryChunk<char> buff(n);
	f(buff);

	// MemoryChunk guards against exceptions (no memory leaks).
	//throw std::logic_error();

	return 0;
}

```
