#include <iostream>
#include <random>
#include <chrono>
#include<unordered_map>
#include <fstream>
#include <sstream>
#include <numeric>
#include<atomic>
#include<mutex>
#include<deque>
#include <unordered_set>


#include"CostantSettings.hpp"
#include"xxhash64.h"
#include"FTK.hpp"
#include"DataHandler.hpp"
#include"pattern.hpp"
#include"ThreadPool.hpp"
#include"CsvHandler.hpp"



void tracks_counting(const std::string& input_csv,
                       const std::string& output_csv)
{
    // 1) Leggi pattern da CSV
    std::unordered_map<std::string, int> pattern_map;
    
    ReadFromCSV(input_csv, pattern_map);

    DataHandler dataHandler(root_post_process_file);

    int tempo = 0;
    while (true) {

        if (!dataHandler.time_step()) {
            std::cout << "EOF reached\n";
            break;
        }

        for (const auto& pattern : dataHandler.data) {
            std::ostringstream oss;
            oss << pattern;                 // QUI usa operator<<
            auto it = pattern_map.find(oss.str());
            if (it != pattern_map.end()) {
                ++it->second;
            }
        }

        std::cout << "Time step: " << tempo++
                  << "    Current iterations: "
                  << dataHandler.data.size() << std::endl;
    }

    // 5) Scrittura risultati
    std::ofstream out(output_csv);
    out << "Pattern;Count\n";

    for (const auto& [pattern, count] : pattern_map) {
        out << pattern << ";" << count << "\n";
    }
}

int main(int argc, char** argv)
{
    if (argc == 3) {
        // uso: ./prog input.csv output.csv
        tracks_counting(argv[1], argv[2]);
    } else {
        // valori di default: cambiali tu
        tracks_counting(
            "/home/abrau/code/data/fulltrack_0.txt",
            "/home/abrau/code/data/fulltrack_0_counting.txt"
        );
    }

    return 0;
}