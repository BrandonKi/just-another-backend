#include "arch/x86_64/encode.h"

using namespace jab;
using namespace x86_64;

#define emit1()

Encoder::Encoder(MCModule* module): module{module} {
	// module->
}

BinaryFile Encoder::bin() {
	return {};
}

// TODO remove, this is just for debugging
std::vector<byte> Encoder::raw_bin() {
	std::vector<byte> buf;
	for(auto* fn: module->functions)
		encode_function(buf, fn);
	return buf;
}

void Encoder::encode_function(std::vector<byte>& buf, MCFunction* fn) {
	for(auto inst: fn->insts) {
		encode_inst(buf, inst);
	}
}

void Encoder::encode_inst(std::vector<byte>& buf, MCInst inst) {
	using enum Opcode;

	switch(inst.op) {
		case mov:
			encode_mov(buf, inst.reg1, inst.reg2);
		case mov_reg_imm:
			encode_mov_reg_imm(buf, inst.reg1, inst.extra.imm);
		case mov_reg_scale:
			encode_mov_reg_scale(buf);
		case mov_scale_imm:
			encode_mov_scale_imm(buf);
		case mov_mem_imm:
			encode_mov_mem_imm(buf);
		case mov_index_imm:
			encode_mov_index_imm(buf);
		case cmov:
			encode_cmov(buf, inst.reg1, inst.reg2, inst.extra.cond);

		case add:
			encode_add(buf, inst.reg1, inst.reg2);
		case add_reg_imm:
			encode_add_reg_imm(buf, inst.reg1, inst.extra.imm);
		case add_reg_scale:
			encode_add_reg_scale(buf);
		case add_scale_imm:
			encode_add_scale_imm(buf);
		case add_mem_imm:
			encode_add_mem_imm(buf);
		case add_index_imm:
			encode_add_index_imm(buf);

		case call:
			encode_call(buf);
		case jmp:
			encode_jmp(buf);
		case ret:
			encode_ret(buf);
		
		case push:
			encode_push(buf);
		case pop:
			encode_pop(buf);
		
		case syscall:
			encode_syscall(buf);
		case breakpoint:
			encode_breakpoint(buf);
		case nop:
			encode_nop(buf, 1);
		default:
			assert(false);
	}
}

void Encoder::encode_mov(
	std::vector<byte>& buf,
	Register dest,
	Register src
) {
	assert(size(dest) >= size(src));

	auto prefix = get_rex_prefix(dest, src);
	
	switch(size(dest)) {
		case 8:
			emit_if_nz<byte>(buf, prefix);
			emit<byte>(buf, 0x88);
			emit<byte>(buf, modrm(3, id(dest), id(src)));
			return;
		case 16:
			emit<byte>(buf, 0x66);
			emit_if_nz<byte>(buf, prefix);
			emit<byte>(buf, 0x89);
			emit<byte>(buf, modrm(3, id(dest), id(src)));
			return;
		case 32:
			emit_if_nz<byte>(buf, prefix);
			emit<byte>(buf, 0x89);
			emit<byte>(buf, modrm(3, id(dest), id(src)));
			return;
		case 64:
			emit<byte>(buf, rex_w | prefix);
			emit<byte>(buf, 0x89);
			emit<byte>(buf, modrm(3, id(dest), id(src)));
			return;
		case 128:
		case 256:
		default:
			assert(false);
	}
}

// TODO pick the smallest immediate encoding
void Encoder::encode_mov_reg_imm(std::vector<byte>& buf, Register dest, u64 src) {
	auto prefix = get_rex_prefix(dest);

	switch(size(dest)) {
		case 8:
			emit_if_nz<byte>(buf, prefix);
			emit<byte>(buf, 0xb0 + id(dest));
			emit<i8>(buf, src);
			return;
		case 16:
			emit<byte>(buf, 0x66);
			emit_if_nz<byte>(buf, prefix);
			emit<byte>(buf, 0xb8 + id(dest));
			emit<i16>(buf, src);
			return;
		case 32:
			emit_if_nz<byte>(buf, prefix);
			emit<byte>(buf, 0xb8 + id(dest));
			emit<i32>(buf, src);
			return;
		case 64:
			emit<byte>(buf, rex_w | prefix);
			emit<byte>(buf, 0xb8 + id(dest));
			emit<i64>(buf, src);
			return;
		case 128:
		case 256:
		default:
			assert(false);
	}
}

void Encoder::encode_mov_reg_scale(std::vector<byte>& buf) {

}

void Encoder::encode_mov_scale_imm(std::vector<byte>& buf) {

}

void Encoder::encode_mov_mem_imm(std::vector<byte>& buf) {

}

void Encoder::encode_mov_index_imm(std::vector<byte>& buf) {

}

static byte get_cmov_opcode(Condition cond) {
	using enum Condition;
	
	switch(cond) {
		case above:
			return 0x47;
		case above_equal:
			return 0x43;
		case below:
			return 0x42;
		case below_equal:
			return 0x46;
		case carry:
			return 0x42;
		case equal:
			return 0x44;
		case greater:
			return 0x4f;
		case greater_equal:
			return 0x4d;
		case lesser:
			return 0x4c;
		case lesser_equal:
			return 0x4e;
		default:
			assert(false);
	}
} 

void Encoder::encode_cmov(
	std::vector<byte>& buf,
	Register dest,
	Register src,
	Condition cond
) {

	auto prefix = get_rex_prefix(dest, src);
	auto op = get_cmov_opcode(cond);

	switch(size(dest)) {
		case 8:
			assert(false);
		case 16:
		case 32:
			emit_if_nz<byte>(buf, prefix);
			emit<byte>(buf, 0x0f);
			emit<byte>(buf, op);
			emit<byte>(buf, modrm(3, id(dest), id(src)));
			return;
		case 64:
			emit<byte>(buf, rex_w | prefix);
			emit<byte>(buf, 0x0f);
			emit<byte>(buf, op);
			emit<byte>(buf, modrm(3, id(dest), id(src)));
			return;
		case 128:
		case 256:
		default:
			assert(false);
	}

}

void Encoder::encode_add(std::vector<byte>& buf, Register dest, Register src) {
	switch(size(dest)) {
		case 8:
			return;
		case 16:
			return;
		case 32:
			return;
		case 64:
			return;
		case 128:
			return;
		case 256:
			return;
		default:
			assert(false);
	}

}

void Encoder::encode_add_reg_imm(std::vector<byte>& buf, Register dest, u64 src) {
	switch(size(dest)) {
		case 8:
			return;
		case 16:
			return;
		case 32:
			return;
		case 64:
			return;
		case 128:
			return;
		case 256:
			return;
		default:
			assert(false);
	}

}

void Encoder::encode_add_reg_scale(std::vector<byte>& buf) {

}

void Encoder::encode_add_scale_imm(std::vector<byte>& buf) {

}

void Encoder::encode_add_mem_imm(std::vector<byte>& buf) {

}

void Encoder::encode_add_index_imm(std::vector<byte>& buf) {

}


void Encoder::encode_call(std::vector<byte>& buf) {

}

void Encoder::encode_jmp(std::vector<byte>& buf) {

}

void Encoder::encode_ret(std::vector<byte>& buf) {

}


void Encoder::encode_push(std::vector<byte>& buf) {

}

void Encoder::encode_pop(std::vector<byte>& buf) {

}


void Encoder::encode_syscall(std::vector<byte>& buf) {

}

void Encoder::encode_breakpoint(std::vector<byte>& buf) {

}

void Encoder::encode_nop(std::vector<byte>& buf, u64 bytes) {

}

byte Encoder::get_rex_prefix(Register reg1) {
	return is_extended(reg1) ? rex_b : 0; 
}

byte Encoder::get_rex_prefix(Register reg1, Register reg2) {
	return get_rex_prefix(reg1) | get_rex_prefix(reg2);
}
