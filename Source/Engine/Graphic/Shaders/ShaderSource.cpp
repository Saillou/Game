#include "ShaderSource.hpp"

#include <sstream>


ShaderSource::ShaderSource() {

}

ShaderSource& ShaderSource::add_var(const std::string& dir, const std::string& type, const std::string& name) {
    std::stringstream ss;
    ss << dir << " ";
    ss << type << " ";
    ss << name << ";\n";

    layouts.push_back(ss.str());
    return *this;
}

ShaderSource& ShaderSource::add_func(const std::string& type, const std::string& name, const std::string& args, const std::string& code) {
    std::stringstream ss;
    ss << type << " ";
    ss << name << "(" << args << ") { \n";
    ss << code << "\n";
    ss << "} \n";

    layouts.push_back(ss.str());
    return *this;
}

std::string ShaderSource::str() const {
    std::stringstream ss;

    // version
    ss << "#version 460\n";

    // variables layouts
    for (const auto& func : functions)
        ss << func;

    // functions
    for (const auto& layout : layouts)
        ss << layout;

    // ending
    ss << "\n\0";
    return ss.str();
}