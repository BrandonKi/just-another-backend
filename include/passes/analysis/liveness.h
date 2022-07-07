#ifndef JAB_ANALYSIS_LIVENESS_H
#define JAB_ANALYSIS_LIVENESS_H

#include "jab.h"

#include <vector>

namespace jab {

struct Interval {
	MIRegister reg;
	i32 start;
	i32 end;
};

struct Liveness {
	static std::vector<Interval> run_pass(Function*);
	static std::vector<Interval> run_pass(Module*);
};

} // namespace jab

#endif // JAB_ANALYSIS_LIVENESS_H
