#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifndef _INPUTSTREAM_H
#define _INPUTSTREAM_H
typedef struct _inputStream {
	FILE *file;
	uint64_t pos;
} * InputStream;

uint32_t readUleb(InputStream in);
uint64_t readUleb64(InputStream in);
int32_t readLeb(InputStream in);
int64_t readLeb64(InputStream in);
// Read float
float readFloatIEEE754(InputStream in);
// Read double from inputstream
double readDoubleIEEE754(InputStream in);
// Read string, returns NULL on error.
const wchar_t *readName(InputStream in);
// Read one byte.
int readOneByte(InputStream in, uint8_t *into);
// Read n bytes, returns NULL on error.
uint8_t *readNBytes(InputStream in, uint32_t howMany);
// Open an input stream. Returns NULL on error
InputStream openInputStream(const char *name);
// Open an input stream. Returns NULL on error
InputStream openInputStreamW(const wchar_t *name);
// Close the inputstream
void closeInputStream(InputStream in);
#endif
