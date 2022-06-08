#ifndef JAB_JIT_ENV_H
#define JAB_JIT_ENV_H

#include "jab.h"

namespace jab {

class JITEnv {
public:
	JITEnv(std::vector<byte> bin): bin{bin} {}

	i32 run_main();
	
private:
	std::vector<byte> bin;

	void* alloc_memory(size_t size);
	void dealloc(void *block, size_t size);
	void* make_executable(void *buf);

};

} // namespace jab

#endif // JAB_JIT_ENV_H
