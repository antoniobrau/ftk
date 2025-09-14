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


// void  save_sliding_window_occorrences(const std::string& filename, const Patterns_Map<std::array<std::pair<int,int>, N_POINTS_SLIDING_WINDOW>>& clusters, const std::array<float,N_POINTS_SLIDING_WINDOW>& total_iterations) {
//     // Scrittura del file in UTF-8
//     std::ofstream file(filename);
//     file.imbue(std::locale::classic());

//     file << "# Total_Iterations\n";
//     file << "#";
//     for(int i = 0; i < N_POINTS_SLIDING_WINDOW; ++i) {
//         file << total_iterations[i] << ";";
//     }
//     file << "\n";

//     file << "Pattern;";
//     for (int i = 0; i < N_POINTS_SLIDING_WINDOW; ++i) {
//         file << "Sum_level_" << i << ";";
//         file << "Count_level_" << i << ";";
//     }
//     file << "\n";
//     for (const auto& pair : clusters) {
//         file << pair.first << ";";
//         for (int i = 0; i < N_POINTS_SLIDING_WINDOW; ++i) {
//             file << pair.second[i].first << ";";
//             file << pair.second[i].second << ";";
//         }
//         file << "\n";
//     }
//     file.close();

// }
// void sliding_window(const std::string& filename, int window_size) {
//     //Prendiamo un insieme di 100 punti
//     Patterns_Map<std::array<std::pair<int,int>, N_POINTS_SLIDING_WINDOW>> clusters;
//     DataHandler dataHandler(filename, 100, 16);
//     ThreadPool pool(POOL_SIZE);
//     FTK ftk(window_size, dataHandler, pool, 0.999, 5000);
//     std::array<float,N_POINTS_SLIDING_WINDOW> total_iterations = {0};

//     size_t current_point = 0;
//     while (ftk.time_update()) {
//         if (ftk.time == 16000) {
//             break;
//         }

//         if (ftk.time % 80 == 0 && ftk.time > 0) {
//             total_iterations[current_point] = ftk.get_total_iterations();
//             auto topc = ftk.get_topc();
//             for (auto it = topc.begin(); it != topc.end(); it++){
//                 auto &cluster = it->first;
//                 auto &pair = it->second;
//                 if (clusters.find(cluster) == clusters.end()){
//                     clusters.emplace(cluster, std::array<std::pair<int,int>, N_POINTS_SLIDING_WINDOW>{});
//                     clusters[cluster][current_point] = std::make_pair(pair.first, pair.second);
//                 }
//                 else {
//                     auto &array = clusters[cluster];
//                     array[current_point] = std::make_pair(pair.first, pair.second);
//                 }
//             }
//             current_point++;
//             if (current_point == N_POINTS_SLIDING_WINDOW) {
//                 break;
//             }
//         }
//         std::cout << "Time step: " << ftk.time <<"    Current iterations: "<<ftk.current_iterations<< std::endl;
//     }

//     save_sliding_window_occorrences("/home/abrau/code/sliding_window.txt", clusters, total_iterations);
//     std::cout << "Sliding window saved." << std::endl;
// }



// void tracks_simulation(const std::string& filename) {
//     std::unordered_set<Cluster> black_list;
//     std::string data = "58,221,173;8,251,72 ;0,157,411;58,241,180;42,94,359 ;58,243,79 ;43,149,730;50,244,54 ;43,17,22  ;50,54,288 ;56,156,722;48,13,12  ;48,180,723;58,217,127;50,188,168;42,206,27 ;42,72,68  ;42,149,175;56,87,349 ;42,249,7  ;50,87,165 ;41,168,294;40,253,686;56,35,473 ;42,220,106;41,103,504;56,108,681;56,198,734;42,211,140;56,172,630;40,187,491;42,88,202 ;50,217,36 ;56,240,633;42,105,98 ;42,170,387;42,78,203 ;58,77,469 ;40,224,567;56,244,480;";

//     std::stringstream ss(data);
//     std::string triple_str;

//     while (std::getline(ss, triple_str, ';')) {
//         // Rimuovi spazi iniziali/finali
//         triple_str.erase(0, triple_str.find_first_not_of(" \t"));
//         triple_str.erase(triple_str.find_last_not_of(" \t") + 1);

//         if (!triple_str.empty()) {
//             std::stringstream triple_ss(triple_str);
//             std::string num_str;
//             std::vector<int> nums;

//             while (std::getline(triple_ss, num_str, ',')) {
//                 // Rimuovi spazi e converti in intero
//                 num_str.erase(0, num_str.find_first_not_of(" \t"));
//                 num_str.erase(num_str.find_last_not_of(" \t") + 1);
//                 nums.push_back(std::stoi(num_str));
//             }

//             // Controllo che ci siano esattamente 3 numeri
//             if (nums.size() == 3) {
//                 Cluster clu(nums[2], nums[0], nums[1]);
//                 black_list.emplace(clu);
//             } else {
//                 std::cerr << "⚠️  Tripletta malformata: '" << triple_str << "'\n";
//             }
//         }
//     }

//     DataHandler dataHandler(filename, 10000, black_list, 1, 16);
//     ThreadPool pool(POOL_SIZE);
//     // FTK ftk(100000000, dataHandler, pool, 0.999, 5000);
//     FTK ftk(200000, dataHandler, pool, 0.999, 50000);

//     while (ftk.time_update()) {
//         // if (ftk.time == 10) {
//         //     break;
//         // }
//         std::cout << "Time step: " << ftk.time <<"    Current iterations: "<<ftk.current_iterations<< "    Total Iterations : " <<ftk.get_total_iterations()<<std::endl;
//     }

//     saveOccorrenzeToCSV(ftk, "/home/abrau/code/full_tracks.txt", ftk.get_total_iterations());
// }



std::vector<std::string> loadTracksFromCSV(const std::string& filename) {
    std::vector<std::string> patterns;

    std::ifstream file(filename, std::ios::in | std::ios::binary);
    // file.imbue(std::locale(std::locale::classic(), new std::codecvt_utf8<char>));

    if (!file.is_open()) {
        std::cerr << "Errore nell'aprire il file: " << filename << std::endl;
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        // Salta i commenti
        if (line.empty() || line[0] == '#')
            continue;

        std::stringstream ss(line);
        std::string pattern_str;

        // Leggi il primo campo (pattern), che è tipo: "sensor,row,col"
        if (!std::getline(ss, pattern_str, ';'))
            continue;

        std::stringstream pattern_stream(pattern_str);
        std::string sensor0_str, row0_str, col0_str, sensor1_str, row1_str, col1_str, sensor2_str, row2_str, col2_str;

        if (std::getline(pattern_stream, sensor0_str, ',') &&
            std::getline(pattern_stream, row0_str, ',') &&
            std::getline(pattern_stream, col0_str, ',') &&
            std::getline(pattern_stream, sensor1_str, ',') &&
            std::getline(pattern_stream, row1_str, ',') &&
            std::getline(pattern_stream, col1_str, ',') &&
            std::getline(pattern_stream, sensor2_str, ',') &&
            std::getline(pattern_stream, row2_str, ',') &&
            std::getline(pattern_stream, col2_str, ',')) {

            int sensor0 = std::stoi(sensor0_str);
            int row0 = std::stoi(row0_str);
            int col0 = std::stoi(col0_str);

            int sensor1 = std::stoi(sensor1_str);
            int row1 = std::stoi(row1_str);
            int col1 = std::stoi(col1_str);

            int sensor2 = std::stoi(sensor2_str);
            int row2 = std::stoi(row2_str);
            int col2 = std::stoi(col2_str);

            std::array<int,9> tmp = { 
                sensor0, row0, col0,
                sensor1, row1, col1,
                sensor2, row2, col2 
            };

            std::ostringstream oss;
            oss << tmp[0] << "/"
                << tmp[4] << "," << tmp[5] << "/"
                << tmp[1] << "," << tmp[2] << "/"
                << tmp[7] << "," << tmp[8];

            patterns.emplace_back(oss.str());


        }
    }

    file.close();
    return patterns;
}
std::vector<Pattern> loadPatternsFromCSV(const std::string& filename) {
    if constexpr (std::is_same_v<Pattern, std::tuple<Cluster,Cluster,Cluster>>) {
        std::vector<Pattern> patterns;

        std::ifstream file(filename, std::ios::in | std::ios::binary);
        // file.imbue(std::locale(std::locale::classic(), new std::codecvt_utf8<char>));

        if (!file.is_open()) {
            std::cerr << "Errore nell'aprire il file: " << filename << std::endl;
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            // Salta i commenti
            if (line.empty() || line[0] == '#')
                continue;

            std::stringstream ss(line);
            std::string pattern_str;

            // Leggi il primo campo (pattern), che è tipo: "sensor,row,col"
            if (!std::getline(ss, pattern_str, ';'))
                continue;

            std::stringstream pattern_stream(pattern_str);
            std::string sensor0_str, row0_str, col0_str, sensor1_str, row1_str, col1_str, sensor2_str, row2_str, col2_str;

            if (std::getline(pattern_stream, sensor0_str, ',') &&
                std::getline(pattern_stream, row0_str, ',') &&
                std::getline(pattern_stream, col0_str, ',') &&
                std::getline(pattern_stream, sensor1_str, ',') &&
                std::getline(pattern_stream, row1_str, ',') &&
                std::getline(pattern_stream, col1_str, ',') &&
                std::getline(pattern_stream, sensor2_str, ',') &&
                std::getline(pattern_stream, row2_str, ',') &&
                std::getline(pattern_stream, col2_str, ',')) {

                int sensor0 = std::stoi(sensor0_str);
                int row0 = std::stoi(row0_str);
                int col0 = std::stoi(col0_str);

                Cluster a0(row0,col0,sensor0);

                int sensor1 = std::stoi(sensor1_str);
                int row1 = std::stoi(row1_str);
                int col1 = std::stoi(col1_str);

                Cluster a1(row1,col1,sensor1);

                int sensor2 = std::stoi(sensor2_str);
                int row2 = std::stoi(row2_str);
                int col2 = std::stoi(col2_str);

                Cluster a2(row2,col2,sensor2);

                patterns.emplace_back(std::make_tuple(a0, a1, a2));
            }
        }

        file.close();
        return patterns;
    }
    if constexpr (std::is_same_v<Pattern, Cluster>) {
        std::vector<Pattern> patterns;

        std::ifstream file(filename, std::ios::in | std::ios::binary);
        // file.imbue(std::locale(std::locale::classic(), new std::codecvt_utf8<char>));

        if (!file.is_open()) {
            std::cerr << "Errore nell'aprire il file: " << filename << std::endl;
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            // Salta i commenti
            if (line.empty() || line[0] == '#')
                continue;

            std::stringstream ss(line);
            std::string pattern_str;

            // Leggi il primo campo (pattern), che è tipo: "sensor,row,col"
            if (!std::getline(ss, pattern_str, ';'))
                continue;

            std::stringstream pattern_stream(pattern_str);
            std::string sensor_str, row_str, col_str;

            if (std::getline(pattern_stream, sensor_str, ',') &&
                std::getline(pattern_stream, row_str, ',') &&
                std::getline(pattern_stream, col_str, ',')) {

                int sensor = std::stoi(sensor_str);
                int row = std::stoi(row_str);
                int col = std::stoi(col_str);

                Cluster a(row,col,sensor);

                patterns.emplace_back(a);
            }
        }

        file.close();
        return patterns;
    }
}

void save_occorrenze( const std::string& filename, std::unordered_map<Pattern, int> &pattern_map, float total_iterations) { 
    // Scrittura del file in UTF-8
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    // file.imbue(std::locale(std::locale::classic(), new std::codecvt_utf8<char>));

    file << "#Total_Iterations\n";
    file << "#"<<total_iterations << "\n";
    file<<"Pattern;p\n";

    for (const auto& pair : pattern_map) {
        file << pair.first << ";" << pair.second << "\n";
    }

    file.close();
}

void save_occorrenze_tracce(const std::string& filename,
    const std::unordered_map<std::string, int>& pattern_map,
    float total_iterations) 
    {
    std::ofstream file(filename);
    if (!file) {
    throw std::runtime_error("Impossibile aprire il file: " + filename);
    }

    file << "#Total_Iterations\n"
    << "#" << total_iterations << "\n"
    << "Pattern;p\n";

    for (const auto& [pattern, count] : pattern_map) {
        file << pattern << ";" << count << "\n";
    }
}


int main() {
    std::unordered_set<Cluster> black_list;
    std::string data = "58,221,173;8,251,72 ;0,157,411;58,241,180;42,94,359 ;58,243,79 ;43,149,730;50,244,54 ;43,17,22  ;50,54,288 ;56,156,722;48,13,12  ;48,180,723;58,217,127;50,188,168;42,206,27 ;42,72,68  ;42,149,175;56,87,349 ;42,249,7  ;50,87,165 ;41,168,294;40,253,686;56,35,473 ;42,220,106;41,103,504;56,108,681;56,198,734;42,211,140;56,172,630;40,187,491;42,88,202 ;50,217,36 ;56,240,633;42,105,98 ;42,170,387;42,78,203 ;58,77,469 ;40,224,567;56,244,480;";

    std::stringstream ss(data);
    std::string triple_str;

    while (std::getline(ss, triple_str, ';')) {
        // Rimuovi spazi iniziali/finali
        triple_str.erase(0, triple_str.find_first_not_of(" \t"));
        triple_str.erase(triple_str.find_last_not_of(" \t") + 1);

        if (!triple_str.empty()) {
            std::stringstream triple_ss(triple_str);
            std::string num_str;
            std::vector<int> nums;

            while (std::getline(triple_ss, num_str, ',')) {
                // Rimuovi spazi e converti in intero
                num_str.erase(0, num_str.find_first_not_of(" \t"));
                num_str.erase(num_str.find_last_not_of(" \t") + 1);
                nums.push_back(std::stoi(num_str));
            }

            // Controllo che ci siano esattamente 3 numeri
            if (nums.size() == 3) {
                Cluster clu(nums[2], nums[0], nums[1]);
                black_list.emplace(clu);
            } else {
                std::cerr << "⚠️  Tripletta malformata: '" << triple_str << "'\n";
            }
        }
    }

    // Esempio di utilizzo
    DataHandler dataHandler("/home/abrau/code/new_clusters_output.txt", 100, black_list, 1,64);
    // std::vector<Pattern> patterns = loadPatternsFromCSV("/home/abrau/code/patterns_tracce_64.txt");
    std::vector<std::string> patterns = loadTracksFromCSV("/home/abrau/code/patterns_tracce_64.txt");
    // Patterns_Map<int> pattern_map;
    std::unordered_map<std::string, int> pattern_map;
    float total_iterations = 0;
    for (const auto& pattern : patterns) {
        pattern_map[pattern] = 0; // Inizializza il conteggio a 0
    }

    int tempo = 0;
    // for (int i = 0; i < 14840; i++) dataHandler.time_step();
    while(true) {
        if (  !dataHandler.time_step()) {

            std::cout << "EOF reached" << std::endl;
            break;
        }
        total_iterations += dataHandler.data.size();
        // if ( tempo++ >= 1000) break;
        for (const auto& pattern : dataHandler.data) {
            std::array<int,9> p = {
                pattern.sensor, pattern.row0, pattern.col0,
                pattern.sensor, pattern.row1, pattern.col1,
                pattern.sensor, pattern.row2, pattern.col2
            };

            std::ostringstream oss;
                oss << p[0] << "/"
                    << p[4] << "," << p[5] << "/"
                    << p[1] << "," << p[2] << "/"
                    << p[7] << "," << p[8];
    
            // Controlla se il cluster è presente nel pattern_map
            auto it = pattern_map.find(oss.str());
            if (it != pattern_map.end()) {
                it->second++; // Incrementa il conteggio
            }
        }
        std::cout << "Time step: " << tempo << "    Current iterations: " << dataHandler.data.size() << std::endl;
    }
    save_occorrenze_tracce("/home/abrau/code/occorrenze.txt", pattern_map, total_iterations);
    return 0;
}
// int main() {
//     // sliding_window("/home/abrau/code/clusters_output.txt", 1);
//     tracks_simulation("/home/abrau/code/new_clusters_output.txt");

//     return 0;
// }