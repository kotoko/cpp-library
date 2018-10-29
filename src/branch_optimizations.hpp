#ifndef BRANCH_OPTIMIZATIONS_HPP
#define BRANCH_OPTIMIZATIONS_HPP

#ifdef OPTIMISE_BRANCHES
#define likely(x)     __builtin_expect(static_cast<bool>(x), 1)
#define unlikely(x)   __builtin_expect(static_cast<bool>(x), 0)
#else
#define likely(x)     (x)
#define unlikely(x)   (x)
#endif

#endif //BRANCH_OPTIMIZATIONS_HPP
