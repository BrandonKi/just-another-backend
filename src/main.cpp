#include "Common.h"

struct OptLevel {
	Od,
	O1,
	O2,
};

struct CompileOptions {
	std::vector<IRModule> modules;
	OptLevel opt;
	
};

int main(int argc, char* argv[]) {
	
}

