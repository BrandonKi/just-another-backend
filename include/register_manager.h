// Cross-platform register manager

#ifndef JAB_REGISTER_MANAGER_H
#define JAB_REGISTER_MANAGER_H

#include "jab.h"

namespace jab {

	class RegisterManager {
	public:
		RegisterManager();

		i32 alloc_ireg();
		void alloc_ireg(i32);
		void free_ireg(i32);
		void spill_ireg(i32);
		
		i32 alloc_freg();
		void alloc_freg(i32);
		void free_freg(i32);
		void spill_freg(i32);
		
		// ints
		std::vector<i32> free_caller_iregs;
		std::vector<i32> free_callee_iregs;
		std::vector<i32> used_caller_iregs;
		// floats
		std::vector<i32> free_caller_fregs;
		std::vector<i32> free_callee_fregs;
		std::vector<i32> used_caller_fregs;
		
		// for ex. x86
		bool two_address_arch;
	};

} // jab

#endif // JAB_REGISTER_MANAGER_H
