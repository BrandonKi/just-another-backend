#ifndef JAB_CONTEXT_H
#define JAB_CONTEXT_H

#include "module_builder.h"

namespace jab {

class Context {
public:
	Context(): options{} {}
	Context(CompileOptions options): options{options} {}

	ModuleBuilder* new_module_builder(std::string);

private:
	CompileOptions options;
};

} // namespace jab

#endif // JAB_CONTEXT_H
