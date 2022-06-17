#ifndef JAB_REGISTER_ALLOCATOR_H
#define JAB_REGISTER_ALLOCATOR_H

#include "jab.h"

#include "arch/x86_64/mdf.h"
#include "register_manager.h"
#include "pass_manager.h"
#include "analysis/liveness.h"

namespace jab {

class RegisterAllocator {
public:
	RegisterAllocator(RegisterManager);

	void alloc(Module*);
	void alloc(Function*);

private:
	RegisterManager mng;

	void assign_to_interval(Function*, Interval);
	void assign_to_interval(Function*, Interval, MIRegister);

	void assign_fn_arg(Function*, Interval, i32);
};

}  // namespace jab

#endif // JAB_REGISTER_ALLOCATOR_H
