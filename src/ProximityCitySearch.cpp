#include "ProximityCitySearch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>

ProximityCitySearch::ProximityCitySearch() {}

/**
 * @brief Adds a city with its coordinates to the search data structure.
 *
 * @param cityName The name of the city.
 * @param cityCoordinates The coordinates of the city (latitude and longitude).
 */
void ProximityCitySearch::addCity(std::string cityName, Coordinates cityCoordinates) {
    cities.emplace(cityName, cityCoordinates);
}

/**
 * @brief Computes the distance between two sets of coordinates using a specified norm function.
 *
 * @param norm The norm function used to compute the distance.
 * @param coord1 The first set of coordinates.
 * @param coord2 The second set of coordinates.
 * @return The distance between the two sets of coordinates.
 */
double ProximityCitySearch::computeDistance(NormFunction norm, const Coordinates& coord1, const Coordinates& coord2) {
    double xDiff = coord1.first - coord2.first;
    double yDiff = coord1.second - coord2.second;
    return norm(xDiff, yDiff);
}

/**
 * @brief Searches for cities within a given radius of a specified city.
 *
 * @param city The name of the city to search around.
 * @param radius The radius within which to search for cities.
 * @param normType The type of norm function to use for distance computation.
 * @return A sorted map of proximal cities, where the key is the distance from the specified city and the value is the city name.
 */
SortedMap ProximityCitySearch::searchProximalCities(const std::string& city, double radius, int normType) {
    SortedMap proximalCities;

    for (const auto& cityData : cities) {
        const std::string& cityName = cityData.first;
        const Coordinates& cityCoords = cityData.second;

        // Skip the specified city
        // if (cityName == city) {
        //     continue;
        // }

        double distance = computeDistance(retrieveNorm(normType), cities[city], cityCoords);

        if (distance <= radius) {
            proximalCities.emplace(distance, cityName);
        }
    }

    return proximalCities;
}

/**
 * @brief Computes the number of cities in the sorted map that are located north of the specified city.
 *
 * @param city The name of the city to compare against.
 * @param citiesInRadius The sorted map of cities within a specified radius.
 * @return The number of cities north of the specified city.
 */
long long ProximityCitySearch::computeNorthernCities(const std::string& city, const SortedMap& citiesInRadius) {
    auto it = citiesInRadius.begin();

    long long northernCitiesCounter = 0;
    if (it != citiesInRadius.end()) {
        for (++it; it != citiesInRadius.end(); ++it) {
            northernCitiesCounter += (cities.at(city).second > cities.at(it->second).second);
        }
    }

    return northernCitiesCounter;
}

/**
 * @brief Returns a copy of the internal map of cities and their coordinates.
 *
 * @return A map containing the cities and their coordinates.
 */
const std::map<std::string, Coordinates> ProximityCitySearch::getCitiesMap() const {
    return cities;
}

/**
 * @brief Retrieves the norm function based on the specified type.
 *
 * @param type The type of norm function to retrieve.
 * @return The norm function.
 */
const NormFunction ProximityCitySearch::retrieveNorm(const int& type) const {
    std::map<int, NormFunction> norms{
        { 0, [](double x, double y) { return std::hypot(x, y); } },                // Euclidean norm
        { 1, [](double x, double y) { return std::max(std::abs(x), std::abs(y)); } },  // Maximum norm
        { 2, [](double x, double y) { return std::abs(x) + std::abs(y); } }         // Manhattan norm
    };

    return norms[type];
}
