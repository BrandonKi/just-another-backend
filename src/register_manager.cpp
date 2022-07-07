#include "register_manager.h"

#include <iostream>
#include <algorithm>

// TODO
// some way to communicate whether a register is callee/caller saved


using namespace jab;

RegisterManager::RegisterManager() {

}

i32 RegisterManager::alloc_ireg() {
	MIRegister reg;
	if(hot_iregs.empty()) {
		assert(!free_caller_iregs.empty());

		reg = free_caller_iregs.back();
		free_caller_iregs.pop_back();
	}
	else {
		reg = hot_iregs.back();
		hot_iregs.pop_back();
	}
	used_caller_iregs.push_back(reg);
	return reg;
}

void RegisterManager::alloc_ireg(MIRegister reg) {
	if(std::find(free_caller_iregs.begin(), free_caller_iregs.end(), reg) != free_caller_iregs.end()) {
		free_caller_iregs.erase(std::remove(free_caller_iregs.begin(), free_caller_iregs.end(), reg));
		used_caller_iregs.push_back(reg);
	}
	else if(std::find(free_callee_iregs.begin(), free_callee_iregs.end(), reg) != free_callee_iregs.end()) {
		free_callee_iregs.erase(std::remove(free_callee_iregs.begin(), free_callee_iregs.end(), reg));
		used_callee_iregs.push_back(reg);		
	}
	else {
		assert(false);
	}
}

void RegisterManager::free_ireg(MIRegister reg) {
	hot_iregs.push_back(reg);

	if(std::find(used_caller_iregs.begin(), used_caller_iregs.end(), reg) != used_caller_iregs.end()) {
		used_caller_iregs.erase(std::remove(used_caller_iregs.begin(), used_caller_iregs.end(), reg));
//		free_caller_iregs.push_back(reg);
	}
	else if(std::find(used_callee_iregs.begin(), used_callee_iregs.end(), reg) != used_callee_iregs.end()) {
		used_callee_iregs.erase(std::remove(used_callee_iregs.begin(), used_callee_iregs.end(), reg));
//		free_callee_iregs.push_back(reg);
	}
	else if(std::find(hot_iregs.begin(), hot_iregs.end(), reg) != hot_iregs.end()) {
		// meh
	}
	else {
		assert(false);
	}
}

void spill_ireg(MIRegister reg) {
	std::cout << "tried to spill an ireg: " << reg << "\n";
}

i32 RegisterManager::alloc_freg() {
	auto reg = free_caller_fregs.back();
	used_caller_fregs.push_back(reg);
	free_caller_fregs.pop_back();
	return reg;
}

void RegisterManager::alloc_freg(MIRegister reg) {
	auto len = free_caller_fregs.size();
	free_caller_fregs.erase(std::remove(free_caller_fregs.begin(), free_caller_fregs.end(), reg));
	used_caller_fregs.push_back(reg);
	
	if(len == free_caller_fregs.size())
		assert(false);
}

void RegisterManager::free_freg(MIRegister reg) {
	auto len = used_caller_fregs.size();
	used_caller_fregs.erase(std::remove(used_caller_fregs.begin(), used_caller_fregs.end(), reg));
	free_caller_fregs.push_back(reg);
	
	if(len == used_caller_fregs.size())
		assert(false);
}

void spill_freg(MIRegister reg) {
	std::cout << "tried to spill an freg: " << reg << "\n";
}

