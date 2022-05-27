#include "arch/x86_64/mdir_gen.h"

using namespace jab;
using namespace x86_64;

MDIRGen::MDIRGen(Module* module): module{module} {

}

std::vector<std::byte> MDIRGen::compile() {
	return {};
	// return gen_module();
}

// MCModule* MDIRGen::gen_module() {
// 	MachineModule* mm = new MachineModule(module->name);
// 	for(auto* fn: module->functions) {
// 		mm->functions.push_back(gen_function(fn));
// 	}
// 	return mm;
// }

// MCFunction* gen_function(Function* fn) {
// 	for()
// }
