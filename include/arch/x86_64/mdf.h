// Machine Description File
// pretty much just a bunch of arch specific stuff at the moment
// will be refactored in the future

#ifndef JAB_X86_64_MDF_H
#define JAB_X86_64_MDF_H

#include "jab.h"
#include "register_manager.h"
#include "arch/x86_64/mdir.h"

namespace jab::x86_64 {

// TODO assumes win64 calling convention
inline RegisterManager register_manager() {
	RegisterManager rm;
	rm.free_caller_iregs = {
		rbx,
		rbp,
		rdi,
		rsi,
		r12,
		r13,
		r14,
		r15,
	};
	rm.free_callee_iregs = {
		rax,
		rcx,
		rdx,
		r8,
		r9,
		r10,
		r11,
	};

	rm.free_caller_fregs = {
		xmm6,
		xmm7,
		xmm8,
		xmm9,
		xmm10,
		xmm11,
		xmm12,
		xmm13,
		xmm14,
		xmm15
	};
	rm.free_callee_fregs = {
		xmm0,
		xmm1,
		xmm2,
		xmm3,
		xmm4,
		xmm5,
	};
	
	rm.two_address_arch = true;
	return rm;
}


// start of CallConv stuff
#define STACK -1

inline MIRegister get_iparam(CallConv callconv, MIRegister num) {
	if(callconv == CallConv::win64) {
		switch(num) {
			case 1:
				return rcx;
			case 2:
				return rdx;
			case 3:
				return r8;
			case 4:
				return r9;
			default:
				if(num >= 5)
					return STACK;
				else
					unreachable
		}
	}
	else {
		// unimplemented
		unreachable
	}
}

inline MIRegister get_fparam(CallConv callconv, MIRegister num) {
	if(callconv == CallConv::win64) {
		switch(num) {
			case 1:
				return xmm0;
			case 2:
				return xmm1;
			case 3:
				return xmm2;
			case 4:
				return xmm3;
			default:
				if(num >= 5)
					return STACK;
				else
					unreachable
		}
	}
	else {
		// unimplemented
		unreachable
	}
}

// TODO this is not correct
inline i32 get_aparam(CallConv callconv, MIRegister num) {
	return get_iparam(callconv, num);
}

inline i32 get_iret() {
	return rax;
}

inline i32 get_fret() {
	return xmm0;
}

// TODO can't return aggregates yet
// usually depends on the size of the aggregate
inline i32 get_aret() {
	return rax;
}

} // jab::x86_64

#endif // JAB_X86_64_MDF_H
