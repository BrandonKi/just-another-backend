#include "module_builder.h"

using namespace jab;

ModuleBuilder::ModuleBuilder(std::string name):
	module{new Module(name)},
	insert_point{nullptr} {

}

Function* ModuleBuilder::newFn(std::string name, std::vector<Type> parameters, Type ret, CallConv callconv) {
	auto* fn = new Function(name, parameters, ret, callconv);
	module->functions.push_back(fn);

	auto* bb = newBB(name + std::to_string(fn->blocks.size()));
	fn->blocks.push_back(bb);
	insert_point = bb;
	
	return fn;
}

BasicBlock* ModuleBuilder::newBB(std::string name) {
	auto* bb = new BasicBlock(name);
	insert_point = bb;
	return bb;
}

IRValue ModuleBuilder::addInst(IROp op, IRValue src1, IRValue src2) {
	auto inst = IRInst(op, next_ssa(), src1, src2);
	insert_point->insts.push_back(inst);
	return inst.dest;
}

IRValue ModuleBuilder::addInst(IROp op, IRValue src1) {
	auto inst = IRInst(op, next_ssa(), src1, {});
	insert_point->insts.push_back(inst);
	return inst.dest;
}

i32 ModuleBuilder::next_ssa() {
	static i32 ssa;
	return ssa++;
}

// make this no-op instead of doing nothing
IRValue ModuleBuilder::none() {
	return {};
}

IRValue ModuleBuilder::iconst8() {
	return {};
}

IRValue ModuleBuilder::iconst16() {
	return {};
}

IRValue ModuleBuilder::iconst32() {
	return {};
}

IRValue ModuleBuilder::iconst64() {
	return {};
}

IRValue ModuleBuilder::fconst32() {
	return {};
}

IRValue ModuleBuilder::fconst64() {
	return {};
}


IRValue ModuleBuilder::mov(IRValue, IRValue) {
	return {};
}


IRValue ModuleBuilder::addi(IRValue src1, IRValue src2) {
	return addInst(IROp::addi, src1, src2);
}

IRValue ModuleBuilder::subi(IRValue src1, IRValue src2) {
	return addInst(IROp::subi, src1, src2);
}

IRValue ModuleBuilder::muli(IRValue src1, IRValue src2) {
	return addInst(IROp::muli, src1, src2);
}

IRValue ModuleBuilder::divi(IRValue src1, IRValue src2) {
	return addInst(IROp::divi, src1, src2);
}

IRValue ModuleBuilder::modi(IRValue src1, IRValue src2) {
	return addInst(IROp::modi, src1, src2);
}


IRValue ModuleBuilder::addf(IRValue src1, IRValue src2) {
	return addInst(IROp::addf, src1, src2);
}

IRValue ModuleBuilder::subf(IRValue src1, IRValue src2) {
	return addInst(IROp::subf, src1, src2);
}

IRValue ModuleBuilder::mulf(IRValue src1, IRValue src2) {
	return addInst(IROp::mulf, src1, src2);
}

IRValue ModuleBuilder::divf(IRValue src1, IRValue src2) {
	return addInst(IROp::divf, src1, src2);
}

IRValue ModuleBuilder::modf(IRValue src1, IRValue src2) {
	return addInst(IROp::modf, src1, src2);
}


IRValue ModuleBuilder::lt(IRValue src1, IRValue src2) {
	return addInst(IROp::lt, src1, src2);
}

IRValue ModuleBuilder::lte(IRValue src1, IRValue src2) {
	return addInst(IROp::lte, src1, src2);
}

IRValue ModuleBuilder::gt(IRValue src1, IRValue src2) {
	return addInst(IROp::gt, src1, src2);
}

IRValue ModuleBuilder::gte(IRValue src1, IRValue src2) {
	return addInst(IROp::gte, src1, src2);
}

IRValue ModuleBuilder::eq(IRValue src1, IRValue src2) {
	return addInst(IROp::eq, src1, src2);
}


IRValue ModuleBuilder::br() {
	return {};
}

IRValue ModuleBuilder::brz() {
	return {};
}

IRValue ModuleBuilder::brnz() {
	return {};
}

IRValue ModuleBuilder::call() {
	return {};
}

IRValue ModuleBuilder::ret(IRValue src) {
	return addInst(IROp::ret, src);
}
