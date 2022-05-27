#ifndef JAB_X86_64_MDIR_GEN_H
#define JAB_X86_64_MDIR_GEN_H

#include "jab.h"

namespace jab::x86_64 {

//TODO maybe move this stuff to a better spot?
enum MCValue {
	none,
	reg,
	mem,
	imm,
};

struct MCInst {

};

struct MCFunction {
	std::string id;
	std::vector<MCValue> parameters;
	MCValue ret;
	CallConv callconv;
	std::vector<MCInst> insts;

	MCFunction(std::string, std::vector<Type>, Type, CallConv);

	MCValue param(int);
};

struct MCModule {
	std::string name;
	// TODO need a symtab of some sort
	// TODO also need storage:
	//     * thread local
	//     * data
	std::vector<MCFunction*> functions;

	MCModule(std::string id): name{id} {}
};
// end of stuff to move

class MDIRGen {
public:
	MDIRGen(Module*);

	std::vector<std::byte> compile();

private:
	Module* module;

};

} // namespace jab::x86_64

#endif // JAB_X86_64_MDIR_GEN_H
