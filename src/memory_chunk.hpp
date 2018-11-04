#ifndef MEMORY_CHUNK_HPP
#define MEMORY_CHUNK_HPP

#include <cstddef>
#include <cstring>
#include <gsl/gsl>


/*
 * Wrapper for new & delete in RAII style. Class allows
 * you to allocate some memory block. It gives you pointer
 * to memory.
 */
template<typename T>
class MemoryChunk
{
private:
	T* memory_;
	std::size_t n_;

public:
	MemoryChunk(std::size_t n = 0);
	MemoryChunk(const MemoryChunk<T>& other) = delete;
	MemoryChunk(MemoryChunk<T>&& other) noexcept;
	MemoryChunk<T>& operator=(const MemoryChunk<T>& other) = delete;
	MemoryChunk<T>& operator=(MemoryChunk<T>&& other) noexcept;
	~MemoryChunk() noexcept;
	T* ptr() const noexcept;  // Pointer to memory.
	std::size_t size() const noexcept;  // Size in bytes.
	std::size_t length() const noexcept;  // Number of elements in array.
	void swap(MemoryChunk<T>& other) noexcept;
	void copy(const MemoryChunk<T>& other);  // Copy other's memory to this chunk (memcpy).
	void zero() noexcept;  // Set array's content to zero's (memset).
	explicit operator bool() const noexcept;  // Check if n != 0.
	operator T*() const noexcept;  // Pointer to memory.
};


template<typename T>
MemoryChunk<T>::MemoryChunk(std::size_t n) : n_(n)
{
	Expects(n >= 0);

	memory_ = new T [n];
}

template<typename T>
MemoryChunk<T>::~MemoryChunk() noexcept
{
	delete[] memory_;
}

template<typename T>
T* MemoryChunk<T>::ptr() const noexcept
{
	return memory_;
}

template<typename T>
std::size_t MemoryChunk<T>::size() const noexcept
{
	return n_ * sizeof(T);
}

template<typename T>
std::size_t MemoryChunk<T>::length() const noexcept
{
	return n_;
}

template<typename T>
MemoryChunk<T>::MemoryChunk(MemoryChunk<T>&& other) noexcept
{
	n_ = 0;
	memory_ = nullptr;

	(*this).swap(other);
}

template<typename T>
void MemoryChunk<T>::swap(MemoryChunk<T>& other) noexcept
{
	std::size_t tmp_n;
	T *tmp_memory;

	tmp_n = other.n_;
	tmp_memory = other.memory_;

	other.n_ = n_;
	other.memory_ = memory_;

	n_ = tmp_n;
	memory_ = tmp_memory;
}

template<typename T>
MemoryChunk<T>& MemoryChunk<T>::operator=(MemoryChunk<T>&& other) noexcept
{
	(*this).swap(other);

	return *this;
}

template<typename T>
void MemoryChunk<T>::copy(const MemoryChunk<T>& other)
{
	Expects(this != &other);
	Expects(n_ > 0);
	Expects(n_ == other.n_);

	std::memcpy(memory_, other.memory_, sizeof(T) * n_);
}

template<typename T>
void MemoryChunk<T>::zero() noexcept
{
	std::memset(memory_, 0, sizeof(T) * n_);
}

template<typename T>
MemoryChunk<T>::operator bool() const noexcept
{
	return n_ != 0;
}

template<typename T>
MemoryChunk<T>::operator T*() const noexcept
{
	return memory_;
}

#endif //MEMORY_CHUNK_HPP
