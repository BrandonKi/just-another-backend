#ifndef JAB_X86_64_ENCODE_H
#define JAB_X86_64_ENCODE_H

#include "jab.h"
#include "arch/x86_64/mdir.h"
#include "arch/x86_64/mdir_gen.h"

namespace jab::x86_64 {

constexpr byte rex(bool w, bool r, bool x, bool b) {
    return 0b1000000 | (w << 3) | (r << 2) | (x << 1) | int(b);
}

constexpr byte modrm(byte mod, byte rm, byte reg) {
    return (mod << 6) | (reg << 3) | rm;
}

constexpr byte sib(byte scale, byte index, byte base) {
    return (scale << 6) | (index << 3) | base;
}

constexpr byte rex_w = rex(1, 0, 0, 0);
constexpr byte rex_r = rex(0, 1, 0, 0);
constexpr byte rex_x = rex(0, 0, 1, 0);
constexpr byte rex_b = rex(0, 0, 0, 1);

class Encoder {
public:
	Encoder(MCModule*);

	BinaryFile bin();
	// just for debug purposes at the moment
	std::vector<byte> raw_bin();

private:
	MCModule* module;

	void encode_function(std::vector<byte>&, MCFunction*);
	void encode_inst(std::vector<byte>&, MCInst);

	void encode_mov(std::vector<byte>&, Register, Register);
	void encode_mov_reg_imm(std::vector<byte>&, Register, u64);
	void encode_mov_reg_scale(std::vector<byte>&);
	void encode_mov_scale_imm(std::vector<byte>&);
	void encode_mov_mem_imm(std::vector<byte>&);
	void encode_mov_index_imm(std::vector<byte>&);

	void encode_cmov(std::vector<byte>&, Register, Register, Condition);

	void encode_add(std::vector<byte>&, Register, Register);
	void encode_add_reg_imm(std::vector<byte>&, Register, u64);
	void encode_add_reg_scale(std::vector<byte>&);
	void encode_add_scale_imm(std::vector<byte>&);
	void encode_add_mem_imm(std::vector<byte>&);
	void encode_add_index_imm(std::vector<byte>&);

	void encode_call(std::vector<byte>&);
	void encode_jmp(std::vector<byte>&);
	void encode_ret(std::vector<byte>&);
		
	void encode_push(std::vector<byte>&);
	void encode_pop(std::vector<byte>&);
		
	void encode_syscall(std::vector<byte>&);
	void encode_breakpoint(std::vector<byte>&);
	void encode_nop(std::vector<byte>&, u64);

	byte get_rex_prefix(Register);
	byte get_rex_prefix(Register, Register);
	
    template <typename T>
    requires requires(T a) {
        { std::is_integral_v<T> };
        { std::is_pointer_v<T> };
        { std::is_floating_point_v<T> };
    }
    inline void emit(std::vector<byte>& buf, const T val_) {

        using U =
            std::conditional_t<std::is_same_v<T, bool>,
                uint8_t,
                std::conditional_t<std::is_pointer_v<T>,
                    uintptr_t,
                    T>>;

        U val;
        if constexpr (std::is_pointer_v<T>)
            val = reinterpret_cast<U>(val_);
        else
            val = static_cast<U>(val_);

        using type =
            std::conditional_t<std::is_signed_v<U>,
                std::conditional_t<std::is_floating_point_v<U>,
                    std::conditional_t<std::is_same_v<float, U> && sizeof(float) == 4,
                        uint32_t,
                        std::conditional_t<std::is_same_v<double, U> && sizeof(double) == 8,
                            uint64_t,
                            void>>,
                U>,
            U>;

        auto raw_val = std::bit_cast<type>(val);
        for (size_t i = 0; i < sizeof(type); ++i)
            buf.push_back(byte((raw_val >> (i * 8)) & 0xff));
    }

    template <typename T>
    requires requires(T a) {
        { std::is_integral_v<T> };
        { std::is_pointer_v<T> };
        { std::is_floating_point_v<T> };
    }
	inline void emit_if_nz(std::vector<byte>& buf, const T val_) {
		if(val_ != 0)
			emit<T>(buf, val_);
	}
};

} // namespace x86_64

#endif // JAB_X86_64_ENCODE_H
