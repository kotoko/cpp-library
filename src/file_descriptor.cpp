#include <unistd.h>

#include "file_descriptor.hpp"


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
