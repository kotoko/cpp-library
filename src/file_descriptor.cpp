#include <unistd.h>

#include "file_descriptor.hpp"


namespace
{
#ifndef NDEBUG
	constexpr bool DEB = true;
#else
	constexpr bool DEB = false;
#endif
}

FileDescriptor::FileDescriptor(int fd) noexcept : fd_(fd)
{}

FileDescriptor::~FileDescriptor() noexcept
{
	close(fd_);
}

FileDescriptor::operator int() const noexcept
{
	return fd_;
}
