## FileDescriptor
Wrapper for file descriptor (RAII). In constructor shall pass already opened fd (int). In destructor class call close() on fd.

### Notes
* linux/unix only
* recommended usage with shared_ptr

### Examples
Simple example:
```
#include "file_desciptor.hpp"

void hello() {
	int tmp = open_file(...);  // Returns file descriptor.
	FileDescriptor text_file(tmp);

	// Do something.
	//write(text_file, "Hello world!", 12);

	// When returning from this function destructor of text_file
	// is called, thus file descriptor automatically closed.
	return;
}

int main() {
	hello();
	return 0;
}
```

Example with shared_ptr:
```
#include <memory>
#include "file_desciptor.hpp"

int main() {
	int tmp;
	std::shared_ptr<FileDescriptor> text_file(nullptr);

	tmp = open_file(...);  // Returns file descriptor.

	try {
		text_file = std::make_shared<FileDescriptor>(tmp);
	} catch(...) {
		close(tmp);
		throw;
	}

	// Do something.
	//write(*text_file, "Hello world!", 12);

	// File descriptor is guarder also against exceptions.
	//throw std::bad_alloc();

	// You can also manually close file descriptor (see documentation of shared_ptr).
	text_file.reset();

	return 0;
}
```
