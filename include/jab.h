#ifndef JAB_JAB_H
#define JAB_JAB_H

#include <cstdint>
#include <vector>
#include <string>
#include <cassert>

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;

namespace jab {

class ModuleBuilder;

enum class Type: i8 {
	none,
	i8,
	i16,
	i32,
	i64
};

enum class CallConv: i8 {
	win64,
	sysv64
};

enum class TargetArch: i8 {
	x64,
	aarch64
};

enum class TargetOS: i8 {
	windows,
	linux,
	macos
};

enum class ObjFileType: i8 {
	coff,
	elf,
	mach
};

enum class OutputType: i8 {
	object_file,
	executable,
	static_lib,
	dynamic_lib
};

enum class IROp: i8 {
	none,
	iconst8,
	iconst16,
	iconst32,
	iconst64,
	fconst32,
	fconst64,

	mov,
	
	addi,
	subi,
	muli,
	divi,
	modi,
	
	addf,
	subf,
	mulf,
	divf,
	modf,

	lt,
	lte,
	gt,
	gte,
	eq,
	
	br,
	brz,
	brnz,
	call,
	ret,
};

enum class IRValueKind: i8 {
	none,
	vreg,
	preg
};

struct VReg {
	i32 num;
};

struct PReg {
	
};

struct IRValue {
	IRValueKind kind;
	Type type;
	union {
		VReg vreg;
		PReg preg;
	};

	IRValue();
	IRValue(Type);
	IRValue(IRValueKind, Type, int);
};

struct IRInst {
	IROp op;
	IRValue dest;
	IRValue src1;
	IRValue src2;

	IRInst(IROp, IRValue);
	IRInst(IROp, IRValue, IRValue, IRValue);
	IRInst(IROp, i32, IRValue, IRValue);
};

struct BasicBlock {
	std::string id;
	std::vector<BasicBlock*> preds;
	std::vector<IRValue> params;
	std::vector<IRInst> insts;

	BasicBlock(std::string);
};

struct Function {
	std::string id;
	std::vector<IRValue> parameters;
	IRValue ret;
	CallConv callconv;
	std::vector<BasicBlock*> blocks;

	Function(std::string, std::vector<Type>, Type, CallConv);

	IRValue param(int);
};

struct Module {
	std::string name;
	std::vector<Function*> functions; 

	Module(std::string);
};

enum class OptLevel: i8 {
	O0,
	O1,
	O2,
	Os
};

enum DebugSymbols {
	codeview,
	dwarf
};

struct CompileOptions {
	OptLevel opt;
	DebugSymbols debug;
};

} // namespace jab

#endif // JAB_JAB_H
