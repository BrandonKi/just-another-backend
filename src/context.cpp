#include "context.h"

// TODO use an allocator for all of this in the future

using namespace jab;

ModuleBuilder* Context::new_module_builder(std::string name) {
	return new ModuleBuilder(name);
}
