#ifndef JAB_LINK_WINDOWS_PE_H
#define JAB_LINK_WINDOWS_PE_H

#include <iostream>
#include <vector>
#include <string>
#include <format>

#include <windows.h>
#include "microsoft_craziness.h"

namespace jab {

void link_coff_files(std::string, std::vector<std::string>);

};

#endif // JAB_LINK_WINDOWS_PE_H
