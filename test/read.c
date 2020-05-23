#include "InputStream.h"
#include "Wasm.h"

int main(int argc,char** argv){
	InputStream in=open(argv[1]);
	WasmModule wm=readModule(in);
	deleteModule(wm);
	close(in);
	in=open(argv[1]);
	WasmUninterpretedModule wm1=readUninterpreted(in);
	deleteUninterpretedModule(wm1);
	close(in);
}
