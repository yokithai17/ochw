#include "config.h"
std::ostream& ConfigHandler::serialize(std::ostream& out) const {
    return out << cfg_.N << '\n'
            << cfg_.WIDTH << '\n'
            << cfg_.HEIGHT << '\n'
            << cfg_.groundColor << '\n'
            << cfg_.gridColor << '\n';
}

std::istream& ConfigHandler::serialize(std::istream& in) {
    return in >> cfg_.N
            >> cfg_.WIDTH
            >> cfg_.HEIGHT
            >> cfg_.groundColor
            >> cfg_.gridColor;
}

std::string ConfigHandler::getCfgLine() const {
    std::ostringstream out(std::ostringstream::ate);

    this->serialize(out);

    return out.str();
}

void ConfigHandler::setConfigFromText(const std::string& text) {
    std::istringstream in(text);

    this->serialize(in);
}

Config ConfigHandler::getConfig() const {
    return cfg_;
}

Config::Config(const Config& cfg): 
        N(cfg.N),WIDTH(cfg.WIDTH),HEIGHT(cfg.HEIGHT)
    , groundColor(cfg.groundColor), gridColor (cfg.gridColor)
{}

Config& Config::operator=(const Config& other) {
    if (this == &other) return *this;
    N = other.N;
    WIDTH = other.WIDTH;
    HEIGHT = other.HEIGHT;
    groundColor = other.groundColor;
    gridColor = other.gridColor;
    return *this;
}