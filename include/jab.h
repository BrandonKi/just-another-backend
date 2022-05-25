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
class MachineModule;

enum class Arch: i8 {
	unknown,
	x64,
	aarch64
};

enum class OS: i8 {
	unknown,
	windows,
	linux,
	macos,
	freebsd,
	android,
};

enum class ObjType: i8 {
	unknown,
	coff,
	elf,
	mach
};

enum class OutputType: i8 {
	unknown,
	object_file,
	executable,
	static_lib,
	dynamic_lib
};

enum DebugSymbols {
	none,
	codeview,
	dwarf
};

inline OS get_host_os() {
	#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
	    return OS::windows;
	#elif defined(__ANDROID__)
		return OS::android;
	#elif defined(__FreeBSD__)
		return OS::freebsd;
	#elif defined(__APPLE__) || defined(__MACH__)
	    return OS::macos;
	#elif defined(__linux__)
		return OS::linux;
	#elif defined(unix) || defined(__unix) || defined(__unix__)
		return OS::linux;	// meh
	#else
	    static_assert("unsupported host os");
	#endif
}

inline Arch get_host_arch() {
	#if defined(__amd64__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_AMD64)
		return Arch::x64;
	#elif defined(_M_ARM64) || defined(__aarch64__)
		return Arch::aarch64;
	#else
		static_assert("unsupported host arch");
	#endif
}

// get host os/arch here
inline OS host_os = get_host_os();
inline Arch host_arch = get_host_arch();

inline DebugSymbols get_default_debug_symbols(OS os) {
	switch(os) {
		case OS::windows:
			return DebugSymbols::codeview;
		case OS::linux:
			return DebugSymbols::dwarf;
		case OS::macos:
			return DebugSymbols::dwarf;
		case OS::freebsd:
			return DebugSymbols::dwarf;	// will not be supported
		case OS::android:
			return DebugSymbols::dwarf;	// will not be supported
		default:
			return DebugSymbols::none;
	}
}

inline ObjType get_default_obj_type(OS os) {
	switch(os) {
		case OS::windows:
			return ObjType::coff;
		case OS::linux:
			return ObjType::elf;
		case OS::macos:
			return ObjType::mach;
		case OS::freebsd:
			return ObjType::elf; // will not be supported
		case OS::android:
			return ObjType::elf; // will not be supported
		default:
			return ObjType::unknown;
	}

}

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

struct CompileOptions {
	OptLevel opt			= OptLevel::O0;
	DebugSymbols debug		= get_default_debug_symbols(host_os);
	Arch target_arch		= host_arch;
	OS target_os			= host_os;
	ObjType obj_type		= get_default_obj_type(host_os);
	OutputType output_type	= OutputType::executable;
};

// TODO host OS and refactor targetos/arch to be used for host too

} // namespace jab

#endif // JAB_JAB_H
