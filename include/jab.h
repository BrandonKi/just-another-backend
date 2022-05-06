#ifndef JAB_JAB_H
#define JAB_JAB_H

#include <cstdint>
#include <vector>
#include <string>

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

enum CallConv {
	win64,
	sysv64
};

enum TargetArch {
	x64,
	aarch64
};

enum TargetOS {
	windows,
	linux,
	macos
};

enum IROp {

};

enum IRValueKind {
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
	union {
		VReg vreg;
		PReg preg;
	};
};

struct IRInst {
	IROp op;
	IRValue dest;
	IRValue src1;
	IRValue src2;
};

struct BasicBlock {
	std::string id;
	std::vector<BasicBlock*> preds;
	std::vector<IRInst> insts;
};

struct IRFunction {
	std::string id;
	std::vector<BasicBlock*> blocks; 
};

struct IRModule {
	std::string name;
	std::vector<IRFunction*> blocks; 
};

enum OptLevel {
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
