#include "jab.h"
#include "module_builder.h"

using namespace jab;

bool test1() {
	ModuleBuilder builder("test1");
	auto* add = builder.newFn("add", {Type::i32, Type::i32}, Type::i32, CallConv::win64);
	auto ret = builder.addi(add->param(0), add->param(1));
	builder.ret(ret);
	
	return true;
}


int main(int argc, char* argv[]) {
	test1();


}
