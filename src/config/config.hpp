#ifndef ALPHA_CONFIG_HPP
#define ALPHA_CONFIG_HPP

#include <iostream>
#include <stack>
#include <memory>
#include <raylib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <filesystem>



class Config {
public:

    Config();
    void load(const std::string& filename);
    static void createDefaultConfig(const std::string& filename) ;

    std::string get(const std::string& section, const std::string& key) const;
    int getInt(const std::string& section, const std::string& key) const;
    bool getBool(const std::string& section, const std::string& key) const;

    void affichage_config();

    std::string directory = "rsc";
    std::string filename = directory + "/config.ini";

private:

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
    static std::string trim(const std::string& str);


};
#endif //ALPHA_CONFIG_HPP
