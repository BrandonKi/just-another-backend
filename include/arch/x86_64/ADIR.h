#ifndef JAB_X86_64_ADIR_H
#define JAB_X86_64_ADIR_H

enum class opcode: i8 {
	mov,
	cmov,

	add,
	add_reg_imm,
	add_reg_scale,
	add_scale_imm,
	add_mem_imm,
	add_index_imm,
}

#endif // JAB_X86_64_ADIR_H
