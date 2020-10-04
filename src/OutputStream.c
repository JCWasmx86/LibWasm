#include "OutputStream.h"
#include <locale.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void writeUleb(OutputStream out, uint32_t v) {
	do {
		uint8_t b = v & 0x7f;
		v >>= 7;
		if (v)
			b |= (1 << 7);
		fputc(b, out->file);
		out->pos++;
	} while (v);
}
void writeUleb64(OutputStream out, uint64_t v) {
	do {
		uint8_t b = v & 0x7f;
		v >>= 7;
		if (v)
			b |= (1 << 7);
		fputc(b, out->file);
		out->pos++;
	} while (v);
}
void writeLeb(OutputStream out, int32_t v) {
	int more = 1;
	while (more) {
		uint8_t b = v & 0x7f;
		v >>= 7;
		if ((v == 0 && (b & 0x40) == 0) || (v == -1 && ((b & 0x40) != 0)))
			more = 0;
		else
			b |= (1 << 7);
		fputc(b, out->file);
		out->pos++;
	}
}
void writeLeb64(OutputStream out, int64_t v) {
	int more = 1;
	while (more) {
		uint8_t b = v & 0x7f;
		v >>= 7;
		if ((v == 0 && (b & 0x40) == 0) || (v == -1 && ((b & 0x40) != 0)))
			more = 0;
		else
			b |= (1 << 7);
		fputc(b, out->file);
		out->pos++;
	}
}
void writeFloatIEEE754(OutputStream out, float f) {
	fwrite(&f, 4, 1, out->file);
	out->pos += 4;
}
void writeDoubleIEEE754(OutputStream out, double d) {
	fwrite(&d, 8, 1, out->file);
	out->pos += 8;
}
// TODO: Currently no unicode support, as I can't think of
// a way to decode one wchar_t and say
//"That wchar_t is one, two, three or four bytes"
void writeName(OutputStream out, const wchar_t *name) {
	size_t len = wcslen(name);
	writeUleb(out, len);
	for (size_t i = 0; i < len; i++) {
		wchar_t ch = name[i];
		fputc(ch, out->file);
		out->pos++;
	}
}
void writeOneByte(OutputStream out, uint8_t b) {
	fputc(b, out->file);
	out->pos++;
}
void writeNBytes(OutputStream out, uint32_t cnt, uint8_t *outBytes) {
	fwrite(outBytes, 1, cnt, out->file);
	out->pos += cnt;
}
void writeByteVectors(OutputStream out, uint8_t *bytes, uint32_t count) {
	writeUleb(out, count);
	fwrite(bytes, 1, count, out->file);
	out->pos += count;
}
OutputStream openOutputStream(const char *name) {
	OutputStream ret = malloc(sizeof(struct _outputStream));
	ret->file = fopen(name, "wb");
	ret->pos = 0;
	return ret;
}
OutputStream openOutputStreamW(const wchar_t *name) {
	setlocale(LC_ALL, "");
	char *tmp = calloc(wcslen(name) + 1, 1);
	wcstombs(tmp, name, wcslen(name));
	OutputStream ret = openOutputStream(tmp);
	free(tmp);
	return ret;
}
void closeOutputStream(OutputStream in) {
	fclose(in->file);
	free(in);
}
