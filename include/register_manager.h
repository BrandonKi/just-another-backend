// Cross-platform register manager

#ifndef JAB_REGISTER_MANAGER_H
#define JAB_REGISTER_MANAGER_H

#include "jab.h"

namespace jab {

	class RegisterManager {
	public:
		RegisterManager();

		i32 alloc_ireg();
		void alloc_ireg(MIRegister);
		void free_ireg(MIRegister);
		void spill_ireg(MIRegister);
		
		i32 alloc_freg();
		void alloc_freg(MIRegister);
		void free_freg(MIRegister);
		void spill_freg(MIRegister);
		
		// ints
		std::vector<MIRegister> free_caller_iregs;
		std::vector<MIRegister> free_callee_iregs;
		std::vector<MIRegister> used_caller_iregs;
		std::vector<MIRegister> used_callee_iregs;

		std::vector<MIRegister> hot_iregs;
		
		// floats
		std::vector<MIRegister> free_caller_fregs;
		std::vector<MIRegister> free_callee_fregs;
		std::vector<MIRegister> used_caller_fregs;
		std::vector<MIRegister> used_callee_fregs;

		std::vector<MIRegister> hot_fregs;
				
		// for ex. x86
		bool two_address_arch;
	};

} // jab

#endif // JAB_REGISTER_MANAGER_H
