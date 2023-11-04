#pragma once

#include <string>
#include <vector>

struct ShaderSource {
    ShaderSource() = default;

    ShaderSource& add_var(const std::string& dir, const std::string& type, const std::string& name);
    ShaderSource& add_func(const std::string& type, const std::string& name, const std::string& args, const std::string& code);

    std::string str() const;

    std::vector<std::string> layouts;
    std::vector<std::string> functions;
};
