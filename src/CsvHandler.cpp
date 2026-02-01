#include"CsvHandler.hpp"

#include "FTK.hpp"
#include "CostantSettings.hpp"

#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <stdexcept>

void saveOccorrenzeToCSV(FTK &ftk, const std::string& filename, float iterations) {
    auto occorrenze = ftk.get_topc();
    // Scrittura del file in UTF-8
    std::ofstream file(filename);
    file.imbue(std::locale::classic());

    file<<"# Total_Iterations; POOL_SIZE; DIM_MULTI_LEVEL\n";
    file<<"#"<<iterations<<";"<<POOL_SIZE<<";"<<DIM_MULTI_LEVEL<<";\n";

    file<<"Pattern;";
    file<<"Sum_level;";
    file<<"Count_level\n";

    for (const auto& pair : occorrenze) {
        file << pair.first << ";" << pair.second.first << ";" << pair.second.second << "\n";
    }

    file.close();
}


void ReadFromCSV(const std::string& filename,
                 std::unordered_map<std::string, int>& map)
{
    std::ifstream file(filename);
    file.imbue(std::locale::classic());

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        // commenti
        if (line[0] == '#')
            continue;

        // header colonne
        if (line.find("Pattern") != std::string::npos)
            continue;

        std::stringstream ss(line);
        std::string pattern;

        std::getline(ss, pattern, ';');

        auto it = map.find(pattern);
        if (it != map.end()) {
            it->second = 0;
        }
    }
}