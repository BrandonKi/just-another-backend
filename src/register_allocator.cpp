#include "register_allocator.h"

#include "pass_manager.h"
#include "analysis/liveness.h"

using namespace jab;

RegisterAllocator::RegisterAllocator() {

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
	for(auto& i: intervals) {
		assign_to_interval(1);
	}
}

void RegisterAllocator::assign_to_interval(TIRegister reg) {
	
}
