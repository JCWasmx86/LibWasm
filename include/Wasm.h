#include "InputStream.h"
#include "WasmStructs.h"
#include <limits.h>
#include <stdint.h>
#include <wchar.h>
#ifndef _WASM_H
#define _WASM_H
#define CUSTOM_SECTION 0
#define TYPE_SECTION 1
#define IMPORT_SECTION 2
#define FUNCTION_SECTION 3
#define TABLE_SECTION 4
#define MEMORY_SECTION 5
#define GLOBAL_SECTION 6
#define EXPORT_SECTION 7
#define START_SECTION 8
#define ELEMENT_SECTION 9
#define CODE_SECTION 10
#define DATA_SECTION 11
#define DATACOUNT_SECTION 12
#define TABLE_ELEMTYPE 0x70
#define FUNC_ID 0x60
#define LIMIT_MAX UINT_MAX
// Public API
WasmModule readModule(InputStream in);
WasmUninterpretedModule readUninterpreted(InputStream in);
void deleteModule(WasmModule module);
void deleteUninterpretedModule(WasmUninterpretedModule wm);
CustomSection findCustomSection(WasmUninterpretedModule wm, char *name);
CustomSection findCustomSectionW(WasmUninterpretedModule wm, wchar_t *name);
TypeSection findTypeSection(WasmUninterpretedModule wm);
ImportSection findImportSection(WasmUninterpretedModule wm);
FunctionSection findFunctionSection(WasmUninterpretedModule wm);
TableSection findTableSection(WasmUninterpretedModule wm);
MemorySection findMemorySection(WasmUninterpretedModule wm);
GlobalSection findGlobalSection(WasmUninterpretedModule wm);
ExportSection findExportSection(WasmUninterpretedModule wm);
StartSection findStartSection(WasmUninterpretedModule wm);
ElementSection findElementSection(WasmUninterpretedModule wm);
CodeSection findCodeSection(WasmUninterpretedModule wm);
DataSection findDataSection(WasmUninterpretedModule wm);
DataCountSection findDataCountSection(WasmUninterpretedModule wm);
// Private API
CustomSection readCustomSection(InputStream in, uint32_t sectionLength);
TypeSection readTypeSection(InputStream in);
ImportSection readImportSection(InputStream in);
FunctionSection readFunctionSection(InputStream in);
TableSection readTableSection(InputStream in);
MemorySection readMemorySection(InputStream in);
GlobalSection readGlobalSection(InputStream in);
ExportSection readExportSection(InputStream in);
StartSection readStartSection(InputStream in);
ElementSection readElementSection(InputStream in);
CodeSection readCodeSection(InputStream in);
DataSection readDataSection(InputStream in);
DataCountSection readDataCountSection(InputStream in);
FuncType readFuncType(InputStream in);
Import readImport(InputStream in);
TableType readTable(InputStream in);
MemType readMemory(InputStream in);
Global readGlobal(InputStream in);
Export readExport(InputStream in);
Element readElement(InputStream in);
Code readCode(InputStream in);
Data readData(InputStream in);
ImportDescriptor readImportDescriptor(InputStream in);
Limit readLimit(InputStream in);
GlobalType readGlobalType(InputStream in);
ExportDescriptor readExportDescriptor(InputStream in);
Function readFunction(InputStream in, uint32_t size);
void freeGlobaltype(GlobalType tt);
void freeMemory(MemType tt);
void freeTable(TableType tt);
void deleteSection(Section s);
void freeCustomSection(CustomSection cs);
void freeTypeSection(TypeSection ts);
void freeFuncType(FuncType ft);
void freeImportSection(ImportSection is);
void freeImport(Import import);
void freeImportDescriptor(ImportDescriptor id);
void freeFunctionSection(FunctionSection fs);
void freeTableSection(TableSection ts);
void freeMemorySection(MemorySection ms);
void freeGlobalSection(GlobalSection gs);
void freeGlobal(Global g);
void freeExportSection(ExportSection es);
void freeExport(Export e);
void freeExportDescriptor(ExportDescriptor ed);
void freeStartSection(StartSection startSection);
void freeElementSection(ElementSection es);
void freeElement(Element e);
void freeCodeSection(CodeSection cs);
void freeCode(Code c);
void freeFunction(Function f);
void freeDataSection(DataSection ds);
void freeData(Data d);
void deleteWasmSection(uint8_t id, WasmSection ws);
#endif
