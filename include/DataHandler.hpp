#ifndef FTK_DATAHANDLER_HPP
#define FTK_DATAHANDLER_HPP

#include <iostream>      
#include <fstream>
#include <sstream>       
#include <vector>               
#include <string>                        
#include <chrono>   
#include <queue>
#include <unordered_map>
#include <cstdint>
#include <random>
#include <algorithm>
#include <utility>
#include <functional>
#include <tuple>

inline void hash_combine(std::size_t& seed, std::size_t hash) {
    seed ^= hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


class Spatial_Invariance_Tracks{
    public:
        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> row_2_array;
        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> col_2_array;
        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> sensor_2_array;
        size_t size_2 = 0;

        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> row_1_array;
        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> col_1_array;
        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> sensor_1_array;
        size_t size_1 = 0;

        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> row_0_array;
        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> col_0_array;
        std::array<int,MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN> sensor_0_array;
        size_t size_0 = 0;

        inline bool operator==(const Spatial_Invariance_Tracks& other) const {
            if (size_0 != other.size_0 || size_2 != other.size_2 || size_1 != other.size_1)
            return false;

            return std::equal(row_0_array.begin(), row_0_array.begin() + size_0, other.row_0_array.begin()) &&
                std::equal(col_0_array.begin(), col_0_array.begin() + size_0, other.col_0_array.begin()) &&
                std::equal(sensor_0_array.begin(), sensor_0_array.begin() + size_0, other.sensor_0_array.begin()) &&
                std::equal(row_1_array.begin(), row_1_array.begin() + size_1, other.row_1_array.begin()) &&
                std::equal(col_1_array.begin(), col_1_array.begin() + size_1, other.col_1_array.begin()) &&
                std::equal(sensor_1_array.begin(), sensor_1_array.begin() + size_1, other.sensor_1_array.begin()) &&
                std::equal(row_2_array.begin(), row_2_array.begin() + size_2, other.row_2_array.begin()) &&
                std::equal(sensor_2_array.begin(), sensor_2_array.begin() + size_2, other.sensor_2_array.begin()) &&
                std::equal(col_2_array.begin(), col_2_array.begin() + size_2, other.col_2_array.begin());
            }
            // Add a (row, col) pair to the "_0" arrays
        inline void add_0(int sensor, int row, int col) {
            if (size_0 < MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN) {
                row_0_array[size_0] = row;
                col_0_array[size_0] = col;
                sensor_0_array[size_0] = sensor;
                ++size_0;
            } else {
                throw std::out_of_range("add_0: Exceeded max capacity");
            }
        }

        inline void add_1(int sensor, int row, int col) {
            if (size_1 < MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN) {
                row_1_array[size_1] = row;
                col_1_array[size_1] = col;
                sensor_1_array[size_1] = sensor;
                ++size_1;
            } else {
                throw std::out_of_range("add_1: Exceeded max capacity");
            }
        }
        // Add a (row, col) pair to the "_2" arrays
        inline void add_2(int sensor, int row, int col) {
            if (size_2 < MAX_SPATIAL_INVARIANT_TRACK_ARRAY_LEN) {
                row_2_array[size_2] = row;
                col_2_array[size_2] = col;
                sensor_2_array[size_2] = sensor;
                ++size_2;
            } else {
                throw std::out_of_range("add_2: Exceeded max capacity");
            }
        }

        friend inline std::ostream& operator<<(std::ostream& os, const Spatial_Invariance_Tracks& c) {
            for (size_t i = 0; i < c.size_0; i++) {
                os << c.sensor_0_array[i] << ','<< c.row_0_array[i] << ',' << c.col_0_array[i];
                if (i != c.size_0 - 1) os << ',';
                else os << '/';
            }

            for (size_t i = 0; i < c.size_1; i++) {
                os << c.sensor_1_array[i] << ','<< c.row_1_array[i] << ',' << c.col_1_array[i];
                if (i != c.size_1 - 1) os << ',';
                else os << '/';
            }
            for (size_t i = 0; i < c.size_2; i++) {
                os << c.sensor_2_array[i] << ','<< c.row_2_array[i] << ',' << c.col_2_array[i];
                if (i != c.size_2 - 1) os << ',';
            }
            return os;
        }

        std::size_t hash(uint64_t seed = 0) const {
            XXHash64 h(seed);
    
            h.add(&size_0, sizeof(size_0));
            h.add(row_0_array.data(), sizeof(uint16_t) * size_0);
            h.add(col_0_array.data(), sizeof(uint16_t) * size_0);
            h.add(sensor_0_array.data(), sizeof(uint16_t) * size_0);

            h.add(&size_1, sizeof(size_1));
            h.add(row_1_array.data(), sizeof(uint16_t) * size_1);
            h.add(col_1_array.data(), sizeof(uint16_t) * size_1);
            h.add(sensor_1_array.data(), sizeof(uint16_t) * size_1);
    
            h.add(&size_2, sizeof(size_2));
            h.add(row_2_array.data(), sizeof(uint16_t) * size_2);
            h.add(col_2_array.data(), sizeof(uint16_t) * size_2);
            h.add(sensor_2_array.data(), sizeof(uint16_t) * size_2);
    
            return h.hash(); // restituisce uint64_t
        }

    };

struct Spatial_Invariance_Tracks_Hash {
    std::size_t operator()(const Spatial_Invariance_Tracks& t) const {
        return t.hash(); // Usa il metodo hash definito nella classe
    }
    };

template <typename T>
using Spatial_Invariance_Tracks_Map = std::unordered_map<Spatial_Invariance_Tracks, T, Spatial_Invariance_Tracks_Hash>;
//----------------------------------------------------------------------------------------------------

// class Spatial_Invariance_Clusters {
//     public:
//         int row0, col0, row2, col2;

//         // Costruttore con parametri
//         inline Spatial_Invariance_Clusters(int row0, int col0, int row2, int col2)
//             : row0(row0), col0(col0), row2(row2), col2(col2) {}
    
//         // Costruttore di default
//         inline Spatial_Invariance_Clusters() = default;
    
//         // Operatore di uguaglianza
//         inline bool operator==(const Spatial_Invariance_Clusters& other) const {
//             return row0 == other.row0 && col0 == other.col0 &&
//                    row2 == other.row2 && col2 == other.col2;
//         }
    
//         // Operatore di confronto per ordinamento
//         inline bool operator<(const Spatial_Invariance_Clusters& other) const {
//             if (row0 != other.row0) return row0 < other.row0;
//             if (col0 != other.col0) return col0 < other.col0;
//             if (row2 != other.row2) return row2 < other.row2;
//             return col2 < other.col2;
//         }
    
//         // Operatore di stampa
//         friend inline std::ostream& operator<<(std::ostream& os, const Spatial_Invariance_Clusters& c) {
//             os << c.row0 << ',' << c.col0 << '/' << c.row2 << ',' << c.col2;
//             return os;
//         }
//     };


// template <>
// struct std::hash<Spatial_Invariance_Clusters> {
//     std::size_t operator()(const Spatial_Invariance_Clusters& c) const {
//         std::size_t seed = 0;
//         hash_combine(seed, std::hash<int>{}(c.row0));
//         hash_combine(seed, std::hash<int>{}(c.col0));
//         hash_combine(seed, std::hash<int>{}(c.row2));
//         hash_combine(seed, std::hash<int>{}(c.col2));
//         return seed;
//     }
// };


// template <typename T>
// using Spatial_Invariance_Clusters_Map = std::unordered_map<Spatial_Invariance_Clusters,T>;
class Spatial_Invariance_Clusters {
    public:
        int row0, col0, row2, col2;
        int row1, col1;
        int sensor;

        // Costruttore con parametri
        inline Spatial_Invariance_Clusters(int row0, int col0, int row2, int col2, int row1, int col1, int sensor)
            : row0(row0), col0(col0), row2(row2), col2(col2), row1(row1), col1(col1), sensor(sensor) {}
    
        // Costruttore di default
        inline Spatial_Invariance_Clusters() = default;
    
        // Operatore di uguaglianza
        inline bool operator==(const Spatial_Invariance_Clusters& other) const {
            return row0 == other.row0 && col0 == other.col0 &&
                   row1 == other.row1 && col1 == other.col1 &&
                   row2 == other.row2 && col2 == other.col2 &&
                    sensor == other.sensor;
        }
    
        // Operatore di confronto per ordinamento
        inline bool operator<(const Spatial_Invariance_Clusters& other) const {
            if (row1 != other.row1) return row1 < other.row1;
            if (col1 != other.col1) return col1 < other.col1;
            if (row0 != other.row0) return row0 < other.row0;
            if (col0 != other.col0) return col0 < other.col0;
            if (row2 != other.row2) return row2 < other.row2;
            if (col2 != other.col2) return col2 < other.col2;
            return sensor < other.sensor;
        }
    
        // Operatore di stampa
        friend inline std::ostream& operator<<(std::ostream& os, const Spatial_Invariance_Clusters& c) {
            os << c.sensor<<"/"<<c.row1 << ',' << c.col1 << '/' << c.row0 << ',' << c.col0 << '/' << c.row2 << ',' << c.col2;
            return os;
        }

        inline std::string to_string() const {
            std::ostringstream oss;
            oss << sensor << "/"
                // << row1 << "," << col1 << "/"
                << row0 << ";" << col0 << "/"
                << row2 << ";" << col2;
            return oss.str();
        }
    };


template <>
struct std::hash<Spatial_Invariance_Clusters> {
    std::size_t operator()(const Spatial_Invariance_Clusters& c) const {
        std::size_t seed = 0;
        hash_combine(seed, std::hash<int>{}(c.row1));
        hash_combine(seed, std::hash<int>{}(c.col1));
        hash_combine(seed, std::hash<int>{}(c.row0));
        hash_combine(seed, std::hash<int>{}(c.col0));
        hash_combine(seed, std::hash<int>{}(c.row2));
        hash_combine(seed, std::hash<int>{}(c.col2));
        hash_combine(seed, std::hash<int>{}(c.sensor));
        return seed;
    }
};


template <typename T>
using Spatial_Invariance_Clusters_Map = std::unordered_map<Spatial_Invariance_Clusters,T>;

//-------------------------------------------------------------------------------------------------
class Cluster {
    public:
        uint16_t row, col, sensor;
    
        inline Cluster(uint16_t row, uint16_t col, uint16_t sensor)
            : row(row), col(col), sensor(sensor) {}
    
        inline Cluster() = default;
    
        inline bool operator==(const Cluster& other) const {
            return row == other.row && col == other.col && sensor == other.sensor;
        }
    
        inline bool operator<(const Cluster& other) const {
            if (sensor != other.sensor) return sensor < other.sensor;
            if (row != other.row) return row < other.row;
            return col < other.col;
        }
    
        friend inline std::ostream& operator<<(std::ostream& os, const Cluster& c) {
            os << c.sensor << ',' << c.row << ',' << c.col;
            return os;
        }
    };

    template<typename T1, typename T2,typename T3>
std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3>& p) {
    return os  << std::get<0>(p) << "," << std::get<1>(p) << "," << std::get<2>(p);
}


template <>
struct std::hash<Cluster> {
    std::size_t operator()(const Cluster& c) const {
        return (static_cast<std::size_t>(c.sensor) << 32) |
                (static_cast<std::size_t>(c.col) << 16) |
                (static_cast<std::size_t>(c.row));
    }
};


namespace std {
    template <>
    struct hash<std::tuple<Cluster, Cluster, Cluster>> {
        std::size_t operator()(const std::tuple<Cluster, Cluster, Cluster>& t) const {
            std::size_t seed = 0;
            hash_combine(seed, std::hash<Cluster>{}(std::get<0>(t)));
            hash_combine(seed, std::hash<Cluster>{}(std::get<1>(t)));
            hash_combine(seed, std::hash<Cluster>{}(std::get<2>(t)));
            return seed;
        }
    };
}

std::string to_string(const std::tuple<Cluster, Cluster, Cluster>& tpl) {
    std::ostringstream oss;
    oss  << std::get<0>(tpl) << "," << std::get<1>(tpl) << "," << std::get<2>(tpl);
    return oss.str();
}

template <typename T>
using Clusters_Map = std::unordered_map<Cluster,T>;

template <typename T>
using Tracks_Map = std::unordered_map<std::tuple<Cluster,Cluster,Cluster>,T>;

class TracksHandler{
private:
    std::random_device rd;
    std::mt19937 g;
    
public:
    size_t n_events;
    std::vector<Cluster> frames_0_clusters;
    std::vector<Cluster> frames_1_clusters;
    std::vector<Cluster> frames_2_clusters;

    std::vector<std::tuple<Cluster,Cluster,Cluster>> data;
    std::ifstream file;
    size_t collapsed_pixels;

    TracksHandler(const std::string& path_file_clusters, size_t n_events, size_t collapsed_pixels = 1)
        : n_events(n_events) , file(path_file_clusters), collapsed_pixels(collapsed_pixels) { 
        g.seed(rd()); // Inizializza il generatore di numeri casuali
        if (!file.is_open()) {
            std::cerr << "Errore nell'aprire il file: " << path_file_clusters << std::endl;
            throw std::runtime_error("File non trovato");
        }
    }
    bool time_step(){
        // Carica sul vettore i clusters successivi liberando prima il vettore
        // Se non ci sono più cluster da leggere ritorna false
        data.clear();
        if (file.eof()) {
            return false; // EOF
        }
        if (!read_tracks()) {
            return false; // Errore di lettura
        }
        return true; // Successo
    }
    bool read_tracks(){
        for(size_t i = 0; i < n_events; ++i) {
            std::string line;
            if (!std::getline(file, line)) {
                return false; // EOF o errore di lettura
            }
            if (line.empty()) {
                i--;
                continue; // Ignora le righe vuote
            }
            std::stringstream ss(line);
            std::string cluster_str;

            int frame = 10;
            while (std::getline(ss, cluster_str, ';')) {
                std::stringstream cluster_ss(cluster_str);
                uint16_t row, col, sensor;
                char comma;
                if (cluster_ss >> sensor >> comma >> row >> comma >> col) {
                    int current_frame = int(int(sensor) / 4);

                    // seleziono solo i sensori dispari
                    // if (sensor % 4 != 0) continue;
                    
                    Cluster cluster(row / collapsed_pixels, col / collapsed_pixels, sensor);

                    if (current_frame == frame){
                        frames_0_clusters.push_back(cluster);
                        }
                    else if (current_frame == frame + 2){
                        frames_1_clusters.push_back(cluster);
                    }
                    else if (current_frame == frame + 4){
                        frames_2_clusters.push_back(cluster);
                    }
                }
            }

            // for(auto clu1 : frames_0_clusters){
            //     for(auto clu2 : frames_1_clusters){
            //         for (auto clu3 : frames_2_clusters){
            //             data.push_back(std::make_tuple(clu1, clu2, clu3));
            //         }
            //     }
            // }
            // frames_0_clusters.clear();
            // frames_1_clusters.clear();
            // frames_2_clusters.clear();


            if (frames_0_clusters.size() == 0 || frames_2_clusters.size() == 0 || frames_1_clusters.size() == 0){
                frames_0_clusters.clear();
                frames_1_clusters.clear();
                frames_2_clusters.clear();
                continue;
            }

            std::vector<Cluster> unique;
            
            for (const auto& x : frames_1_clusters) {
                bool found = false;
                for (const auto& y : unique) {
                    if (x == y) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    continue;
                }
                unique.push_back(x);
            }
            
            // Rimuovi i duplicati da frames_1_clusters
            frames_1_clusters = std::move(unique);
            unique.clear();
            // for (auto roba : frames_1_clusters){
            //     std::cout<<roba<<" ";
            // }
            // std::cout<<std::endl;


            for (const auto& x : frames_0_clusters) {
                bool found = false;
                for (const auto& y : unique) {
                    if (x == y) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    continue;
                }
                unique.push_back(x);
            }
            
            // Rimuovi i duplicati da frames_0_clusters
            frames_0_clusters = std::move(unique);
            unique.clear();

            // for (auto roba : frames_0_clusters){
            //     std::cout<<roba<<" ";
            // }
            // std::cout<<std::endl;


            for (const auto& x : frames_2_clusters) {
                bool found = false;
                for (const auto& y : unique) {
                    if (x == y) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    continue;
                }
                unique.push_back(x);
            }
            
            // Rimuovi i duplicati da frames_1_clusters
            frames_2_clusters = std::move(unique);
            unique.clear();

            // for (auto roba : frames_2_clusters){
            //     std::cout<<roba<<" ";
            // }
            // std::cout<<std::endl;
            // exit(0);

    


            for(auto clu1 : frames_1_clusters){
                for(auto clu0 : frames_0_clusters){
                    for (auto clu2 : frames_2_clusters){
                                // Spatial_Invariance_Clusters clusters(row0, col0, row2, col2);
                        data.push_back(std::make_tuple(clu0, clu1, clu2));
                    }
                }
            }
            frames_0_clusters.clear();
            frames_1_clusters.clear();
            frames_2_clusters.clear();
        }
        return true; // Successo
    }
};


class Spatial_Invariance_TracksHandler{    
    public:
        size_t n_events;
        std::vector<Cluster> frames_0_clusters;
        std::vector<Cluster> frames_1_clusters;
        std::vector<Cluster> frames_2_clusters;
    
        std::vector<Spatial_Invariance_Tracks> data;
        std::ifstream file;
        size_t collapsed_pixels;

    
        Spatial_Invariance_TracksHandler(const std::string& path_file_clusters, size_t n_events, size_t collapsed_pixels = 1)
            : n_events(n_events) , file(path_file_clusters), collapsed_pixels(collapsed_pixels) { 
            if (!file.is_open()) {
                std::cerr << "Errore nell'aprire il file: " << path_file_clusters << std::endl;
                throw std::runtime_error("File non trovato");
            }
        }
        bool time_step(){
            // Carica sul vettore i clusters successivi liberando prima il vettore
            // Se non ci sono più cluster da leggere ritorna false
            data.clear();
            if (file.eof()) {
                return false; // EOF
            }
            if (!read_tracks()) {
                return false; // Errore di lettura
            }
            return true; // Successo
        }
        bool read_tracks(){
            for(size_t i = 0; i < n_events; ++i) {
                std::string line;
                if (!std::getline(file, line)) {
                    return false; // EOF o errore di lettura
                }
                if (line.empty()) {
                    i--;
                    continue; // Ignora le righe vuote
                }
                std::stringstream ss(line);
                std::string cluster_str;
    
                int frame = 10;
                while (std::getline(ss, cluster_str, ';')) {
                    std::stringstream cluster_ss(cluster_str);
                    uint16_t row, col, sensor;
                    char comma;
                    if (cluster_ss >> sensor >> comma >> row >> comma >> col) {
                        int current_frame = int(int(sensor) / 4);
    
                        // seleziono solo i sensori dispari
                        // if (sensor % 4 == 0) continue;
                        
                        Cluster cluster(row / collapsed_pixels, col / collapsed_pixels, sensor);
    
                        if (current_frame == frame){
                            frames_0_clusters.push_back(cluster);
                            }
                        else if (current_frame == frame + 2){
                            frames_1_clusters.push_back(cluster);
                        }
                        else if (current_frame == frame + 4){
                            frames_2_clusters.push_back(cluster);
                        }
                    }
                }
                if (frames_0_clusters.size() == 0 & frames_2_clusters.size() == 0 & frames_1_clusters.size() == 0){
                    frames_0_clusters.clear();
                    frames_1_clusters.clear();
                    frames_2_clusters.clear();
                    continue;
                }

                std::vector<Cluster> unique;
            
                for (const auto& x : frames_1_clusters) {
                    bool found = false;
                    for (const auto& y : unique) {
                        if (x == y) {
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        continue;
                    }
                    unique.push_back(x);
                }
                
                // Rimuovi i duplicati da frames_1_clusters
                frames_1_clusters = std::move(unique);
                unique.clear();
                // for (auto roba : frames_1_clusters){
                //     std::cout<<roba<<" ";
                // }
                // std::cout<<std::endl;
    
    
                for (const auto& x : frames_0_clusters) {
                    bool found = false;
                    for (const auto& y : unique) {
                        if (x == y) {
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        continue;
                    }
                    unique.push_back(x);
                }
                
                // Rimuovi i duplicati da frames_0_clusters
                frames_0_clusters = std::move(unique);
                unique.clear();
    
                // for (auto roba : frames_0_clusters){
                //     std::cout<<roba<<" ";
                // }
                // std::cout<<std::endl;
    
    
                for (const auto& x : frames_2_clusters) {
                    bool found = false;
                    for (const auto& y : unique) {
                        if (x == y) {
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        continue;
                    }
                    unique.push_back(x);
                }
                
                // Rimuovi i duplicati da frames_1_clusters
                frames_2_clusters = std::move(unique);
                unique.clear();


                std::sort(frames_0_clusters.begin(), frames_0_clusters.end());
                std::sort(frames_1_clusters.begin(), frames_1_clusters.end());
                std::sort(frames_2_clusters.begin(), frames_2_clusters.end());

                Spatial_Invariance_Tracks track;
    
                for(auto clu1 : frames_1_clusters){
                    int row = static_cast<int>(clu1.row);
                    int col = static_cast<int>(clu1.col);
                    int sensor = static_cast<int>(clu1.sensor);
                    track.add_1(sensor, row, col);
                }
    
                for(auto clu1 : frames_0_clusters){
                    int row = static_cast<int>(clu1.row);
                    int col = static_cast<int>(clu1.col);
                    int sensor = static_cast<int>(clu1.sensor);
                    track.add_0(sensor, row, col);
                }
    
                for (auto clu1 : frames_2_clusters){
                    int row = static_cast<int>(clu1.row);
                    int col = static_cast<int>(clu1.col);
                    int sensor = static_cast<int>(clu1.sensor);
                    track.add_2(sensor, row, col);
                }
                if (track.size_0 > 0 || track.size_2 > 0 || track.size_1 > 0){
                    data.push_back(track);
                }
    

                frames_0_clusters.clear();
                frames_1_clusters.clear();
                frames_2_clusters.clear();
            }
            return true; // Successo
        }
    };
//-------------------------------------------------------------------------------------------------------------------------------------
class Spatial_Invariance_ClustersHandler{    
    public:
        size_t n_events;
        std::vector<Cluster> frames_0_clusters;
        std::vector<Cluster> frames_1_clusters;
        std::vector<Cluster> frames_2_clusters;

        std::unordered_set<Cluster> &black_
        list;
    
        std::vector<Spatial_Invariance_Clusters> data;
        std::ifstream file;
        size_t collapsed_pixels;
        size_t window_size = WINDOW_SIZE;
    
        Spatial_Invariance_ClustersHandler(const std::string& path_file_clusters, size_t n_events, std::unordered_set<Cluster> &black_list, size_t collapsed_pixels = 1, size_t window_size = WINDOW_SIZE)
            : n_events(n_events), file(path_file_clusters), black_list(black_list), collapsed_pixels(collapsed_pixels), window_size(window_size) { 
            if (!file.is_open()) {
                std::cerr << "Errore nell'aprire il file: " << path_file_clusters << std::endl;
                throw std::runtime_error("File non trovato");
            }
        }
        bool time_step(){
            // Carica sul vettore i clusters successivi liberando prima il vettore
            // Se non ci sono più cluster da leggere ritorna false
            data.clear();
            if (file.eof()) {
                return false; // EOF
            }
            if (!read_tracks()) {
                return false; // Errore di lettura
            }
            return true; // Successo
        }
        bool read_tracks(){
            for(size_t i = 0; i < n_events; ++i) {
                std::string line;
                if (!std::getline(file, line)) {
                    return false; // EOF o errore di lettura
                }
                if (line.empty()) {
                    i--;
                    continue; // Ignora le righe vuote
                }
                std::stringstream ss(line);
                std::string cluster_str;
    
                int frame = 10;
                while (std::getline(ss, cluster_str, ';')) {
                    std::stringstream cluster_ss(cluster_str);
                    uint16_t row, col, sensor;
                    char comma;
                    if (cluster_ss >> sensor >> comma >> row >> comma >> col) {
                        int current_frame = int(int(sensor) / 4);
    
                        // seleziono solo i sensori dispari
                        // if (sensor % 4 == 0) continue;
                        
                        Cluster cluster(row / collapsed_pixels, col / collapsed_pixels, sensor);

                        if (black_list.find(cluster) != black_list.end()) continue;
    
                        if (current_frame == frame){
                            frames_0_clusters.push_back(cluster);
                            }
                        else if (current_frame == frame + 2){
                            frames_1_clusters.push_back(cluster);
                        }
                        else if (current_frame == frame + 4){
                            frames_2_clusters.push_back(cluster);
                        }
                    }
                }
                if (frames_0_clusters.size() == 0 || frames_2_clusters.size() == 0 || frames_0_clusters.size() == 0){
                    frames_0_clusters.clear();
                    frames_1_clusters.clear();
                    frames_2_clusters.clear();
                    continue;
                }
    
                for(auto clu1 : frames_1_clusters){
                    for(auto clu0 : frames_0_clusters){
                        int row0 = static_cast<int>(clu0.row) - static_cast<int>(clu1.row);
                        int col0 = static_cast<int>(clu0.col) - static_cast<int>(clu1.col);
                        if ( (clu1.sensor %4 == clu0.sensor%4) && std::abs(row0) < window_size && std::abs(col0) < window_size ){
                            for (auto clu2 : frames_2_clusters){
                                int row2 = static_cast<int>(clu2.row) - static_cast<int>(clu1.row);
                                int col2 = static_cast<int>(clu2.col) - static_cast<int>(clu1.col);
                                if ( (clu1.sensor %4 == clu2.sensor%4) && std::abs(row2) < window_size && std::abs(col2) < window_size ){
                                    Spatial_Invariance_Clusters clusters(row0, col0, row2, col2, static_cast<int>(clu1.row)/ 1000, static_cast<int>(clu1.col)/ 1000, clu0.sensor%4);
                                    data.push_back(clusters);
                                }
                            }
                        }
                    }
                }
                frames_0_clusters.clear();
                frames_1_clusters.clear();
                frames_2_clusters.clear();
            }
            return true; // Successo
        }
    };
    
class Spatial_Invariance_ClustersHandler_predictive_track{    
    public:
        size_t n_events;
        std::vector<Cluster> frames_0_clusters;
        std::vector<Cluster> frames_1_clusters;
        std::vector<Cluster> frames_2_clusters;
        std::unordered_set<Cluster> &black_list;
    
        std::vector<Spatial_Invariance_Clusters> data;
        std::ifstream file;
        size_t collapsed_pixels;
        size_t window_size = WINDOW_SIZE;
    
        Spatial_Invariance_ClustersHandler_predictive_track(const std::string& path_file_clusters, size_t n_events, std::unordered_set<Cluster> &black_list, size_t collapsed_pixels = 1, size_t window_size = WINDOW_SIZE)
            : n_events(n_events) , file(path_file_clusters), collapsed_pixels(collapsed_pixels), window_size(window_size), black_list(black_list) { 
            if (!file.is_open()) {
                std::cerr << "Errore nell'aprire il file: " << path_file_clusters << std::endl;
                throw std::runtime_error("File non trovato");
            }
        }
        bool time_step(){
            // Carica sul vettore i clusters successivi liberando prima il vettore
            // Se non ci sono più cluster da leggere ritorna false
            data.clear();
            if (file.eof()) {
                return false; // EOF
            }
            if (!read_tracks()) {
                return false; // Errore di lettura
            }
            return true; // Successo
        }
        bool read_tracks(){
            for(size_t i = 0; i < n_events; ++i) {
                std::string line;
                if (!std::getline(file, line)) {
                    return false; // EOF o errore di lettura
                }
                if (line.empty()) {
                    i--;
                    continue; // Ignora le righe vuote
                }
                std::stringstream ss(line);
                std::string cluster_str;
    
                int frame = 10;
                while (std::getline(ss, cluster_str, ';')) {
                    std::stringstream cluster_ss(cluster_str);
                    uint16_t row, col, sensor;
                    char comma;
                    if (cluster_ss >> sensor >> comma >> row >> comma >> col) {
                        int current_frame = int(int(sensor) / 4);
    
                        // seleziono solo i sensori dispari
                        // if (sensor % 4 == 0) continue;
                        
                        Cluster cluster(row / collapsed_pixels, col / collapsed_pixels, sensor);

                        if (black_list.find(cluster) != black_list.end()) { std::cout<<cluster;continue;}
    
                        if (current_frame == frame){
                            frames_0_clusters.push_back(cluster);
                            }
                        else if (current_frame == frame + 2){
                            frames_1_clusters.push_back(cluster);
                        }
                        else if (current_frame == frame + 4){
                            frames_2_clusters.push_back(cluster);
                        }
                    }
                }
                if (frames_0_clusters.size() == 0 || frames_2_clusters.size() == 0 || frames_0_clusters.size() == 0){
                    frames_0_clusters.clear();
                    frames_1_clusters.clear();
                    frames_2_clusters.clear();
                    continue;
                }
    
                for(auto clu2 : frames_2_clusters){
                    for(auto clu0 : frames_0_clusters){
                        if ( (clu2.sensor %4 == clu0.sensor%4) ){
                            for (auto clu1 : frames_1_clusters){
                                // int row0 = static_cast<int>(clu0.row) - static_cast<int>(clu1.row);
                                // int col0 = static_cast<int>(clu0.col) - static_cast<int>(clu1.col);

                                // int row2 = static_cast<int>(clu2.row) - static_cast<int>(clu1.row);
                                // int col2 = static_cast<int>(clu2.col) - static_cast<int>(clu1.col);
                                
                                int row0 = static_cast<int>(clu0.row) ;
                                int col0 = static_cast<int>(clu0.col) ;
                                int row1 = static_cast<int>(clu1.row) ;
                                int col1 = static_cast<int>(clu1.col) ;
                                int row2 = static_cast<int>(clu2.row) ;
                                int col2 = static_cast<int>(clu2.col) ;

                                int baricentro_row = (row0 + row2)/2;
                                int baricentro_col = (col0 + col2)/2;

                                if ( (clu1.sensor %4 == clu2.sensor%4) && std::abs(baricentro_row - row1) < window_size && std::abs(baricentro_col - col1) < window_size ){
                                    Spatial_Invariance_Clusters clusters(row0 - row1, col0 - col1, row2 - row1, col2 - col1, row1/32, col1/32, clu0.sensor%4);
                                    data.push_back(clusters);
                                }
                            }
                        }
                    }
                }
                frames_0_clusters.clear();
                frames_1_clusters.clear();
                frames_2_clusters.clear();
            }
            return true; // Successo
        }
    };
//-----------------------------------------------------------------------------------------

class ClustersHandler{
    private:
        std::random_device rd;
        std::mt19937 g;
        
    public:
        size_t n_events;
        std::vector<Cluster> data;
        std::ifstream file;
        size_t collapsed_pixels;
    
        ClustersHandler(const std::string& path_file_clusters, size_t n_events, size_t collapsed_pixels = 1)
            : n_events(n_events) , file(path_file_clusters), collapsed_pixels(collapsed_pixels){ 
            g.seed(rd()); // Inizializza il generatore di numeri casuali
            if (!file.is_open()) {
                std::cerr << "Errore nell'aprire il file: " << path_file_clusters << std::endl;
                throw std::runtime_error("File non trovato");
            }
        }
                
        bool read_clusters() {
            // il file è codificato in questo modo:
            // -ogni riga corrisponde ad un evento: ogni evento contiene 3 numeri interi che corrispondo ai cluster e sono separati da una virgola
            // i cluster sono rappresentati da 3 numeri interi: riga, colonna e sensore
            // esempio: 1,2,3. Ogni cluster è separato da un punto e virgola
            //esempio di file:
            // 1,2,3;4,5,6;7,8,9;\n
            // 10,11,12;13,14,15;16,17,18;\n
    
        
            for(size_t i = 0; i < n_events; ++i) {
                std::string line;
                if (!std::getline(file, line)) {
                    return false; // EOF o errore di lettura
                }
                if (line.empty()) {
                    i--;
                    continue; // Ignora le righe vuote
                }
                std::stringstream ss(line);
                std::string cluster_str;
                int frame = 10;
                while (std::getline(ss, cluster_str, ';')) {
                    std::stringstream cluster_ss(cluster_str);
                    uint16_t row, col, sensor;
                    char comma;
                    if (cluster_ss >> sensor >> comma >> row >> comma >> col) {
                        int current_frame = int(int(sensor) / 4);
                        if ((current_frame != frame) & (current_frame != frame +2) & (current_frame != frame +4)) continue;
                        Cluster cluster(row / collapsed_pixels, col / collapsed_pixels, sensor);

                        data.emplace_back(cluster);
                    }
                }
            }
            return true; // Successo
        }
        void shuffle_clusters() {
            // Mescola i cluster per evitare che siano ordinati in modo sequenziale
            std::shuffle(data.begin(), data.end(), g);
        }
        bool time_step() {
            // Carica sul vettore i clusters successivi liberando prima il vettore
            // Se non ci sono più cluster da leggere ritorna false
    
            data.clear();
            if (file.eof()) {
                return false; // EOF
            }
            if (!read_clusters()) {
                return false; // Errore di lettura
            }
    
            //shuffle dei cluster
            shuffle_clusters();
            return true; // Successo
        }
    };


#endif //FTK_DATAHANDLER_HPP