#include "InputStream.h"
#include "Wasm.h"
#include <stdlib.h>

int main(int argc, char **argv) {
	InputStream in = openInputStream(argv[1]);
	WasmModule wm = readModule(in);
	deleteModule(wm);
	closeInputStream(in);
	in = openInputStream(argv[1]);
	WasmUninterpretedModule wm1 = readUninterpreted(in);
	deleteUninterpretedModule(wm1);
	closeInputStream(in);
	return EXIT_SUCCESS;
}
