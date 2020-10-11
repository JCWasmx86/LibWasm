#include "InputStream.h"
#include "Wasm.h"
#include "WasmStructs.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EMERGENCY(x)                           \
	do {                                       \
		if (!x) {                              \
			emergencyFree(cnt, sections, ret); \
			return NULL;                       \
		}                                      \
	} while (0);
static void emergencyFree(int numberOfCustomSections,
						  CustomSection *customSections, WasmModule module);
static void emergencyFree(int numberOfCustomSections,
						  CustomSection *customSections, WasmModule module) {
	if (module->typeSection)
		freeTypeSection(module->typeSection);
	if (module->importSection)
		freeImportSection(module->importSection);
	if (module->functionSection)
		freeFunctionSection(module->functionSection);
	if (module->tableSection)
		freeTableSection(module->tableSection);
	if (module->memorySection)
		freeMemorySection(module->memorySection);
	if (module->globalSection)
		freeGlobalSection(module->globalSection);
	if (module->exportSection)
		freeExportSection(module->exportSection);
	if (module->startSection)
		freeStartSection(module->startSection);
	if (module->elementSection)
		freeElementSection(module->elementSection);
	if (module->dataCountSection)
		freeDataCountSection(module->dataCountSection);
	if (module->codeSection)
		freeCodeSection(module->codeSection);
	if (module->dataSection)
		freeDataSection(module->dataSection);
	for (int i = 0; i < numberOfCustomSections; i++) {
		freeCustomSection(customSections[i]);
	}
	free(customSections);
	free(module);
}
WasmModule readModule(InputStream in) {
	if (in == NULL)
		return NULL;
	uint8_t *magic = readNBytes(in, 4);
	if (!(magic[0] == 0x00 && magic[1] == 0x61 && magic[2] == 0x73 &&
		  magic[3] == 0x6d))
		return NULL;
	free(magic);
	uint8_t *version = readNBytes(in, 4);
	free(version);
	CustomSection *sections = malloc(8 * sizeof(struct _customS));
	if (!sections) {
		return NULL;
	}
	int cnt = 0;
	int max = 8;
	WasmModule ret = calloc(1, sizeof(struct _wasmModule));
	if (!ret) {
		free(sections);
		return NULL;
	}
	while (1) {
		uint8_t byte = 0;
		int byteCnt = readOneByte(in, &byte);
		if (byteCnt == 0) { // EOF
			break;
		}
		uint32_t sectionLength = readUleb(in);
		uint32_t start = in->pos;
		switch (byte) {
			case CUSTOM_SECTION: {
				CustomSection cs = readCustomSection(in, sectionLength);
				EMERGENCY(cs);
				if (cnt == max) {
					CustomSection *tmp =
						calloc(max * 2, sizeof(struct _customS));
					if (tmp == NULL) {
						emergencyFree(cnt, sections, ret);
						return NULL;
					}
					memcpy(tmp, sections, max);
					max *= 2;
					free(sections);
					sections = tmp;
				}
				sections[cnt++] = cs;
				break;
			}
			case TYPE_SECTION: {
				TypeSection ts = readTypeSection(in);
				EMERGENCY(ts);
				ret->typeSection = ts;
				break;
			}
			case IMPORT_SECTION: {
				ImportSection is = readImportSection(in);
				EMERGENCY(is);
				ret->importSection = is;
				break;
			}
			case FUNCTION_SECTION: {
				FunctionSection fs = readFunctionSection(in);
				EMERGENCY(fs);
				ret->functionSection = fs;
				break;
			}
			case TABLE_SECTION: {
				TableSection ts1 = readTableSection(in);
				EMERGENCY(ts1);
				ret->tableSection = ts1;
				break;
			}
			case MEMORY_SECTION: {
				MemorySection ms = readMemorySection(in);
				EMERGENCY(ms);
				ret->memorySection = ms;
				break;
			}
			case GLOBAL_SECTION: {
				GlobalSection gs = readGlobalSection(in);
				EMERGENCY(gs);
				ret->globalSection = gs;
				break;
			}
			case EXPORT_SECTION: {
				ExportSection es = readExportSection(in);
				EMERGENCY(es);
				ret->exportSection = es;
				break;
			}
			case START_SECTION: {
				StartSection ss = readStartSection(in);
				EMERGENCY(ss);
				ret->startSection = ss;
				break;
			}
			case ELEMENT_SECTION: {
				ElementSection es1 = readElementSection(in);
				EMERGENCY(es1);
				ret->elementSection = es1;
				break;
			}
			case DATACOUNT_SECTION: {
				DataCountSection ds1 = readDataCountSection(in);
				EMERGENCY(ds1);
				ret->dataCountSection = ds1;
				break;
			}
			case CODE_SECTION: {
				CodeSection cs1 = readCodeSection(in);
				EMERGENCY(cs1);
				ret->codeSection = cs1;
				break;
			}
			case DATA_SECTION: {
				DataSection ds = readDataSection(in);
				EMERGENCY(ds);
				ret->dataSection = ds;
				break;
			}
			default: {
				emergencyFree(cnt, sections, ret);
				return NULL;
			}
		}
		uint32_t end = in->pos;
		assert(end - start == sectionLength);
	}
	CustomSection *truncatedSections = malloc(cnt * sizeof(struct _customS));
	if (!truncatedSections) {
		emergencyFree(cnt, sections, ret);
	}
	memcpy(truncatedSections, sections, cnt * sizeof(struct _customS));
	ret->customSections = truncatedSections;
	ret->numberOfCustomSections = cnt;
	free(sections);
	return ret;
}
void deleteSection(Section s) {
	deleteWasmSection(s->id, s->section);
	free(s);
}
void freeCustomSection(CustomSection cs) {
	free(cs->name);
	free(cs->data);
	free(cs);
}
void freeTypeSection(TypeSection ts) {
	for (uint32_t i = 0; i < ts->size; i++) {
		freeFuncType(ts->types[i]);
	}
	free(ts->types);
	free(ts);
}
void freeFuncType(FuncType ft) {
	free(ft->args);
	free(ft->returns);
	free(ft);
}
void freeImportSection(ImportSection is) {
	for (uint32_t i = 0; i < is->size; i++) {
		freeImport(is->imports[i]);
	}
	free(is->imports);
	free(is);
}
void freeImport(Import import) {
	free(import->name);
	free(import->module);
	freeImportDescriptor(import->descriptor);
	free(import);
}
void freeImportDescriptor(ImportDescriptor id) {
	switch (id->type) {
		case IMPORT_TYPE:
			break;
		case IMPORT_TABLE:
			freeTable(id->table);
			break;
		case IMPORT_MEMORY:
			freeMemory(id->memory);
			break;
		case IMPORT_GLOBALTYPE:
			freeGlobaltype(id->global);
			break;
	}
	free(id);
}
void freeFunctionSection(FunctionSection fs) {
	free(fs->typeIndices);
	free(fs);
}
void freeTableSection(TableSection ts) {
	for (uint32_t i = 0; i < ts->size; i++) {
		freeTable(ts->tables[i]);
	}
	free(ts->tables);
	free(ts);
}
void freeMemorySection(MemorySection ms) {
	for (uint32_t i = 0; i < ms->size; i++) {
		freeMemory(ms->memories[i]);
	}
	free(ms->memories);
	free(ms);
}
void freeGlobalSection(GlobalSection gs) {
	for (uint32_t i = 0; i < gs->size; i++) {
		freeGlobal(gs->globals[i]);
	}
	free(gs->globals);
	free(gs);
}
void freeGlobal(Global g) {
	free(g->initExpr);
	freeGlobaltype(g->type);
	free(g);
}
void freeExportSection(ExportSection es) {
	for (uint32_t i = 0; i < es->size; i++) {
		freeExport(es->exports[i]);
	}
	free(es->exports);
	free(es);
}
void freeExport(Export e) {
	free(e->name);
	freeExportDescriptor(e->descriptor);
	free(e);
}
void freeExportDescriptor(ExportDescriptor ed) { free(ed); }
void freeStartSection(StartSection startSection) { free(startSection); }

void freeElementSection(ElementSection es) {
	for (uint32_t i = 0; i < es->size; i++) {
		freeElement(es->elements[i]);
	}
	free(es->elements);
	free(es);
}
void freeElement(Element e) {
	free(e->initExpr);
	free(e->functionIndices);
	free(e);
}
void freeCodeSection(CodeSection cs) {
	for (uint32_t i = 0; i < cs->size; i++) {
		freeCode(cs->codes[i]);
	}
	free(cs->codes);
	free(cs);
}
void freeCode(Code c) {
	freeFunction(c->func);
	free(c);
}
void freeFunction(Function f) {
	free(f->code);
	for (uint32_t j = 0; j < f->localsSize; j++) {
		free(f->locals[j]);
	}
	free(f->locals);
	free(f);
}
void freeDataSection(DataSection ds) {
	for (uint32_t i = 0; i < ds->size; i++) {
		freeData(ds->data[i]);
	}
	free(ds->data);
	free(ds);
}
void freeData(Data d) {
	free(d->offsetCode);
	free(d->init);
	free(d);
}
void freeDataCountSection(DataCountSection dcs) { free(dcs); }
void deleteWasmSection(uint8_t id, WasmSection ws) {
	switch (id) {
		case CUSTOM_SECTION:
			freeCustomSection(ws->customSection);
			break;
		case TYPE_SECTION:
			freeTypeSection(ws->typeSection);
			break;
		case IMPORT_SECTION:
			freeImportSection(ws->importSection);
			break;
		case FUNCTION_SECTION:
			freeFunctionSection(ws->functionSection);
			break;
		case TABLE_SECTION:
			freeTableSection(ws->tableSection);
			break;
		case MEMORY_SECTION:
			freeMemorySection(ws->memorySection);
			break;
		case GLOBAL_SECTION:
			freeGlobalSection(ws->globalSection);
			break;
		case EXPORT_SECTION:
			freeExportSection(ws->exportSection);
			break;
		case START_SECTION:
			freeStartSection(ws->startSection);
			break;
		case ELEMENT_SECTION:
			freeElementSection(ws->elementSection);
			break;
		case CODE_SECTION:
			freeCodeSection(ws->codeSection);
			break;
		case DATA_SECTION:
			freeDataSection(ws->dataSection);
			break;
		case DATACOUNT_SECTION:
			freeDataCountSection(ws->dataCountSection);
			break;
	}
	free(ws);
}
void deleteModule(WasmModule module) {
	for (uint32_t i = 0; i < module->numberOfCustomSections; i++) {
		freeCustomSection(module->customSections[i]);
	}
	free(module->customSections);
	TypeSection ts = module->typeSection;
	if (ts != NULL) {
		freeTypeSection(ts);
	}
	ImportSection is = module->importSection;
	if (is != NULL) {
		freeImportSection(is);
	}
	FunctionSection fs = module->functionSection;
	if (fs != NULL) {
		freeFunctionSection(fs);
	}
	TableSection ts1 = module->tableSection;
	if (ts1 != NULL) {
		freeTableSection(ts1);
	}
	MemorySection ms = module->memorySection;
	if (ms != NULL) {
		freeMemorySection(ms);
	}
	GlobalSection gs = module->globalSection;
	if (gs != NULL) {
		freeGlobalSection(gs);
	}
	ExportSection es = module->exportSection;
	if (es != NULL) {
		freeExportSection(es);
	}
	if (module->startSection != NULL)
		freeStartSection(module->startSection);
	ElementSection es1 = module->elementSection;
	if (es1 != NULL) {
		freeElementSection(es1);
	}
	CodeSection cs = module->codeSection;
	if (cs != NULL) {
		freeCodeSection(cs);
	}
	DataSection ds = module->dataSection;
	if (ds != NULL) {
		freeDataSection(ds);
	}
	free(module);
}
void freeTable(TableType tt) {
	free(tt->limit);
	free(tt);
}
void freeMemory(MemType tt) {
	free(tt->limit);
	free(tt);
}
void freeGlobaltype(GlobalType tt) { free(tt); }
DataCountSection readDataCountSection(InputStream in) {
	DataCountSection ret = calloc(1, sizeof(struct _dataCountS));
	ret->count = readUleb(in);
	return ret;
}
CustomSection readCustomSection(InputStream in, uint32_t sectionLength) {
	CustomSection ret = calloc(1, sizeof(struct _customS));
	uint64_t pos = in->pos;
	ret->name = (wchar_t *)readName(in);
	uint64_t pos2 = in->pos;
	uint64_t diff = pos2 - pos;
	ret->size = (sectionLength - diff);
	ret->data = readNBytes(in, ret->size);
	return ret;
}
TypeSection readTypeSection(InputStream in) {
	TypeSection ret = calloc(1, sizeof(struct _typeS));
	ret->size = readUleb(in);
	ret->types = calloc(ret->size, sizeof(struct _funcType));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->types[i] = readFuncType(in);
	return ret;
}
ImportSection readImportSection(InputStream in) {
	ImportSection ret = calloc(1, sizeof(struct _importS));
	ret->size = readUleb(in);
	ret->imports = calloc(ret->size, sizeof(struct _import));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->imports[i] = readImport(in);
	return ret;
}
FunctionSection readFunctionSection(InputStream in) {
	FunctionSection ret = calloc(1, sizeof(struct _functionS));
	ret->size = readUleb(in);
	ret->typeIndices = calloc(ret->size, 4);
	for (uint32_t i = 0; i < ret->size; i++)
		ret->typeIndices[i] = readUleb(in);
	return ret;
}
TableSection readTableSection(InputStream in) {
	TableSection ret = calloc(1, sizeof(struct _tableS));
	ret->size = readUleb(in);
	ret->tables = malloc(ret->size * sizeof(struct _tableType));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->tables[i] = readTable(in);
	return ret;
}
MemorySection readMemorySection(InputStream in) {
	MemorySection ret = calloc(1, sizeof(struct _memoryS));
	ret->size = readUleb(in);
	ret->memories = malloc(ret->size * sizeof(struct _memType));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->memories[i] = readMemory(in);
	return ret;
}
GlobalSection readGlobalSection(InputStream in) {
	GlobalSection ret = calloc(1, sizeof(struct _globalS));
	ret->size = readUleb(in);
	ret->globals = malloc(ret->size * sizeof(struct _global));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->globals[i] = readGlobal(in);
	return ret;
}
ExportSection readExportSection(InputStream in) {
	ExportSection ret = calloc(1, sizeof(struct _exportS));
	ret->size = readUleb(in);
	ret->exports = malloc(ret->size * sizeof(struct _export));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->exports[i] = readExport(in);
	return ret;
}
StartSection readStartSection(InputStream in) {
	StartSection ret = calloc(1, sizeof(struct _startS));
	uint32_t idx = readUleb(in);
	ret->functionIndex = idx;
	return ret;
}
ElementSection readElementSection(InputStream in) {
	ElementSection ret = calloc(1, sizeof(struct _elementS));
	ret->size = readUleb(in);
	ret->elements = malloc(ret->size * sizeof(struct _element));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->elements[i] = readElement(in);
	return ret;
}
CodeSection readCodeSection(InputStream in) {
	CodeSection ret = calloc(1, sizeof(struct _codeS));
	ret->size = readUleb(in);
	ret->codes = malloc(ret->size * sizeof(struct _code));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->codes[i] = readCode(in);
	return ret;
}
DataSection readDataSection(InputStream in) {
	DataSection ret = calloc(1, sizeof(struct _dataS));
	ret->size = readUleb(in);
	ret->data = malloc(ret->size * sizeof(struct _data));
	for (uint32_t i = 0; i < ret->size; i++)
		ret->data[i] = readData(in);
	return ret;
}
FuncType readFuncType(InputStream in) {
	FuncType ret = calloc(1, sizeof(struct _funcType));
	uint8_t magic = 0;
	readOneByte(in, &magic);
	assert(magic == FUNC_ID);
	ret->numArgs = readUleb(in);
	ret->args = readNBytes(in, ret->numArgs);
	ret->numReturns = readUleb(in);
	ret->returns = readNBytes(in, ret->numReturns);
	return ret;
}
Import readImport(InputStream in) {
	Import ret = calloc(1, sizeof(struct _import));
	ret->module = (wchar_t *)readName(in);
	ret->name = (wchar_t *)readName(in);
	ret->descriptor = readImportDescriptor(in);
	return ret;
}
TableType readTable(InputStream in) {
	TableType ret = calloc(1, sizeof(struct _tableType));
	uint8_t magic = 0;
	readOneByte(in, &magic);
	assert(magic == TABLE_ELEMTYPE);
	ret->limit = readLimit(in);
	return ret;
}
MemType readMemory(InputStream in) {
	MemType ret = calloc(1, sizeof(struct _memType));
	ret->limit = readLimit(in);
	return ret;
}
Global readGlobal(InputStream in) {
	Global ret = calloc(1, sizeof(struct _global));
	uint8_t *initExpr = malloc(32);
	uint32_t initExprLength = 0;
	while (1) {
		readOneByte(in, &initExpr[initExprLength]);
		initExprLength++;
		if (initExpr[initExprLength - 1] == 0x0b)
			break;
	}
	ret->initExpr = initExpr;
	ret->initExprLength = initExprLength;
	ret->type = readGlobalType(in);
	return ret;
}
Export readExport(InputStream in) {
	Export ret = calloc(1, sizeof(struct _export));
	ret->name = (wchar_t *)readName(in);
	ret->descriptor = readExportDescriptor(in);
	return ret;
}
Element readElement(InputStream in) {
	Element ret = calloc(1, sizeof(struct _element));
	ret->tableidx = readUleb(in);
	uint8_t *initExpr = malloc(32);
	uint32_t initExprLength = 0;
	while (1) {
		readOneByte(in, &initExpr[initExprLength]);
		initExprLength++;
		if (initExpr[initExprLength - 1] == 0x0b)
			break;
	}
	ret->initExpr = initExpr;
	ret->initExprLength = initExprLength;
	ret->size = readUleb(in);
	ret->functionIndices = calloc(ret->size, 4);
	for (uint32_t i = 0; i < ret->size; i++)
		ret->functionIndices[i] = readUleb(in);
	return ret;
}
Code readCode(InputStream in) {
	Code ret = calloc(1, sizeof(struct _code));
	ret->size = readUleb(in);
	ret->func = readFunction(in, ret->size);
	return ret;
}
Data readData(InputStream in) {
	Data ret = calloc(1, sizeof(struct _data));
	ret->memidx = readUleb(in);
	uint8_t *initExpr = malloc(32);
	uint32_t initExprLength = 0;
	while (1) {
		readOneByte(in, &initExpr[initExprLength]);
		initExprLength++;
		if (initExpr[initExprLength - 1] == 0x0b)
			break;
	}
	ret->offsetCode = initExpr;
	ret->offsetCodeLength = initExprLength;
	ret->initLength = readUleb(in);
	ret->init = readNBytes(in, ret->initLength);
	return ret;
}
ImportDescriptor readImportDescriptor(InputStream in) {
	ImportDescriptor ret = calloc(1, sizeof(struct _importDescriptor));
	readOneByte(in, &ret->type);
	switch (ret->type) {
		case IMPORT_GLOBALTYPE:
			ret->global = readGlobalType(in);
			break;
		case IMPORT_MEMORY:
			ret->memory = readMemory(in);
			break;
		case IMPORT_TABLE:
			ret->table = readTable(in);
			break;
		case IMPORT_TYPE:
			ret->typeidx = readUleb(in);
			break;
		default: {
			fprintf(stderr, "Unknown import: %d\n", ret->type);
			abort();
		}
	}
	return ret;
}
Limit readLimit(InputStream in) {
	Limit ret = calloc(1, sizeof(struct _limit));
	readOneByte(in, &ret->type);
	ret->min = readUleb(in);
	switch (ret->type) {
		case LOWER:
			ret->max = LIMIT_MAX;
			break;
		case LOWER_UPPER:
			ret->max = readUleb(in);
			if (ret->max > LIMIT_MAX) {
				fprintf(stderr, "Max in limit is too big!\n");
				abort();
			}
			break;
		default: {
			fprintf(stderr, "Unkown limit type: %d\n", ret->type);
			abort();
		}
	}
	return ret;
}
GlobalType readGlobalType(InputStream in) {
	GlobalType ret = calloc(1, sizeof(struct _globalType));
	readOneByte(in, &ret->type);
	readOneByte(in, &ret->mut);
	return ret;
}
ExportDescriptor readExportDescriptor(InputStream in) {
	ExportDescriptor ret = calloc(1, sizeof(struct _exportDescriptor));
	readOneByte(in, &ret->type);
	ret->index = readUleb(in);
	return ret;
}
Function readFunction(InputStream in, uint32_t size) {
	Function ret = calloc(1, sizeof(struct _function));
	uint64_t startPos = in->pos;
	ret->localsSize = readUleb(in);
	ret->locals = calloc(ret->localsSize, sizeof(struct _local));
	for (uint32_t i = 0; i < ret->localsSize; i++) {
		ret->locals[i] = calloc(1, sizeof(struct _local));
		readOneByte(in, &ret->locals[i]->valtype);
		ret->locals[i]->count = readUleb(in);
	}
	uint64_t endPos = in->pos;
	size -= (endPos - startPos);
	ret->codeSize = size;
	ret->code = readNBytes(in, ret->codeSize);
	return ret;
}
WasmUninterpretedModule readUninterpreted(InputStream in) {
	uint8_t *magic = readNBytes(in, 4);
	if (!(magic[0] == 0x00 && magic[1] == 0x61 && magic[2] == 0x73 &&
		  magic[3] == 0x6d))
		return NULL;
	free(magic);
	uint8_t *version = readNBytes(in, 4);
	free(version);
	WasmUninterpretedModule ret =
		calloc(1, sizeof(struct _uninterpretedModule));
	ret->sections = calloc(0, sizeof(struct _section));
	ret->count = 0;
	while (1) {
		uint8_t byte = 0;
		int byteCnt = readOneByte(in, &byte);
		if (byteCnt == 0) { // EOF
			break;
		}
		uint32_t sectionLength = readUleb(in);
		uint32_t start = in->pos;
		Section s = calloc(1, sizeof(struct _section));
		WasmSection ws = calloc(1, sizeof(union _wasmSection));
		s->id = byte;
		switch (byte) {
			case CUSTOM_SECTION:
				ws->customSection = readCustomSection(in, sectionLength);
				break;
			case TYPE_SECTION:
				ws->typeSection = readTypeSection(in);
				break;
			case IMPORT_SECTION:
				ws->importSection = readImportSection(in);
				break;
			case FUNCTION_SECTION:
				ws->functionSection = readFunctionSection(in);
				break;
			case TABLE_SECTION:
				ws->tableSection = readTableSection(in);
				break;
			case MEMORY_SECTION:
				ws->memorySection = readMemorySection(in);
				break;
			case GLOBAL_SECTION:
				ws->globalSection = readGlobalSection(in);
				break;
			case EXPORT_SECTION:
				ws->exportSection = readExportSection(in);
				break;
			case START_SECTION:
				ws->startSection = readStartSection(in);
				break;
			case ELEMENT_SECTION:
				ws->elementSection = readElementSection(in);
				break;
			case CODE_SECTION:
				ws->codeSection = readCodeSection(in);
				break;
			case DATA_SECTION:
				ws->dataSection = readDataSection(in);
				break;
			case DATACOUNT_SECTION:
				ws->dataCountSection = readDataCountSection(in);
				break;
			default: {
				return NULL;
			}
		}
		uint32_t end = in->pos;
		assert(end - start == sectionLength);
		ret->sections =
			realloc(ret->sections, (ret->count + 1) * sizeof(struct _section));
		s->section = ws;
		ret->sections[ret->count] = s;
		ret->count++;
	}
	return ret;
}
void deleteUninterpretedModule(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++)
		deleteSection(wm->sections[i]);
	free(wm->sections);
	free(wm);
}
