#ifndef PROXIMITY_CITY_SEARCH_H
#define PROXIMITY_CITY_SEARCH_H

#include <unordered_map>
#include <string>
#include <functional>
#include <map>
#include <set>

/**
 * @typedef NormFunction
 * @brief A function type used to compute distances between coordinates.
 *
 * The NormFunction type represents a function that takes two doubles (x and y) as input
 * and returns a double representing the distance between them according to a specific norm.
 */
using NormFunction = std::function<double(double, double)>;

/**
 * @typedef SortedMap
 * @brief A container type that stores cities sorted by their distance from a reference city.
 *
 * The SortedMap type is a multimap where the keys represent the distance from a reference city,
 * and the values represent the names of the cities. The cities are sorted based on their distance.
 */
using SortedMap = std::multimap<double, std::string>;

/**
 * @typedef Coordinates
 * @brief A pair of double values representing the latitude and longitude of a city.
 *
 * The Coordinates type is a pair of double values, where the first value represents the latitude
 * and the second value represents the longitude of a city's coordinates.
 */
using Coordinates = std::pair<double, double>;


/**
 * @class ProximityCitySearch
 * @brief A class that performs proximity-based city searches.
 *
 * The ProximityCitySearch class allows you to add cities with their coordinates to a search data structure
 * and perform proximity-based searches to find cities within a given radius of a specified city.
 * It supports different norm functions for distance computation and can also compute the number of cities
 * located north of a specified city within a given radius.
 */
class ProximityCitySearch {
public:
    ProximityCitySearch();
    void addCity(std::string, Coordinates);
    SortedMap searchProximalCities(const std::string&, double, int);
    long long computeNorthernCities(const std::string&, const SortedMap&);
    const std::map<std::string, Coordinates> getCitiesMap() const;
    
private:
    std::map<std::string, Coordinates> cities;

    double computeDistance(NormFunction, const Coordinates&, const Coordinates&);
    const NormFunction retrieveNorm(const int&) const;
};

#endif  // PROXIMITY_CITY_SEARCH_H