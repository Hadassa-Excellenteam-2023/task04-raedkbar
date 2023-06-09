<h1>Proximity City Search</h1>

<p>
The Priority Proximity City Search is a C++ implementation of the STL's containers and algorithms. The program allows the user to add cities with their coordinates to a search data structure and perform proximity-based searches to find cities within a given radius of a specified city. It supports different norm functions for distance computation and can also compute the number of cities located north of a specified city within a given radius.
</p>

<h2>Motivation</h2>

<p>
The exercise's goal is to learn how to implement STL's containers and algorithms in C++.
</p>

<h2>Features</h2>
    <ul>
        <li>Add cities and their coordinates to the search data structure.</li>
        <li>Perform proximity-based searches to find cities within a given radius of a specified city.</li>
        <li>Supports different norm functions (Euclidean, Maximum, and Manhattan) for distance computation.</li>
        <li>Compute the number of cities located north of a specified city within a given radius.</li>
    </ul>

<h2>Containers and Algorithms</h2>
    <p>The Proximity City Search program utilizes the following containers and algorithms from the C++ Standard Library:</p>
    <ul>
        <li><strong>std::unordered_map</strong>: Used to store the mapping of city names to their coordinates.</li>
        <li><strong>std::multimap</strong>: Used as a sorted map to store proximal cities based on their distance from a reference city.</li>
        <li><strong>std::pair</strong>: Used to represent the coordinates of a city.</li>
        <li><strong>std::function</strong>: Used as a function type to represent different norm functions for distance computation.</li>
    </ul>

<h2>Error Handling</h2>
<p>The Proximity City Search program provides error handling for the following scenarios:</p>
<ul>
    <li>If an invalid city name or coordinates are provided when adding a city, an appropriate error message will be generated.</li>
    <li>If an invalid city name is provided during proximity-based searches or computing northern cities, an appropriate error message will be generated.</li>
</ul>

