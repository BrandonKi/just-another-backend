#include "register_allocator.h"

using namespace jab;

RegisterAllocator::RegisterAllocator(RegisterManager mng): mng{mng} {

}

// TODO do actual global allocation
void RegisterAllocator::alloc(Module* module) {
	for(auto* fn: module->functions)
		alloc(fn);
}

// forward pass to collect liveness information
// backward pass to allocate registers
void RegisterAllocator::alloc(Function* function) {
	auto intervals = run_analysis_pass<Liveness>(function);
	i32 arg_num = 0;
	for(auto& i: intervals) {
		if(i.start == 0) {	// if it's one of the function args
			assign_fn_arg(function, i, arg_num++);
		}
		else
			assign_to_interval(function, i);
//		expire_old_intervals();
	}
}

void RegisterAllocator::assign_to_interval(Function* fn, Interval interval) {
	assign_to_interval(fn, interval, mng.alloc_ireg());
}

// FIXME does not account for types at all
// always uses and ireg/gpr
void RegisterAllocator::assign_to_interval(Function* fn, Interval interval, MIRegister mireg) {
	auto reg = HReg{mireg};

	// start at 1 because 0 means it's a fn param
	i32 i = 1;
	for(auto* bb: fn->blocks) {
		for(auto& inst: bb->insts) {
			if(i >= interval.start && i <= interval.end) {
				if(inst.dest_is_vreg()) {
					auto num = inst.dest.vreg.num;

					if(interval.reg == num)
						inst.dest = IRValue(inst.dest.type, reg);
				}
				if(inst.src1_is_vreg()) {
					auto num = inst.src1.vreg.num;

					if(interval.reg == num)
						inst.src1 = IRValue(inst.src1.type, reg);
				}
				if(inst.src2_is_vreg()) {
					auto num = inst.src2.vreg.num;

					if(interval.reg == num)
						inst.src2 = IRValue(inst.src2.type, reg);
				}
				
			}
			++i;
		}
	}
}

//void RegisterAllocator::expire_old_intervals(std::vector<Interval> intervals) {
//}

void RegisterAllocator::assign_fn_arg(Function* fn, Interval interval, i32 arg_num) {
	auto& arg = fn->params[arg_num];
	// TODO fix this to work properly
	//	needs to query target arch and calling convention
	//	also needs to take type into account for real
	if((i32)arg.type <= (i32)Type::i64) {
		// have to add 1 here to match with calling convention stuff
		auto reg = x86_64::get_iparam(CallConv::win64, arg_num + 1);
		arg = IRValue{arg.type, HReg{reg}};
		assign_to_interval(fn, interval, reg);
	}
	else {
		assert(false);
	}
}
