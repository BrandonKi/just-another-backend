#include "link/windows_pe.h"

using namespace jab;

static auto result = find_visual_studio_and_windows_sdk();

static void add_default_libpaths(std::wstring& buffer) {
	// default libpaths
	buffer += std::format(L"/libpath:\"{}\" ", result.vs_library_path);
	buffer += std::format(L"/libpath:\"{}\" ", result.windows_sdk_ucrt_library_path);
	buffer += std::format(L"/libpath:\"{}\" ", result.windows_sdk_um_library_path);
}

static void add_default_libs(std::wstring& buffer) {
	// default libs
	buffer += std::format(L"/defaultlib:\"{}\" ", L"LIBCMT");
	buffer += std::format(L"/defaultlib:\"{}\" ", L"OLDNAMES");
}

void jab::link_coff_files(std::string name, std::vector<std::string> files) {

	auto wname = std::wstring(name.begin(), name.end());
	
	std::wstring command = std::format(
		L"{}\\link.exe /nologo /machine:amd64 "
		L"/subsystem:console  /debug /pdb:{}.pdb /out:{}.exe ",
		result.vs_exe_path, wname, wname);
///entry:main
	add_default_libpaths(command);
	add_default_libs(command);
	
	for(auto& file: files) {
		auto filename = std::wstring(file.begin(), file.end());
		command += std::format(L"{} ", filename);
	}
		
	std::wcout << L"Running Linker Command: " << command << L"\n";

    STARTUPINFOW si = {};
    PROCESS_INFORMATION pi = {};

    if (!CreateProcessW(nullptr, command.data(), nullptr, nullptr, true, 0, nullptr, nullptr, &si, &pi)) {
		std::cout << "linker failed :(";
		assert(false);
	}

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
