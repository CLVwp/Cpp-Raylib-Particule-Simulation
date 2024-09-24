#include "config.hpp"

void Config::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    std::string current_section;

    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue; // Ignore comments and empty lines
        }

        if (line[0] == '[' && line.back() == ']') {
            current_section = line.substr(1, line.size() - 2);
        } else {
            std::istringstream ss(line);
            std::string key, value;

            if (std::getline(ss, key, '=') && std::getline(ss, value)) {
                key = trim(key);
                value = trim(value);
                data[current_section][key] = value;
            }
        }
    }

    file.close();
}

void Config::createDefaultConfig(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + filename);
    }

    file << "[window]\n";
    file << "width = 1024\n";
    file << "height = 768\n";
    file << "fps = 60\n\n";

    file << "[graphics]\n";
    file << "fullscreen = false\n\n";

    file << "[audio]\n";
    file << "global = 100\n";
    file << "music = 100\n";
    file << "fx = 100\n";

    file.close();
}

std::string Config::get(const std::string& section, const std::string& key) const {
    return data.at(section).at(key);
}

int Config::getInt(const std::string& section, const std::string& key) const {
    return std::stoi(data.at(section).at(key));
}

bool Config::getBool(const std::string& section, const std::string& key) const {
    std::string value = data.at(section).at(key);
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    return value == "true" || value == "1";
}

std::string Config::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");

    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

Config::Config() {
    // Vérifier si le dossier "rsc" existe, sinon le créer
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directory(directory);
    }
    // Vérifier si le fichier "config.ini" existe, sinon le créer
    if (!std::filesystem::exists(filename)) {
        createDefaultConfig(filename);
        std::cout << "Default config.ini created in " << directory << std::endl;
    }
}

void Config::affichage_config() {
    std::cout << "--------config.ini--------" << "\n";
    for (const auto& section_pair : data) {
        std::cout << "[" << section_pair.first << "]\n"; // Affiche le nom de la section

        // Parcours des clés et valeurs dans chaque section
        for (const auto& key_value_pair : section_pair.second) {
            std::cout << key_value_pair.first << " = " << key_value_pair.second << "\n"; // Affiche chaque clé et valeur
        }
        std::cout << "\n";
    }
    std::cout << "--------------------------" << "\n";

}
