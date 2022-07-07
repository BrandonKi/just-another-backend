#include "jab.h"
#include "module_builder.h"
#include "jit_env.h"
#include "context.h"

#include "cprint.h"

using namespace jab;
using namespace std::literals;

#define test(x) run_test(#x, x);

std::vector<std::string> passed_tests;
std::vector<std::string> failed_tests;

void run_test(std::string name, auto test_fn) {
	using cprint::println;

	static auto pass_str = cprint::fmt("passed: ", cprint::BRIGHT_GREEN);
	static auto fail_str = cprint::fmt("failed: ", cprint::BRIGHT_RED);

	println("Running test: "s + name);
	
	if(test_fn()) {
		println(pass_str + name);
		passed_tests.push_back(name);
	}
	else {
		println(fail_str + name);
		failed_tests.push_back(name);
	}
}

void print_report() {
	using cprint::println;

	std::string failed = std::to_string(failed_tests.size());
	std::string passed = std::to_string(passed_tests.size());
	std::string total = std::to_string(failed_tests.size() + passed_tests.size());

	println();
	println(cprint::fmt("Failed: ", cprint::BRIGHT_RED) + failed);
	println(cprint::fmt("Passed: ", cprint::BRIGHT_GREEN) + passed);
	println("Total: "s + total);
}

bool exit_success() {
	Context ctx;
	ctx.options.output_dir = "temp_files/";
	ctx.options.output_name = "exit_success";

	auto* builder = ctx.new_module_builder("test");
	auto* add = builder->newFn("main", {}, Type::i32, CallConv::win64);
	auto ret = builder->iconst8(0);
	builder->ret(ret);

	auto bin = ctx.compile(builder);
	ctx.write_object_file(bin);
	ctx.link_objects();
	
	auto* jit = ctx.new_jit_env(builder);
	auto result = jit->run_function<i32(*)()>("main");
	return result == 0;
}

bool exit_fail() {
	Context ctx;
	auto* builder = ctx.new_module_builder("test");
	auto* add = builder->newFn("main", {}, Type::i32, CallConv::win64);
	auto ret = builder->iconst64(-1);
	builder->ret(ret);

	auto* jit = ctx.new_jit_env(builder);
	auto result = jit->run_function<i32(*)()>("main");
	return result == -1;
}


bool add() {
	Context ctx;
	auto* builder = ctx.new_module_builder("test");
	auto* add = builder->newFn("add", {Type::i64, Type::i64}, Type::i64, CallConv::win64);
	auto ret = builder->addi(add->param(0), add->param(1));
	builder->ret(ret);

	auto* jit = ctx.new_jit_env(builder);
	auto result = jit->run_function<i64(*)(i64, i64)>("add", 5, 6);
	return result == 11;
}

bool add_imm() {
	Context ctx;
	auto* builder = ctx.new_module_builder("test");

	auto* add_imm = builder->newFn("add_imm", {}, Type::i64, CallConv::win64);
	auto imm1 = builder->iconst64(20);
	auto imm2 = builder->iconst64(30);
	auto ret = builder->addi(imm1, imm2);
	builder->ret(ret);

	auto* jit = ctx.new_jit_env(builder);
	auto result = jit->run_function<i64(*)()>("add_imm");
	return result == 50;
}

bool add4() {
	Context ctx;
	auto* builder = ctx.new_module_builder("test");
	auto* add = builder->newFn("add4", {Type::i64, Type::i64, Type::i64, Type::i64}, Type::i64, CallConv::win64);
	auto res1 = builder->addi(add->param(0), add->param(1));
	auto res2 = builder->addi(add->param(2), add->param(3));
	auto res3 = builder->addi(res1, res2);
	builder->ret(res3);

	auto* jit = ctx.new_jit_env(builder);
	auto result = jit->run_function<i64(*)(i64, i64, i64, i64)>("add4", 12, 8, 20, 15);
	return result == 55;
}

#include "link/windows_pe.h"

int main(int argc, char* argv[]) {
/*	test(exit_success);
	test(exit_fail);
	test(add)
	test(add_imm)
	test(add4)
*/
//	link_coff_files("test", {"C:/Users/Kirin/Desktop/just-another-backend/test.o"});
	link_coff_files("test", {"C:/Users/Kirin/Desktop/just-another-backend/temp_files/test.obj"});

	print_report();
}
