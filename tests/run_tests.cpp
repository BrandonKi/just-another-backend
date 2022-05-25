#include "jab.h"
#include "module_builder.h"
#include "machine_module.h"
#include "context.h"

using namespace jab;

bool test1() {
	Context ctx;
	auto* builder = ctx.new_module_builder("test");
	auto* add = builder->newFn("add", {Type::i32, Type::i32}, Type::i32, CallConv::win64);
	auto ret = builder->addi(add->param(0), add->param(1));
	builder->ret(ret);

	MachineModule* module = builder->compile();
	auto exit_code = module->jit();
	return exit_code;
}

int main(int argc, char* argv[]) {
	assert(test1() == 0);
}
