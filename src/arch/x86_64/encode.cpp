#include "arch/x86_64/encode.h"

using namespace jab;
using namespace x86_64;

Encoder::Encoder(Module* module): module{module} {

}

BinaryFile Encoder::bin() {
	return {};
}

std::vector<std::byte> Encoder::raw_bin() {
	return {};
}
