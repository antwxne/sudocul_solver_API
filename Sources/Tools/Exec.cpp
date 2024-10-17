#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

#include "Tools/Exec.hpp"

#ifdef WIN32
    #define popen _popen
#endif

std::string Exec::run(const std::string &cmd) {
        std::string result;
    std::array<char, 128> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Can run the cmd: " + cmd);
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}