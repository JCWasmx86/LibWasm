#include <wchar.h>
#include <stdint.h>
#ifndef _WASMSTRUCTS_H
#define _WASMSTRUCTS_H
//All types
#define PACKED __attribute__((__packed__))
typedef enum PACKED _val{
	I32=0x7F,
	I64=0x7E,
	F32=0x7D,
	F64=0x7C
}Valtype;
//Is a global mutable?
typedef enum PACKED _mut{
	CONST=0x00,
	VAR=0x01
}Mutability;
//What is imported?
typedef enum PACKED _importType{
	IMPORT_TYPE=0x00,
	IMPORT_TABLE=0x01,
	IMPORT_MEMORY=0x02,
	IMPORT_GLOBALTYPE=0x03
}ImportType;
//What is exported?
typedef enum PACKED _exportType{
	EXPORT_FUNCTION=0x00,
	EXPORT_TABLE=0x01,
	EXPORT_MEMORY=0x02,
	EXPORT_GLOBALTYPE=0x03
}ExportType;
//Has this limit bounds?
typedef enum PACKED _limitBounds{
	LOWER=0x00,
	LOWER_UPPER=0x01
}LimitBound;
//Limit used by MemType and Table
typedef struct _limit{
	uint8_t type;
	uint32_t min;
	uint32_t max;
}*Limit;
typedef struct _nameAssoc{
	uint32_t idx;
	wchar_t* name;
}*NameAssoc;
typedef struct _indirectNameAssoc{
	uint32_t index;
	NameAssoc* names;
	uint32_t numNames;
}*IndirectNameAssoc;
typedef struct _memType{
	Limit limit;
}*MemType;
typedef struct _globalType{
	Valtype type;
	Mutability mut;
}*GlobalType;
typedef struct _global{
	GlobalType type;
	uint8_t *initExpr;
	uint32_t initExprLength;
}*Global;
typedef struct _tableType{
	Limit limit;
}*TableType;
typedef struct _importDescriptor{
	ImportType type;
	uint32_t typeidx;
	TableType table;
	MemType memory;
	GlobalType global;
}*ImportDescriptor;
typedef struct _import{
	wchar_t* module;
	wchar_t* name;
	ImportDescriptor descriptor;
}*Import;
typedef struct _exportDescriptor{
	ExportType type;
	uint32_t index;
}*ExportDescriptor;
typedef struct _export{
	wchar_t* name;
	ExportDescriptor descriptor;
}*Export;
typedef struct _element{
	uint32_t tableidx;
	uint8_t *initExpr;
	uint32_t initExprLength;
	uint32_t *functionIndices;
	uint32_t size;
}*Element;
typedef struct _local{
	Valtype valtype;
	uint32_t count;
}*Local;
typedef struct _function{
	Local* locals;
	uint32_t localsSize;
	uint8_t *code;
	uint32_t codeSize;
}*Function;
typedef struct _code{
	uint32_t size;
	Function func;
}*Code;
typedef struct _data{
	uint32_t memidx;
	uint8_t* offsetCode;
	uint32_t offsetCodeLength;
	uint8_t* init;
	uint32_t initLength;
}*Data;
typedef struct _funcType{
	Valtype *args;
	uint32_t numArgs;
	Valtype *returns;
	uint32_t numReturns;
}*FuncType;
typedef struct _customS{
	wchar_t* name;
	uint8_t* data;
	uint32_t size;
}*CustomSection;
typedef struct _typeS{
	FuncType* types;
	uint32_t size;
}*TypeSection;
typedef struct _importS{
	Import* imports;
	uint32_t size;
}*ImportSection;
typedef struct _functionS{
	uint32_t *typeIndices;
	uint32_t size;
}*FunctionSection;
typedef struct _tableS{
	TableType* tables;
	uint32_t size;
}*TableSection;
typedef struct _memoryS{
	MemType* memories;
	uint32_t size;
}*MemorySection;
typedef struct _globalS{
	Global* globals;
	uint32_t size;
}*GlobalSection;
typedef struct _exportS{
	Export* exports;
	uint32_t size;
}*ExportSection;
typedef struct _startS{
	uint32_t functionIndex;
}*StartSection;
typedef struct _elementS{
	Element* elements;
	uint32_t size;
}*ElementSection;
typedef struct _dataCountS{
	uint32_t count;
}*DataCountSection;
typedef struct _codeS{
	Code* codes;
	uint32_t size;
}*CodeSection;
typedef struct _dataS{
	Data* data;
	uint32_t size;
}*DataSection;
typedef struct _wasmFunc{
	FuncType signature;
	Valtype* locals;
	uint32_t localsSize;
	uint8_t* code;
	uint32_t codeSize;
}*WasmFunction;
typedef struct _wasmModule{
	CustomSection* customSections;
	uint32_t numberOfCustomSections;
	TypeSection typeSection;
	ImportSection importSection;
	FunctionSection functionSection;
	TableSection tableSection;
	MemorySection memorySection;
	GlobalSection globalSection;
	ExportSection exportSection;
	StartSection startSection;
	ElementSection elementSection;
	DataCountSection dataCountSection;
	CodeSection codeSection;
	DataSection dataSection;
}*WasmModule;
typedef union _wasmSection{
	CustomSection customSection;
	TypeSection typeSection;
	ImportSection importSection;
	FunctionSection functionSection;
	TableSection tableSection;
	MemorySection memorySection;
	GlobalSection globalSection;
	ExportSection exportSection;
	StartSection startSection;
	ElementSection elementSection;
	DataCountSection dataCountSection;
	CodeSection codeSection;
	DataSection dataSection;
}*WasmSection;
typedef struct _section{
	uint8_t id;
	WasmSection section;
}*Section;
typedef struct _uninterpretedModule{
	Section* sections;
	uint32_t count;
}*WasmUninterpretedModule;
#endif
