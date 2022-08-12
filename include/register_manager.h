// Cross-platform register manager

#ifndef JAB_REGISTER_MANAGER_H
#define JAB_REGISTER_MANAGER_H

#include "jab.h"

namespace jab {

	class RegisterManager {
	public:
		RegisterManager();

		MIRegister alloc_gpr();
		void alloc_gpr(MIRegister);
		void free_gpr(MIRegister);
		void spill_gpr(MIRegister);

		MIRegister alloc_fpr();
		void alloc_fpr(MIRegister);
		void free_fpr(MIRegister);
		void spill_fpr(MIRegister);

		std::vector<MIRegister> free_caller_gprs;
		std::vector<MIRegister> free_callee_gprs;
		std::vector<MIRegister> used_caller_gprs;
		std::vector<MIRegister> used_callee_gprs;

		std::vector<MIRegister> free_caller_fprs;
		std::vector<MIRegister> free_callee_fprs;
		std::vector<MIRegister> used_caller_fprs;
		std::vector<MIRegister> used_callee_fprs;

		caller_gpr_mask
		callee_gpr_mask
	};


	class RegisterManager {
		std::vector<MIRegister> hot_iregs;
		
		std::vector<MIRegister> free_caller_fregs;
		std::vector<MIRegister> free_callee_fregs;
		std::vector<MIRegister> used_caller_fregs;
		std::vector<MIRegister> used_callee_fregs;

		std::vector<MIRegister> hot_fregs;
				
		bool two_address_arch;
	};

} // jab

#endif // JAB_REGISTER_MANAGER_H
