#include "Wasm.h"
#include "wchar.h"
#include <stdlib.h>
CustomSection findCustomSection(WasmUninterpretedModule wm, char *name) {
	wchar_t *tmp = calloc(strlen(name) * 4, sizeof(wchar_t));
	mbstowcs(tmp, name, strlen(name));
	CustomSection cs = findCustomSectionW(wm, tmp);
	free(tmp);
	return cs;
}
CustomSection findCustomSectionW(WasmUninterpretedModule wm, wchar_t *name) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == CUSTOM_SECTION) {
			wchar_t *other = s->section->customSection->name;
			if (wcscmp(other, name) == 0)
				return s->section->customSection;
		}
	}
	return NULL;
}
TypeSection findTypeSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == TYPE_SECTION)
			return s->section->typeSection;
	}
	return NULL;
}
ImportSection findImportSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == IMPORT_SECTION)
			return s->section->importSection;
	}
	return NULL;
}
FunctionSection findFunctionSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == FUNCTION_SECTION)
			return s->section->functionSection;
	}
	return NULL;
}
TableSection findTableSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == TABLE_SECTION)
			return s->section->tableSection;
	}
	return NULL;
}
MemorySection findMemorySection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == MEMORY_SECTION)
			return s->section->memorySection;
	}
	return NULL;
}
GlobalSection findGlobalSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == GLOBAL_SECTION)
			return s->section->globalSection;
	}
	return NULL;
}
ExportSection findExportSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == EXPORT_SECTION)
			return s->section->exportSection;
	}
	return NULL;
}
StartSection findStartSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == START_SECTION)
			return s->section->startSection;
	}
	return NULL;
}
ElementSection findElementSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == ELEMENT_SECTION)
			return s->section->elementSection;
	}
	return NULL;
}
CodeSection findCodeSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == CODE_SECTION)
			return s->section->codeSection;
	}
	return NULL;
}
DataSection findDataSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == DATA_SECTION)
			return s->section->dataSection;
	}
	return NULL;
}
DataCountSection findDataCountSection(WasmUninterpretedModule wm) {
	for (uint32_t i = 0; i < wm->count; i++) {
		Section s = wm->sections[i];
		if (s->id == DATACOUNT_SECTION)
			return s->section->dataCountSection;
	}
	return NULL;
}
