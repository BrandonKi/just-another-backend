// possibly split this up into seperate files in the future
// implements:
//	 Module
//   Function
//	 BasicBlock
//	 IRInst
//	 IRValue

#include "jab.h"

using namespace jab;

// start of Module impl

Module::Module(std::string id): name{id} {

}

// start of Function impl

Function::Function(std::string name, std::vector<Type> param_types, Type ret_type, CallConv callconv):
	id{name},
	parameters{},
	ret{IRValue(ret_type)},
	callconv{callconv}
{
	for(auto t: param_types) {
		parameters.push_back(IRValue(t));
	}
}

IRValue Function::param(int index) {
	return parameters[index];
}

// start of BasicBlock impl

BasicBlock::BasicBlock(std::string name):
	id{name},
	preds{},
	params{},
	insts{}
{

}

// start of IRInst impl

IRInst::IRInst(IROp op, IRValue dest): op{op}, dest{dest} {

}

IRInst::IRInst(IROp op, i32 dest, IRValue src1, IRValue src2):
	op{op},
	dest{IRValueKind::vreg, Type::i32, dest},
	src1{src1},
	src2{src2}
{

}

IRInst::IRInst(IROp op, IRValue dest, IRValue src1, IRValue src2):
	op{op},
	dest{dest},
	src1{src1},
	src2{src2}
{

}

// start of IRValue impl

IRValue::IRValue():
	kind{IRValueKind::none},
	type{Type::none},
	vreg{}
{

}

IRValue::IRValue(Type type):
	kind{IRValueKind::vreg},
	type{type},
	vreg{}
{

}


IRValue::IRValue(IRValueKind kind, Type type, int num):
	kind{kind},
	type{type}
{
	switch(kind) {
		case IRValueKind::vreg:
			vreg = VReg(num);
			break;
		case IRValueKind::preg:
			assert(false);
			break;
		default:
			assert(false);
	}
}
