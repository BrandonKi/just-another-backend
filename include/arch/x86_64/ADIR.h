#ifndef JAB_X86_64_ADIR_H
#define JAB_X86_64_ADIR_H

#include "jab.h"

enum Register: i8 {
    rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi,
    r8, r9, r10, r11, r12, r13, r14, r15,

    eax, ecx, edx, ebx, esp, ebp, esi, edi,
    r8d, r9d, r10d, r11d, r12d, r13d, r14d, r15d,

    ax, cx, dx, bx, sp, bp, si, di,
    r8w, r9w, r10w, r11w, r12w, r13w, r14w, r15w,

	// only include low regs
    al, cl, dl, bl, ah, ch, dh, bh,
    r8b, r9b, r10b, r11b, r12b, r13b, r14b, r15b,

    xmm0, xmm1, xmm2,  xmm3,  xmm4,  xmm5,  xmm6,  xmm7,
    xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15,

    ymm0, ymm1, ymm2,  ymm3,  ymm4,  ymm5,  ymm6,  ymm7,
    ymm8, ymm9, ymm10, ymm11, ymm12, ymm13, ymm14, ymm15,
};

int id(Register reg) {
	using enum Register;

	if(rax <= reg && reg <= r15)
		return reg;
	else if(eax <= reg && reg <= r15d)
		return reg - 16;
	else if(ax <= reg && reg <= r15w)
		return reg - 32;
	else if(al <= reg && reg <= r15b)
		return reg - 48;
	else if(xmm0 <= reg && reg <= xmm15)
		return reg - 64;
	else if(ymm0 <= reg && reg <= ymm15)
		return reg - 80;
	else
		assert(false);
}

int size(Register reg) {
	using enum Register;

	if(rax <= reg && reg <= r15)
		return 64;
	else if(eax <= reg && reg <= r15d)
		return 32;
	else if(ax <= reg && reg <= r15w)
		return 16;
	else if(al <= reg && reg <= r15b)
		return 8;
	else if(xmm0 <= reg && reg <= xmm15)
		return 128;
	else if(ymm0 <= reg && reg <= ymm15)
		return 256;
	else
		assert(false);
}

enum class opcode: i8 {
	mov,
	mov_reg_imm,
	mov_reg_scale,
	mov_scale_imm,
	mov_mem_imm,
	mov_index_imm,
	cmov,
	cmov_reg_imm,
	cmov_reg_scale,
	cmov_scale_imm,
	cmov_mem_imm,
	cmov_index_imm,

	add,
	add_reg_imm,
	add_reg_scale,
	add_scale_imm,
	add_mem_imm,
	add_index_imm,

	call,
	jmp,
	ret,
	
	push,
	pop,

	syscall,
	breakpoint,
	nop,
};

#endif // JAB_X86_64_ADIR_H
