#include "InputStream.h"
#include "OutputStream.h"
#include <limits.h>
#include <stdint.h>

int main(int argc, char **argv) {
	for (uint32_t i = 0; i < UINT_MAX - 10001; i += 10000) {
		OutputStream out = openOutputStream("test.uleb");
		writeUleb(out, i);
		closeOutputStream(out);
		InputStream in = openInputStream("test.uleb");
		uint32_t a = readUleb(in);
		if (a != i) {
			printf("UINT32_t: %d != %d\n", i, a);
		}
		close(in);
	}
	printf("********************************************************\n");
	for (uint64_t i = 0; i < 12U * (1000L * 1000L * 1000L); i += 500000) {
		OutputStream out = openOutputStream("test.uleb");
		writeUleb64(out, i);
		closeOutputStream(out);
		InputStream in = openInputStream("test.uleb");
		uint64_t a = readUleb64(in);
		if (a != i) {
			printf("UINT64_t: %llu != %llu\n", i, a);
		}
		close(in);
	}
	printf("********************************************************\n");
	for (int32_t i = -2 * (1000L * 1000L * 1000L);
		 i < 2 * (1000L * 1000L * 1000L); i += 200000) {
		OutputStream out = openOutputStream("test.uleb");
		writeLeb(out, i);
		closeOutputStream(out);
		InputStream in = openInputStream("test.uleb");
		int32_t a = readLeb(in);
		if (a != i) {
			printf("INT32_T: %d != %d\n", i, a);
		}
		close(in);
	}
	printf("********************************************************\n");
	for (int64_t i = -12L * (1000 * 1000 * 1000);
		 i < 12L * (1000 * 1000 * 1000); i += 1000000) {
		OutputStream out = openOutputStream("test.uleb");
		writeLeb64(out, i);
		closeOutputStream(out);
		InputStream in = openInputStream("test.uleb");
		int64_t a = readLeb64(in);
		if (a != i) {
			printf("INT64_t: %lld != %lld\n", i, a);
		}
		close(in);
	}
	printf("********************************************************\n");
	for (double d = -4000000000.0; d < 400000000000.0; d += 100000000) {
		OutputStream out = openOutputStream("test.uleb");
		writeDoubleIEEE754(out, d);
		closeOutputStream(out);
		InputStream in = openInputStream("test.uleb");
		double a = readDoubleIEEE754(in);
		if (a != d) {
			printf("FLOAT: %lf != %lf\n", d, a);
		}
		close(in);
	}
	printf("********************************************************\n");
	for (float d = -4000000000.0; d < 400000000000.0; d += 100000000) {
		OutputStream out = openOutputStream("test.uleb");
		writeFloatIEEE754(out, d);
		closeOutputStream(out);
		InputStream in = openInputStream("test.uleb");
		float a = readFloatIEEE754(in);
		if (a != d) {
			printf("DOUBLE: %lf != %lf\n", d, a);
		}
		close(in);
	}
	return 0;
}
