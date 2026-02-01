#pragma once

#include <string>
#include<unordered_map>

class FTK;  // forward declaration


// Scrive le occorrenze su file CSV
void saveOccorrenzeToCSV(FTK& ftk,
                         const std::string& filename,
                         float iterations);


// Legge un CSV e azzera i valori delle chiavi trovate nel file
void ReadFromCSV(const std::string& filename,
                 std::unordered_map<std::string, int>& map);
