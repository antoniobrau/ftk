#ifndef FTK_PATTERN_HPP
#define FTK_PATTERN_HPP

#include<DataHandler.hpp>

// template <typename T>
// using Patterns_Map = Spatial_Invariance_Tracks_Map<T>;
// using Pattern = Spatial_Invariance_Tracks;
// using DataHandler = Spatial_Invariance_TracksHandler;


// template <typename T>
// using Patterns_Map = Clusters_Map<T>;
// using Pattern = Cluster;
// using DataHandler = ClustersHandler;


// template <typename T>
// using Patterns_Map = Tracks_Map<T>;
// using Pattern = std::tuple<Cluster,Cluster,Cluster>;
// using DataHandler = TracksHandler;

template <typename T>
using Patterns_Map = Spatial_Invariance_Clusters_Map<T>;
using Pattern = Spatial_Invariance_Clusters;
using DataHandler = Spatial_Invariance_ClustersHandler;

#endif //FTK_PATTERN_HPP