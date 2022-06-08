#ifndef JAB_JAB_H
#define JAB_JAB_H

#include <cstdint>
#include <vector>
#include <string>
#include <cassert>
#include <cstddef>

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

using byte = u8;

namespace jab {


class ModuleBuilder;

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

enum class DebugSymbols: i8 {
	none,
	codeview,
	dwarf
};

constexpr OS get_host_os() {
	#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
		#define OS_WINDOWS
	    return OS::windows;
	#elif defined(__ANDROID__)
		#define OS_ANDROID
		return OS::android;
	#elif defined(__FreeBSD__)
		#define OS_FREEBSD
		return OS::freebsd;
	#elif defined(__APPLE__) || defined(__MACH__)
	    #define OS_MACOS
		return OS::macos;
	#elif defined(__linux__)
	    #define OS_LINUX
		return OS::linux;
	#elif defined(unix) || defined(__unix) || defined(__unix__)
	    #define OS_LINUX
		return OS::linux;	// meh
	#else
	    assert("unsupported host os");
	#endif
}

constexpr Arch get_host_arch() {
	#if defined(__amd64__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_AMD64)
		#define ARCH_X64
		return Arch::x64;
	#elif defined(_M_ARM64) || defined(__aarch64__)
		#define ARCH_AARCH64
		return Arch::aarch64;
	#else
		assert("unsupported host arch");
	#endif
}

// get host os/arch here
constexpr OS host_os = get_host_os();
constexpr Arch host_arch = get_host_arch();

inline DebugSymbols get_default_debug_symbols(OS os) {
	switch(os) {
		case OS::windows:
			return DebugSymbols::codeview;
		case OS::linux:
			return DebugSymbols::dwarf;
		case OS::macos:
			return DebugSymbols::dwarf;
		case OS::freebsd:				// will not be supported
			return DebugSymbols::dwarf;
		case OS::android:				// will not be supported
			return DebugSymbols::dwarf;
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
	none,
	win64,
	sysv64
};

enum class Linkage: i8 {
	none,
	interal,
	external,
};

struct Symbol {
	std::string name;
};

enum class RelocType {
	none,
	addr32,
	addr64,
	
	rel32,
	rel32_1,
	rel32_2,
	rel32_3,
	rel32_4,
	rel32_5,
	
};

struct Reloc {
	u64 virtual_address;
	u64 symtab_index;
	RelocType type;
};

struct Section {
	std::string name;

	u64 virtual_size;
	u64 virtual_address;

	std::vector<Reloc> relocs;
	std::vector<byte> bin;
};

struct BinaryFile {
	std::string name;
	std::vector<Symbol> symbols;
	std::vector<Section> sections;
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
	preg,
	imm
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
		u64 imm;
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
	std::vector<IRValue> params;
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

inline bool is_imm(IROp op) {
	return (i64)op >= (i64)IROp::iconst8 && (i64)op <= (i64)IROp::fconst64;
}

inline bool is_mov(IROp op) {
	return op == IROp::mov;
}

inline bool is_bin(IROp op) {
	return (i64)op >= (i64)IROp::addi && (i64)op <= (i64)IROp::eq;
}

inline bool is_branch(IROp op) {
	return (i64)op >= (i64)IROp::br && (i64)op <= (i64)IROp::brnz;
}

inline bool is_call(IROp op) {
	return op == IROp::call;
}

inline bool is_ret(IROp op) {
	return op == IROp::ret;
}

} // namespace jab

#endif // JAB_JAB_H
