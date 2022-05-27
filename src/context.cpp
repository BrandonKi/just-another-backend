#include "context.h"

// TODO use an allocator for all of this in the future

using namespace jab;

ModuleBuilder* Context::new_module_builder(std::string name) {
	return new ModuleBuilder(name);
}

JITEnv* Context::new_jit_env(ModuleBuilder* builder, CompileOptions options) {

	std::vector<std::byte> bin;
	if(options.target_arch == Arch::x64) {
		x86_64::MDIRGen mdir_gen(builder->module);
		bin = mdir_gen.compile();
	}

	return new JITEnv(bin);
}
