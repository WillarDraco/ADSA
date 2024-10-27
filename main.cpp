#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <tuple>

class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unionSets(int x, int y) {
        int rX = find(x);
        int rY = find(y);

        if (rX != rY) {
            if (rank[rX] > rank[rY]) {
                parent[rY] = rX;
            } else if (rank[rX] < rank[rY]) {
                parent[rX] = rY;
            } else {
                parent[rY] = rX;
                rank[rX]++;
            }
            return true;
        }
        return false;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

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

int costCalc(std::vector<std::string> country, std::vector<std::string> build, std::vector<std::string> destroy) {
    int cities = country.size();
    std::vector<std::tuple<int, int, int>> toDestroy;
    std::vector<std::tuple<int, int, int>> toBuild;

    for (int i = 0; i < cities; i++) {
        for (int j = i + 1; j < cities; j++) {
            if (country[i][j] == '1') {
                int costD = transformCost(destroy[i][j]);
                toDestroy.emplace_back(costD, i, j);
            } else {
                int bcost = transformCost(build[i][j]);
                toBuild.emplace_back(bcost, i, j);
            }
        }
    }

    std::sort(toDestroy.begin(), toDestroy.end(), std::greater<std::tuple<int, int, int>>());
    std::sort(toBuild.begin(), toBuild.end());

    UnionFind unionFind(cities);
    int totalCost = 0;

    for (const auto& edge : toDestroy) {
        int costD, u, v;
        std::tie(costD, u, v) = edge;
        if (!unionFind.unionSets(u, v)) {
            totalCost += costD;
        }
    }

    for (const auto& edge : toBuild) {
        int bcost, u, v;
        std::tie(bcost, u, v) = edge;
        if (unionFind.unionSets(u, v)) {
            totalCost += bcost;
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
}