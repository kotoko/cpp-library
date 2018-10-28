#ifndef FILEDESCRIPTOR_HPP
#define FILEDESCRIPTOR_HPP


/* Wrapper for file descriptor (RAII). In constructor
 * shall pass already opened fd. In destructor class
 * call close() on fd.
 *
 * Recommended usage with shared_ptr().
 */
class FileDescriptor
{
public:
	FileDescriptor(int fd) noexcept;
	FileDescriptor(const FileDescriptor& other) = delete;
	FileDescriptor(FileDescriptor&& other) = delete;
	~FileDescriptor() noexcept;
	FileDescriptor& operator=(const FileDescriptor& other) = delete;
	FileDescriptor& operator=(FileDescriptor&& other) = delete;
	operator int() const noexcept;

private:
	const int fd_;

};


#endif //FILEDESCRIPTOR_HPP
