#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

class CircularBuffer
{
public:
    CircularBuffer(unsigned int size);
    ~CircularBuffer();
    unsigned int	getReadSize() const;
    void		append(const void *ptr, unsigned int size);
    bool		hasCharacter(const char c) const;
    unsigned int	extract(void *buffer, unsigned int maxSize, const char delim = -1);
    unsigned int        extractKeepDelim(void *buffer,
                                         unsigned int maxSize, const char delim);
    char		getByte();
    bool		isEmpty() const;
    unsigned int	dropBack(unsigned int size);
    unsigned int	extractKeep(void *buffer, unsigned int maxSize, const char delim = -1);
    unsigned int	restore(unsigned int size);
    unsigned int	drop(unsigned int size);
    char                getByteKeep() const;

protected:
    char	*_buf;
    int		_readPtr;
    int		_writePtr;
    int		_len;
};

#endif // CIRCULARBUFFER_H
