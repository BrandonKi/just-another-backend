// Machine Description File
// pretty much just a bunch of arch specific stuff at the moment
// will be refactored in the future

#ifndef JAB_X86_64_MDF_H
#define JAB_X86_64_MDF_H

namespace jab::x86_64 {

// TODO assumes win64 calling convention
RegisterManager register_manager() {
	RegisterManager rm;
	rm.caller_saved_iregs = {
		rbx,
		rbp,
		rdi,
		rsi,
		r12,
		r13,
		r14,
		r15,
	};
	rm.callee_saved_iregs = {
		rax,
		rcx,
		rdx,
		r8,
		r9,
		r10,
		r11,
	};

	rm.caller_saved_fregs = {
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
	rm.callee_saved_fregs = {
		xmm0,
		xmm1,
		xmm2,
		xmm3,
		xmm4,
		xmm5,
	};
	
	rm.two_address_arch = true;
	
}


// start of CallConv stuff
#define STACK -1

i32 get_iparam(CallConv callconv, i32 num) {
	if(callconv == CallConc::win64) {
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
					assert(false);
		}
	}
	else {
		// unimplemented
		assert(false);
	}
}

i32 get_fparam(CallConv callconv, i32 num) {
	if(callconv == CallConc::win64) {
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
					assert(false);
		}
	}
	else {
		// unimplemented
		assert(false);
	}
}

// TODO this is not correct
i32 get_aparam(CallConv callconv, i32 num) {
	get_iparam(callconv, num);
}

i32 get_iret() {
	return rax;
}

i32 get_fret() {
	return xmm0;
}

// TODO can't return aggregates yet
// usually depends on the size of the aggregate
i32 get_aret() {
	return rax;
}

} // jab::x86_64

#endif // JAB_X86_64_MDF_H
