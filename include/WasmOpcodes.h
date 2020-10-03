// All webassembly opcodes, given by the spec.
#ifndef __WASM_OPCODES_H
#define __WASM_OPCODES_H
#define OP_UNREACHABLE 0x00
#define OP_NOP 0x01
#define OP_BLOCK 0x02
#define OP_LOOP 0x03
#define OP_IF 0x04
#define OP_ELSE 0x05
#define OP_END 0x0B
#define OP_BR 0x0C
#define OP_BR_IF 0x0D
#define OP_BR_TABLE 0x0E
#define OP_RETURN 0x0F
#define OP_CALL 0x10
#define OP_CALL_INDIRECT 0x11
#define OP_DROP 0x1A
#define OP_SELECT 0x1B
#define OP_LOCAL_GET 0x20
#define OP_LOCAL_SET 0x21
#define OP_LOCAL_TEE 0x22
#define OP_GLOBAL_GET 0x23
#define OP_GLOBAL_SET 0x24
#define OP_I32_LOAD 0x28
#define OP_I64_LOAD 0x29
#define OP_F32_LOAD 0x2A
#define OP_F64_LOAD 0x2B
#define OP_I32_LOAD8S 0x2C
#define OP_I32_LOAD8U 0x2D
#define OP_I32_LOAD16S 0x2E
#define OP_I32_LOAD16U 0x2F
#define OP_I64_LOAD8S 0x30
#define OP_I64_LOAD8U 0x31
#define OP_I64_LOAD16S 0x32
#define OP_I64_LOAD16U 0x33
#define OP_I64_LOAD32S 0x34
#define OP_I64_LOAD32U 0x35
#define OP_I32_STORE 0x36
#define OP_I64_STORE 0x37
#define OP_F32_STORE 0x38
#define OP_F64_STORE 0x39
#define OP_I32_STORE8 0x3A
#define OP_I32_STORE16 0x3B
#define OP_I64_STORE8 0x3C
#define OP_I64_STORE16 0x3D
#define OP_I64_STORE32 0x3E
#define OP_MEMORY_SIZE 0x3F
#define OP_MEMORY_GROW 0x40
#define OP_I32_CONST 0x41
#define OP_I64_CONST 0x42
#define OP_F32_CONST 0x43
#define OP_F64_CONST 0x44
#define OP_I32_EQZ 0x45
#define OP_I32_EQ 0x46
#define OP_I32_NE 0x47
#define OP_I32_LTS 0x48
#define OP_I32_LTU 0x49
#define OP_I32_GTS 0x4A
#define OP_I32_GTU 0x4B
#define OP_I32_LES 0x4C
#define OP_I32_LEU 0x4D
#define OP_I32_GES 0x4E
#define OP_I32_GEU 0x4F
#define OP_I64_EQZ 0x50
#define OP_I64_EQ 0x51
#define OP_I64_NE 0x52
#define OP_I64_LTS 0x53
#define OP_I64_LTU 0x54
#define OP_I64_GTS 0x55
#define OP_I64_GTU 0x56
#define OP_I64_LES 0x57
#define OP_I64_LEU 0x58
#define OP_I64_GES 0x59
#define OP_I64_GEU 0x5A
#define OP_F32_EQ 0x5B
#define OP_F32_NE 0x5C
#define OP_F32_LT 0x5D
#define OP_F32_GT 0x5E
#define OP_F32_LE 0x5F
#define OP_F32_GE 0x60
#define OP_F64_EQ 0x61
#define OP_F64_NE 0x62
#define OP_F64_LT 0x63
#define OP_F64_GT 0x64
#define OP_F64_LE 0x65
#define OP_F64_GE 0x66
#define OP_I32_CLZ 0x67
#define OP_I32_CTZ 0x68
#define OP_I32_POPCNT 0x69
#define OP_I32_ADD 0x6A
#define OP_I32_SUB 0x6B
#define OP_I32_MUL 0x6C
#define OP_I32_DIVS 0x6D
#define OP_I32_DIVU 0x6E
#define OP_I32_REMS 0x6F
#define OP_I32_REMU 0x70
#define OP_I32_AND 0x71
#define OP_I32_OR 0x72
#define OP_I32_XOR 0x73
#define OP_I32_SHL 0x74
#define OP_I32_SHRS 0x75
#define OP_I32_SHRU 0x76
#define OP_I32_ROTL 0x77
#define OP_I32_ROTR 0x78
#define OP_I64_CLZ 0x79
#define OP_I64_CTZ 0x7A
#define OP_I64_POPCNT 0x7B
#define OP_I64_ADD 0x7C
#define OP_I64_SUB 0x7D
#define OP_I64_MUL 0x7E
#define OP_I64_DIVS 0x7F
#define OP_I64_DIVU 0x80
#define OP_I64_REMS 0x81
#define OP_I64_REMU 0x82
#define OP_I64_AND 0x83
#define OP_I64_OR 0x84
#define OP_I64_XOR 0x85
#define OP_I64_SHL 0x86
#define OP_I64_SHRS 0x87
#define OP_I64_SHRU 0x88
#define OP_I64_ROTL 0x89
#define OP_I64_ROTR 0x8A
#define OP_F32_ABS 0x8B
#define OP_F32_NEG 0x8C
#define OP_F32_CEIL 0x8D
#define OP_F32_FLOOR 0x8E
#define OP_F32_TRUNC 0x8F
#define OP_F32_NEAREST 0x90
#define OP_F32_SQRT 0x91
#define OP_F32_ADD 0x92
#define OP_F32_SUB 0x93
#define OP_F32_MUL 0x94
#define OP_F32_DIV 0x95
#define OP_F32_MIN 0x96
#define OP_F32_MAX 0x97
#define OP_F32_COPYSIGN 0x98
#define OP_F64_ABS 0x99
#define OP_F64_NEG 0x9A
#define OP_F64_CEIL 0x9B
#define OP_F64_FLOOR 0x9C
#define OP_F64_TRUNC 0x9D
#define OP_F64_NEAREST 0x9E
#define OP_F64_SQRT 0x9F
#define OP_F64_ADD 0xA0
#define OP_F64_SUB 0xA1
#define OP_F64_MUL 0xA2
#define OP_F64_DIV 0xA3
#define OP_F64_MIN 0xA4
#define OP_F64_MAX 0xA5
#define OP_F64_COPYSIGN 0xA6
#define OP_I32_WRAP_I64 0xA7
#define OP_I32_TRUNC_F32S 0xA8
#define OP_I32_TRUNC_F32U 0xA9
#define OP_I32_TRUNC_F64S 0xAA
#define OP_I32_TRUNC_F64U 0xAB
#define OP_I64_EXTEND_I32S 0xAC
#define OP_I64_EXTEND_I32U 0xAD
#define OP_I64_TRUNC_F32S 0xAE
#define OP_I64_TRUNC_F32U 0xAF
#define OP_I64_TRUNC_F64S 0xB0
#define OP_I64_TRUNC_F64U 0xB1
#define OP_F32_CONVERT_I32S 0xB2
#define OP_F32_CONVERT_I32U 0xB3
#define OP_F32_CONVERT_I64S 0xB4
#define OP_F32_CONVERT_I64U 0xB5
#define OP_F32_DEMOTE_F64 0xB6
#define OP_F64_CONVERT_I32S 0xB7
#define OP_F64_CONVERT_I32U 0xB8
#define OP_F64_CONVERT_I64S 0xB9
#define OP_F64_CONVERT_I64U 0xBA
#define OP_F64_PROMOTE_F32 0xBB
#define OP_I32_REINTERPRET_F32 0xBC
#define OP_I64_REINTERPRET_F64 0xBD
#define OP_F32_REINTERPRET_I32 0xBE
#define OP_F64_REINTERPRET_I64 0xBF
#define OP_I32_EXTEND8S 0xC0
#define OP_I32_EXTEND16S 0xC1
#define OP_I64_EXTEND8S 0xC2
#define OP_I64_EXTEND16S 0xC3
#define OP_I64_EXTEND32S 0xC4
#define OP_CONTINUE 0xFC
#define OP_CONT_I32_TRUNC_SAT_F32S 0x00
#define OP_CONT_I32_TRUNC_SAT_F32U 0x01
#define OP_CONT_I32_TRUNC_SAT_F64S 0x02
#define OP_CONT_I32_TRUNC_SAT_F64U 0x03
#define OP_CONT_I64_TRUNC_SAT_F32S 0x04
#define OP_CONT_I64_TRUNC_SAT_F32U 0x05
#define OP_CONT_I64_TRUNC_SAT_F64S 0x06
#define OP_CONT_I64_TRUNC_SAT_F64U 0x07
#endif
