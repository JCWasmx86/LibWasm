#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#ifndef _OUTPUTSTREAM_H
#define _OUTPUTSTREAM_H
typedef struct _outputStream {
	FILE *file;
	uint64_t pos;
} * OutputStream;
void writeUleb(OutputStream out, uint32_t v);
void writeUleb64(OutputStream out, uint64_t v);
void writeLeb(OutputStream out, int32_t v);
void writeLeb64(OutputStream out, int64_t v);
void writeFloatIEEE754(OutputStream out, float f);
void writeDoubleIEEE754(OutputStream out, double d);
void writeName(OutputStream out, const wchar_t *name);
void writeOneByte(OutputStream out, uint8_t b);
void writeNBytes(OutputStream out, uint32_t cnt, uint8_t *outBytes);
void writeByteVectors(OutputStream out, uint8_t *bytes, uint32_t count);
OutputStream openOutputStream(const char *name);
OutputStream openOutputStreamW(const wchar_t *name);
void closeOutputStream(OutputStream in);
#endif
