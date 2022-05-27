#include "jit_env.h"

#include <windows.h>
#include <iostream>

using namespace jab;

// TODO take argc, argv
i32 JITEnv::run_main() {
    void* block = alloc_memory(bin.size());
    memcpy(block, bin.data(), bin.size());
    using exe = int(*)();
    exe func = (exe)make_executable(block);
    auto ret = func();
    dealloc(block, bin.size());
    return ret;
}

void* JITEnv::alloc_memory(size_t size) {
    //void *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); // linux
    void* ptr = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);               // windows

    if (ptr == (void *)-1) {
        std::cerr << "JIT ALLOC ERROR\n";
		assert(false);
        return nullptr;
    }
    return ptr;
}

void JITEnv::dealloc(void *block, size_t size) {
    //munmap(block, size);
    VirtualFree(block, size, MEM_RELEASE);
}

void* JITEnv::make_executable(void *buf) {

    //mprotect(buf, sizeof(*(char *)buf), PROT_READ | PROT_EXEC); // linux

    DWORD old;
    VirtualProtect(buf, sizeof(*(char*)buf), PAGE_EXECUTE_READ, &old);  // windows

    return buf;
}
