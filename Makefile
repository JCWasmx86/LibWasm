CLANG=clang
CC=clang
CFLAGS+=-fPIE
WASMFLAGS+=--target=wasm32 -nostdlib -c
all:
	mkdir -p bin/obj
	$(CC) $(CFLAGS) -I"include" -O3 -Wall -Wextra -pedantic -c -o bin/obj/InputStream.o src/InputStream.c
	$(CC) $(CFLAGS) -I"include" -O3 -Wall -Wextra -pedantic -c -o bin/obj/OutputStream.o src/OutputStream.c
	$(CC) $(CFLAGS) -I"include" -O3 -Wall -Wextra -pedantic -c -o bin/obj/WasmModule.o src/WasmModule.c
	$(CC) $(CFLAGS) -I"include" -O3 -Wall -Wextra -pedantic -c -o bin/obj/LebUtils.o src/LebUtils.c
	$(CC) $(CFLAGS) -I"include" -O3 -Wall -Wextra -pedantic -c -o bin/obj/UninterpretedWasmModule.o src/UninterpretedWasmModule.c
	llvm-ar r bin/libwasm.a bin/obj/InputStream.o bin/obj/OutputStream.o bin/obj/WasmModule.o bin/obj/LebUtils.o bin/obj/UninterpretedWasmModule.o
all-debug:
	mkdir -p bin/obj
	$(CC) $(CFLAGS) -I"include" -O0 -g3 -Wall -Wextra -pedantic -c -o bin/obj/InputStream.o src/InputStream.c
	$(CC) $(CFLAGS) -I"include" -O0 -g3 -Wall -Wextra -pedantic -c -o bin/obj/OutputStream.o src/OutputStream.c
	$(CC) $(CFLAGS) -I"include" -O0 -g3 -Wall -Wextra -pedantic -c -o bin/obj/WasmModule.o src/WasmModule.c
	$(CC) $(CFLAGS) -I"include" -O0 -g3 -Wall -Wextra -pedantic -c -o bin/obj/LebUtils.o src/LebUtils.c
	$(CC) $(CFLAGS) -I"include" -O0 -g3 -Wall -Wextra -pedantic -c -o bin/obj/UninterpretedWasmModule.o src/UninterpretedWasmModule.c
	llvm-ar r bin/libwasm.a bin/obj/InputStream.o bin/obj/OutputStream.o bin/obj/WasmModule.o bin/obj/LebUtils.o bin/obj/UninterpretedWasmModule.o
test: all-debug compileTestCases
	$(CC) $(CFLAGS) -I"include" -g3 -O0 -Wall -Wextra -pedantic -c -Wno-unused-parameter -Wno-format -o bin/obj/EncodeDecodeTests.o test/EncodeDecodeTests.c
	$(CC) $(CFLAGS) -I"include" -g3 -O0 -Wall -Wextra -pedantic -c -Wno-unused-parameter -o bin/obj/read.o test/read.c
	$(CC) -o bin/encodeDecode bin/obj/InputStream.o bin/obj/OutputStream.o bin/obj/EncodeDecodeTests.o
	$(CC) -o bin/read bin/obj/read.o bin/obj/InputStream.o bin/obj/WasmModule.o
	cd bin&&./read test1.wasm&&cd ..
	cd bin&&./read test2.wasm&&cd ..
	cd bin&&./read test3.wasm&&cd ..
	cd bin&&./encodeDecode&&cd ..
compileTestCases:
	$(CLANG) $(WASMFLAGS) -O3 -o bin/test1.wasm test/testcases/test1.c
	$(CLANG) $(WASMFLAGS) -O3 -o bin/test2.wasm test/testcases/test2.c
	$(CLANG) $(WASMFLAGS) -O3 -o bin/test3.wasm test/testcases/test3.c
clean:
	rm -rf bin
format:
	find src include test -iname *.h -o -iname *.c | xargs clang-format --style=file -verbose -i
