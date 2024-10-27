#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void inputToString (std::string input, std::vector<std::string> &country, std::vector<std::string> &build, std::vector<std::string> &destroy) {
    int firstSpace = input.find(' ');
    int secondSpace = input.find(' ', firstSpace + 1);
    
    std::string countryString = input.substr(0, firstSpace);
    std::string buildString = input.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    std::string destroyString = input.substr(secondSpace + 1);
    
    country = split(countryString, ',');
    build = split(buildString, ',');
    destroy = split(destroyString, ',');
}

int transformCost(char toTrans) {
    if ('A' <= toTrans && toTrans <= 'Z') {
        return toTrans - 'A';
    } else if ('a' <= toTrans && toTrans <= 'z') {
        return toTrans - 'a' + 26;
    }
    return 0;
}

int costCalc (std::vector<std::string> country, std::vector<std::string> build, std::vector<std::string> destroy) {
    int cities = country.size();
    std::vector<std::vector<std::pair<int, std::pair<int, std::string>>>> adjacencyList(cities);

    for (int i = 0; i < cities; i++) {
        for (int j = i + 1; j < cities; j++) {
            if (country[i][j] == '1') {
                int cost = transformCost(destroy[i][j]);
                adjacencyList[i].push_back({cost, {j, "destroy"}});
                adjacencyList[j].push_back({cost, {i, "destroy"}});
            } else {
                int cost = transformCost(build[i][j]);
                adjacencyList[i].push_back({cost, {j, "build"}});
                adjacencyList[j].push_back({cost, {i, "build"}});
            }
        }
    }

    int totalCost = 0;
    std::unordered_set<int> visited;
    std::priority_queue<std::pair<int, std::pair<int, std::string>>, 
                        std::vector<std::pair<int, std::pair<int, std::string>>>, 
                        std::greater<std::pair<int, std::pair<int, std::string>>>> heap;

    heap.push({0, {0, "none"}});

    while (!heap.empty() && visited.size() < cities) {
        auto top = heap.top();
        heap.pop();
        int cost = top.first;
        int current = top.second.first;
        std::string action = top.second.second;

        if (visited.find(current) != visited.end()) {
            continue;
        }

        visited.insert(current);

        if (action == "build" || action == "destroy") {
            totalCost += cost;
        }

        for (auto& neighbour : adjacencyList[current]) {
            int neighbourCost = neighbour.first;
            int neighbourCity = neighbour.second.first;
            std::string neighbourAction = neighbour.second.second;

            if (visited.find(neighbourCity) == visited.end()) {
                heap.push({neighbourCost, {neighbourCity, neighbourAction}});
            }
        }
    }
    return totalCost;
}

int main() {
    std::string input;
    getline(std::cin, input);

    std::vector<std::string> country, build, destroy;
    inputToString(input, country, build, destroy);

    int minCost = costCalc(country, build, destroy);
    std::cout << minCost << std::endl;

    return 0;
}