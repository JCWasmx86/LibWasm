# LibWasm
LibWasm is a library to read Webassembly files.
## Usage
There are two ways to read a Webassembly file:
1. Use `readModule` to get a `WasmModule`.
2. Use `readUninterpreted` to get a `WasmUninterpretedModule`.
Both take an `InputStream`-struct, you obtain by calling `open` with the 
filename as argument. Returns NULL, if the file couldn't be openend.
The difference between `WasmModule` and `WasmUninterpretedModule` is that
in the first LibWasm tries to interpret each section, so you can simply do:
`wasmModule->importSection` to access the import section.
In the latter, the order of the sections is preserved, so you have to call
`findImportSection` to get either NULL or a pointer to the importSection.
To release a module use `deleteModule` or `deleteUninterpretedModule`.
