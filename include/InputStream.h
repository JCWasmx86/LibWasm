#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
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
float readFloatIEEE754(InputStream in);
double readDoubleIEEE754(InputStream in);
const wchar_t *readName(InputStream in);
int readOneByte(InputStream in, uint8_t *into);
uint8_t *readNBytes(InputStream in, uint32_t howMany);
InputStream open(const char *name);
InputStream openW(const wchar_t *name);
void close(InputStream in);
#endif
