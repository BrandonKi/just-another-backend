#include "jab.h"
#include "module_builder.h"
#include "jit_env.h"
#include "context.h"

using namespace jab;

bool test1() {
	Context ctx;
	auto* builder = ctx.new_module_builder("test");
	auto* add = builder->newFn("add", {Type::i64, Type::i64}, Type::i64, CallConv::win64);
	auto ret = builder->addi(add->param(0), add->param(1));
	builder->ret(ret);

	auto* jit = ctx.new_jit_env(builder);
	auto result = jit->run_main();
	return result == 3;
}

int main(int argc, char* argv[]) {
	assert(test1() == 0);
}
