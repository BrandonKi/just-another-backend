#ifndef JAB_X86_64_ENCODE_H
#define JAB_X86_64_ENCODE_H

#include "jab.h"
#include "arch/x86_64/mdir.h"

namespace jab::x86_64 {

inline u8 rex(bool w, bool r, bool x, bool b) {
    return 0b1000000 | (w << 3) | (r << 2) | (x << 1) | int(b);
}

inline u8 modrm(u8 mod, u8 rm, u8 reg) {
    return (mod << 6) | (reg << 3) | rm;
}

inline u8 sib(u8 scale, u8 index, u8 base) {
    return (scale << 6) | (index << 3) | base;
}

inline u8 rex_w = rex(1, 0, 0, 0);
inline u8 rex_r = rex(0, 1, 0, 0);
inline u8 rex_x = rex(0, 0, 1, 0);
inline u8 rex_b = rex(0, 0, 0, 1);

class Encoder {
public:
	Encoder(Module*);

	BinaryFile bin();
	// just for debug purposes at the moment
	std::vector<std::byte> raw_bin();

private:
	Module* module;

};

} // namespace x86_64

#endif // JAB_X86_64_ENCODE_H
