#ifndef JAB_REGISTER_ALLOCATOR_H
#define JAB_REGISTER_ALLOCATOR_H

#include "jab.h"

namespace jab {

class RegisterAllocator {
public:
	RegisterAllocator();

	void alloc(Module*);
	void alloc(Function*);

private:
	void assign_to_interval(TIRegister);
};

}  // namespace jab

#endif // JAB_REGISTER_ALLOCATOR_H
