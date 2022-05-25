#ifndef JAB_MODULE_BUILDER_H
#define JAB_MODULE_BUILDER_H

#include "jab.h"
#include "machine_module.h"

namespace jab {

class ModuleBuilder {
public:
	ModuleBuilder(std::string);

	MachineModule* compile(CompileOptions options = {});
	
	Function* newFn(std::string, std::vector<Type>, Type, CallConv);
	BasicBlock* newBB(std::string);

	IRValue addInst(IROp, IRValue, IRValue);
	IRValue addInst(IROp, IRValue);

	IRValue none();
	IRValue iconst8();
	IRValue iconst16();
	IRValue iconst32();
	IRValue iconst64();
	IRValue fconst32();
	IRValue fconst64();

	IRValue mov(IRValue, IRValue);
	
	IRValue addi(IRValue, IRValue);
	IRValue subi(IRValue, IRValue);
	IRValue muli(IRValue, IRValue);
	IRValue divi(IRValue, IRValue);
	IRValue modi(IRValue, IRValue);
	
	IRValue addf(IRValue, IRValue);
	IRValue subf(IRValue, IRValue);
	IRValue mulf(IRValue, IRValue);
	IRValue divf(IRValue, IRValue);
	IRValue modf(IRValue, IRValue);

	IRValue lt(IRValue, IRValue);
	IRValue lte(IRValue, IRValue);
	IRValue gt(IRValue, IRValue);
	IRValue gte(IRValue, IRValue);
	IRValue eq(IRValue, IRValue);
	
	IRValue br();
	IRValue brz();
	IRValue brnz();
	IRValue call();
	IRValue ret(IRValue);

	
private:
	Module* module;
	BasicBlock* insert_point;

	i32 next_ssa();
};

} // namespace jab

#endif // JAB_MODULE_BUILDER_H
