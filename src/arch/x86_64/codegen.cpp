#include "encoder.h"

Encoder::Encoder(Module* module): module{module} {

}

BinaryFile Encoder::bin() {
	return {};
}

std::vector<std::byte> Encoder::raw_bin() {
	return {};
}
