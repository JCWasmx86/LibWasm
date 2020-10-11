#include <stdint.h>
#include <wchar.h>
#ifndef _WASMSTRUCTS_H
#define _WASMSTRUCTS_H

#define PACKED __attribute__((__packed__))
// All types
// A valtype.
typedef enum PACKED _val {
	I32 = 0x7F,
	I64 = 0x7E,
	F32 = 0x7D,
	F64 = 0x7C
} Valtype;
// Is a global mutable?
typedef enum PACKED _mut { CONST = 0x00, VAR = 0x01 } Mutability;
// What is imported?
typedef enum PACKED _importType {
	IMPORT_TYPE = 0x00,
	IMPORT_TABLE = 0x01,
	IMPORT_MEMORY = 0x02,
	IMPORT_GLOBALTYPE = 0x03
} ImportType;
// What is exported?
typedef enum PACKED _exportType {
	EXPORT_FUNCTION = 0x00,
	EXPORT_TABLE = 0x01,
	EXPORT_MEMORY = 0x02,
	EXPORT_GLOBALTYPE = 0x03
} ExportType;
// Has this limit bounds?
typedef enum PACKED _limitBounds {
	LOWER = 0x00,	   // Just the lower bounds is given
	LOWER_UPPER = 0x01 // Lower and upper bounds are given
} LimitBound;
// Limit used by MemType and Table
typedef struct _limit {
	LimitBound type; // Describes the type of the limit
	uint32_t min;	 // Minimum value
	uint32_t max;	 // Maximum value
} * Limit;
// Associates a name with an index. Used in the name section
typedef struct _nameAssoc {
	uint32_t idx;
	wchar_t *name;
} * NameAssoc;
typedef struct _indirectNameAssoc {
	uint32_t index;
	NameAssoc *names;
	uint32_t numNames;
} * IndirectNameAssoc;
// Describes a memtype from the memory section
typedef struct _memType {
	Limit limit;
} * MemType;
// Describes a global type from the global section
typedef struct _globalType {
	Valtype type;	// What type does this global have?
	Mutability mut; // Is it mutable?
} * GlobalType;
// A global.
typedef struct _global {
	GlobalType type; // Describes the global
	uint8_t
		*initExpr; // The bytes of the initexpr (<type>.const <someValue> end)
	uint32_t initExprLength; // Length of the initexpression
} * Global;
// Describes a tabletype from the table section
typedef struct _tableType {
	Limit limit;
} * TableType;
// Further specifies an import,
typedef struct _importDescriptor {
	ImportType type;   // What is imported?
	uint32_t typeidx;  // Set if IMPORT_TYPE is specified
	TableType table;   // Set if IMPORT_TABLE is specified
	MemType memory;	   // Set if IMPORT_MEMORY is specified
	GlobalType global; // Set if IMPORT_GLOBALTYPE is specified
} * ImportDescriptor;
// Describes an import.
typedef struct _import {
	wchar_t *module; // Name of the module
	wchar_t *name;	 // Name of the imported symbol
	ImportDescriptor descriptor;
} * Import;
// Further specifies an export
typedef struct _exportDescriptor {
	ExportType type; // What is exported?
	uint32_t index;	 // Index of the exported symbol
} * ExportDescriptor;
// Describes an export
typedef struct _export {
	wchar_t *name; // Name of the exported symbol
	ExportDescriptor descriptor;
} * Export;
// Is an element from the element section
typedef struct _element {
	uint32_t tableidx;		   // For which table is this Element?
	uint8_t *initExpr;		   // Initexpression, gives the offset
	uint32_t initExprLength;   // Number of bytes in initExpr
	uint32_t *functionIndices; // Function indices
	uint32_t size;			   // Number of function indices
} * Element;
// A local variable, given in the code section
typedef struct _local {
	Valtype valtype; // Of what type is this local?
	uint32_t count;	 // How many?
} * Local;
// Describes a webassembly function.
typedef struct _function {
	Local *locals;		 // The locals
	uint32_t localsSize; // Number of Local-structs
	uint8_t *code;		 // The code in bytes
	uint32_t codeSize;	 // The number of bytes in code.
} * Function;
// Specifies a code element from the code section.
typedef struct _code {
	uint32_t size; // Size of func
	Function func;
} * Code;
// Data element
typedef struct _data {
	uint32_t memidx;		   // Which memtype is specified
	uint8_t *offsetCode;	   // Specifies the offset
	uint32_t offsetCodeLength; // Length of the offsetCode
	uint8_t *init;			   // Bytes for initializing the memory
	uint32_t initLength;	   // Number of bytes
} * Data;
// Functype that gives the signature of a function
typedef struct _funcType {
	Valtype *args;		 // The types of the arguments
	uint32_t numArgs;	 // Number of arguments
	Valtype *returns;	 // Types of return value(s)
	uint32_t numReturns; // Number of return values.
} * FuncType;
typedef struct _customS {
	wchar_t *name; // Name of the section
	uint8_t *data; // The bytes of the data
	uint32_t size; // Size of data
} * CustomSection;
typedef struct _typeS {
	FuncType *types;
	uint32_t size;
} * TypeSection;
typedef struct _importS {
	Import *imports;
	uint32_t size;
} * ImportSection;
typedef struct _functionS {
	uint32_t *typeIndices;
	uint32_t size;
} * FunctionSection;
typedef struct _tableS {
	TableType *tables;
	uint32_t size;
} * TableSection;
typedef struct _memoryS {
	MemType *memories;
	uint32_t size;
} * MemorySection;
typedef struct _globalS {
	Global *globals;
	uint32_t size;
} * GlobalSection;
typedef struct _exportS {
	Export *exports;
	uint32_t size;
} * ExportSection;
typedef struct _startS {
	uint32_t functionIndex;
} * StartSection;
typedef struct _elementS {
	Element *elements;
	uint32_t size;
} * ElementSection;
typedef struct _dataCountS {
	uint32_t count;
} * DataCountSection;
typedef struct _codeS {
	Code *codes;
	uint32_t size;
} * CodeSection;
typedef struct _dataS {
	Data *data;
	uint32_t size;
} * DataSection;
typedef struct _wasmFunc {
	FuncType signature;
	Valtype *locals;
	uint32_t localsSize;
	uint8_t *code;
	uint32_t codeSize;
} * WasmFunction;
// Describes a Webassembly-module.
typedef struct _wasmModule {
	CustomSection *customSections;
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
} * WasmModule;
typedef union _wasmSection {
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
} * WasmSection;
// An uninterpreted webassembly section
// id is one of the *_SECTION preprocessor defines
typedef struct _section {
	uint8_t id;
	WasmSection section;
} * Section;
// Describes an uninterpreted webassembly module, that preserves the order of
// the sections
typedef struct _uninterpretedModule {
	Section *sections;
	uint32_t count;
} * WasmUninterpretedModule;
#endif
