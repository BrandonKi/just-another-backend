#include "context.h"

#include "arch/x86_64/mdf.h"
#include "register_manager.h"
#include "register_allocator.h"

#include "pretty_print.h"


// TODO use an allocator for all of this in the future

using namespace jab;

ModuleBuilder* Context::new_module_builder(std::string name) {
	return new ModuleBuilder(name);
}

JITEnv* Context::new_jit_env(ModuleBuilder* builder, CompileOptions options) {

	std::vector<byte> bin;
	if(options.target_arch == Arch::x64) {
		pretty_print(builder->module);

		auto mng = x86_64::register_manager();
		RegisterAllocator reg_alloc(mng);
		reg_alloc.alloc(builder->module->functions[0]);

		x86_64::MDIRGen mdir_gen(options, builder->module);
		mdir_gen.compile();
		bin = mdir_gen.emit_raw_bin();
	}

	return new JITEnv(bin);
}
