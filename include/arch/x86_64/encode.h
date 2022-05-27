#ifndef JAB_X86_64_ENCODE_H
#define JAB_X86_64_ENCODE_H

#include "x86_64/MDIR.h"

namespace x86_64 {

constexpr u8 rex_w = rex(1, 0, 0, 0);
constexpr u8 rex_r = rex(0, 1, 0, 0);
constexpr u8 rex_x = rex(0, 0, 1, 0);
constexpr u8 rex_b = rex(0, 0, 0, 1);

u8 rex(bool w, bool r, bool x, bool b) {
    return 0b1000000 | (w << 3) | (r << 2) | (x << 1) | int(b);
}

u8 modrm(std::byte mod, std::byte rm, std::byte reg) {
    return (mod << 6) | (reg << 3) | rm;
}

u8 sib(std::byte scale, std::byte index, std::byte base) {
    return (scale << 6) | (index << 3) | base;
}

} // namespace x86_64

#endif // JAB_X86_64_ENCODE_H
