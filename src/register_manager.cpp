#include "register_manager.h"

#include <iostream>
#include <algorithm>

using namespace jab;

RegisterManager::RegisterManager() {

}

i32 RegisterManager::alloc_ireg() {
	auto reg = free_caller_iregs.back();
	used_caller_iregs.push_back(reg);
	free_caller_iregs.pop_back();
	return reg;
}

void RegisterManager::alloc_ireg(i32 reg) {
	auto len = free_caller_iregs.size();
	free_caller_iregs.erase(std::remove(free_caller_iregs.begin(), free_caller_iregs.end(), reg));
	used_caller_iregs.push_back(reg);
	
	if(len == free_caller_iregs.size())
		assert(false);
}


void RegisterManager::free_ireg(i32 reg) {
	auto len = used_caller_iregs.size();
	used_caller_iregs.erase(std::remove(used_caller_iregs.begin(), used_caller_iregs.end(), reg));
	free_caller_iregs.push_back(reg);
	
	if(len == used_caller_iregs.size())
		assert(false);
}

void spill_ireg(i32 reg) {
	std::cout << "tried to spill an ireg: " << reg << "\n";
}

i32 RegisterManager::alloc_freg() {
	auto reg = free_caller_fregs.back();
	used_caller_fregs.push_back(reg);
	free_caller_fregs.pop_back();
	return reg;
}

void RegisterManager::alloc_freg(i32 reg) {
	auto len = free_caller_fregs.size();
	free_caller_fregs.erase(std::remove(free_caller_fregs.begin(), free_caller_fregs.end(), reg));
	used_caller_fregs.push_back(reg);
	
	if(len == free_caller_fregs.size())
		assert(false);
}

void RegisterManager::free_freg(i32 reg) {
	auto len = used_caller_fregs.size();
	used_caller_fregs.erase(std::remove(used_caller_fregs.begin(), used_caller_fregs.end(), reg));
	free_caller_fregs.push_back(reg);
	
	if(len == used_caller_fregs.size())
		assert(false);
}

void spill_freg(i32 reg) {
	std::cout << "tried to spill an freg: " << reg << "\n";
}

