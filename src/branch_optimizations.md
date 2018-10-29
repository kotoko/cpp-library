## Branch optimizations
Define two macros: `likely(x)` and `unlikely(x)`. These macros are hints for compiler what value should expect. Compiler _may_ try to use this information to rearrange assembly code and avoid cache misses. Macros are adopted from linux kernel.

### Explanation
GCC has `__builtin_expect(x, n)`. It says expression `x` probably have value `n`. `likely(x)` and `unlikely(x)` assumes that `x` is a bool expression. `likely(x)` is a hint that expression `x` probably has value `true`. `unlikely(x)` is a hint that expression `x` probably has value `false`. The most common usage is inside `if()` statement. Because inside `if()` there is a bool expression thus names are `likely()`, `ulikely()` - _"we (un)likely get inside this if"_. See? Makes sense.

### Notes
* GCC only
* optimizations are turned off by default
* to turn on optimizations pass `-DOPTIMISE_BRANCHES` as parameter to GCC

### Example
Let's assume we have this loop:
```
int main() {
	int status;
	while(true) {
		status = ...
		if(status < 0) {
			// Do error handling.
		}
		else {
			// Do something.
		}
	}
	return 0;
}
```
We expect that errors happens rarely, so we can write this:
```
#include "branch_optimizations.hpp"
int main() {
	int status;
	while(true) {
		status = ...
		if(unlikely(status < 0)) {
			// Do error handling.
		}
		else {
			// Do something.
		}
	}
	return 0;
}
```
Or something like this:
```
#include "branch_optimizations.hpp"
int main() {
	int status;
	while(true) {
		status = ...
		if(likely(status >= 0)) {
			// Do something.
		}
		else {
			// Do error handling.
		}
	}
	return 0;
}
```
