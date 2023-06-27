#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "ProximityCitySearch.h"
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <limits>

const std::string DATA_FILE = "/path/to/data.txt";  // file in resources

/**
 * @brief Check if a line representing a city has a valid format.
 * 
 * @param line The line to validate.
 * @return True if the line is a valid city format, false otherwise.
 */
bool isValidCityLine(const std::string& line) {
    std::regex cityRegex(R"(^[a-zA-Z'\.\s\-(),]+(,\s[a-zA-Z]{2})?$)");
    return std::regex_match(line, cityRegex);
}


/**
 * @brief Check if a line representing coordinates has a valid format.
 * 
 * @param line The line to validate.
 * @return True if the line is a valid coordinates format, false otherwise.
 */
bool isValidCoordinatesLine(const std::string& line) {
    std::regex coordinatesRegex(R"([-+]?([0-9]*\.[0-9]+|[0-9]+)\s*-?\s*[0-9]*\.[0-9]+|[0-9]+)");
    return std::regex_match(line, coordinatesRegex);
}


/**
 * @brief Read the contents of a file and populate the ProximityCitySearch object with city data.
 * 
 * @param filename The path to the file.
 * @param citySearch The ProximityCitySearch object to populate with city data.
 * @throws std::runtime_error if the file fails to open or if the city name or coordinates format is invalid.
 */
void readFile(const std::string& filename, ProximityCitySearch& citySearch) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file");
    }

    std::string line;
    std::string cityName;
    int lineCount = 0;

    while (std::getline(file, line)) {
        lineCount++;
        std::stringstream ss(line);

        if (lineCount % 2 == 1) {
            if (!isValidCityLine(line)) {
                std::cout << line;
                throw std::runtime_error("Invalid city name format");
            }

            if (std::getline(ss, cityName)) {
                cityName.erase(cityName.find_last_not_of("\r\n") + 1);
            }
        } else {
            if (!isValidCoordinatesLine(line)) {
                throw std::runtime_error("Invalid coordinates format");
            }

            double x, y;
            ss >> x;
            ss.ignore(3);
            ss >> y;

            Coordinates cityCoords(x, y);
            citySearch.addCity(cityName, cityCoords);
        }
    }
}

/**
 * @brief Get the name of the selected city from the user.
 * 
 * @return The name of the selected city.
 */
std::string getSelectedCityName() {
    std::string selectedCityName;
    std::cout << "Please enter the selected city name (with a line break after it):\n";
    std::getline(std::cin, selectedCityName);

    if (selectedCityName == "0") {
        return "0";
    }

    while (!isValidCityLine(selectedCityName)) {
        std::cout << "Invalid city name. Please enter the selected city name (with a line break after it):\n";
        std::getline(std::cin, selectedCityName);
    }

    return selectedCityName;
}


/**
 * @brief Get the desired search radius from the user.
 * 
 * @return The desired search radius.
 */
double getRadius() {
    std::cout << "\nPlease enter the desired radius:\n";
    double radius;
    std::cin >> radius;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return radius;
}


/**
 * @brief Get the desired norm type from the user.
 * 
 * @return The desired norm type (0 - L2, 1 - Linf, 2 - L1).
 */
int getNorm() {
    int norm;
    std::cout << "\nPlease enter the desired norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance):\n";
    std::cin >> norm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (norm < 0 || norm > 2) {
        std::cout << "Invalid norm. Please enter the desired norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance):\n";
        std::cin >> norm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return norm;
}

void printSearchResult(const std::string& selectedCityName, int numCitiesInRadius, int numCitiesNorth, const SortedMap& cityData) {
    std::cout << "\nSearch result:\n";
    std::cout << numCitiesInRadius << " city/cities found in the given radius.\n";
    std::cout << numCitiesNorth << " cities are to the north of the selected city.\n";
    std::cout << "City list:\n";
    for (const auto& city : cityData) {
        if (city.second != selectedCityName)
            std::cout << city.second << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    try {
        ProximityCitySearch citySearch;

        // Change the path to the appropriate one
        readFile(DATA_FILE, citySearch);

        while (true) {
            std::string selectedCityName = getSelectedCityName();
            if (selectedCityName == "0") {
                break;
            }

            double radius = getRadius();
            int norm = getNorm();

            const SortedMap& cityData = citySearch.searchProximalCities(selectedCityName, radius, norm);

            int numCitiesInRadius = cityData.size() - 1;
            int numCitiesNorth = citySearch.computeNorthernCities(selectedCityName, cityData);

            printSearchResult(selectedCityName, numCitiesInRadius, numCitiesNorth, cityData);
        }
    } catch (const std::exception& e) {
        std::cout << "\nError: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "\nBye";
    return EXIT_SUCCESS;
}
