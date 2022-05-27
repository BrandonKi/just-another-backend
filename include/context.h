#ifndef JAB_CONTEXT_H
#define JAB_CONTEXT_H

#include "module_builder.h"
#include "jit_env.h"
#include "arch/x86_64/mdir_gen.h"

namespace jab {

class Context {
public:
	Context(): options{} {}
	Context(CompileOptions options): options{options} {}

	ModuleBuilder* new_module_builder(std::string);
	JITEnv* new_jit_env(ModuleBuilder*, CompileOptions = {});

private:
	CompileOptions options;
};

} // namespace jab

#endif // JAB_CONTEXT_H
