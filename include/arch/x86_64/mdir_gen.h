#ifndef JAB_X86_64_MDIR_GEN_H
#define JAB_X86_64_MDIR_GEN_H

#include "jab.h"
#include "arch/x86_64/mdir.h"
#include "arch/x86_64/encode.h"

namespace jab::x86_64 {

// TODO maybe move this stuff to a better spot?
enum class MCValueKind: i8 {
	none,
	reg,
	mem,
	imm,
};

struct MCValue {
	MCValueKind kind;
	Type type;
	union {
	    Register reg;
		u64 imm;
	};
};

struct MCInst {
	Opcode op;
	Register reg1;
	Register reg2;

	union {
		Register reg3;
		u64 imm;
		struct {
			// TODO stuff for 
		} scale;
	} extra;
};

struct MCFunction {
	std::string id;
	std::vector<MCValue> params;
	MCValue ret;
	CallConv callconv;
	std::vector<MCInst> insts;

	MCFunction(Function* fn): id{fn->id}, params{}, ret{}, callconv{fn->callconv} {
		using enum MCValueKind;
		// TODO get register depending on calling convention
		// TODO if dealing with PRegs then take the reg from that
		// TODO associate each vreg with it's physical counterpart
		// TODO not sure what to do with the type field here or if should even exist
		for(auto param: fn->params) {
			params.push_back({
				.kind = reg,
				.type = param.type,
				.reg = Register::rax});
		}
		ret = {
			.kind = reg,
			.type = fn->ret.type,
			.reg = Register::rax};
	}

	MCValue param(int);
};

struct MCModule {
	std::string name;
	// TODO need a symtab of some sort
	// TODO also need storage:
	//     * data
	//     * thread local
	std::vector<MCFunction*> functions;

	MCModule(std::string id): name{id} {}
};
// end of stuff to move

class MDIRGen {
public:
	MDIRGen(CompileOptions, Module*);

	void compile();
	
	std::vector<std::byte> emit_raw_bin();

private:
	CompileOptions options;
	Module* module;
	MCModule* machine_module;

	MCModule* gen_module();
	MCFunction* gen_function(Function*);
	void gen_inst(MCFunction*, IRInst);
	void gen_imm(MCFunction*, IRInst);
	void gen_mov(MCFunction*, IRInst);
	void gen_bin(MCFunction*, IRInst);
	void gen_branch(MCFunction*, IRInst);
	void gen_call(MCFunction*, IRInst);
	void gen_ret(MCFunction*, IRInst);

	void append_inst(MCFunction*, MCInst);
};

} // namespace jab::x86_64

#endif // JAB_X86_64_MDIR_GEN_H
