#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct Hashtable {
    std::vector<std::string> word;
    std::vector<std::string> status;
};

int search(Hashtable* hash, std::string word) {
    char key = word.back();
    int num = (key - 'a') % 26;
    int originalNum = num;
    int end = (num + 25) % 26;

    if (hash->word[num] != word) {
        while (hash->status[num] != "never used" && num != end) {
            if (hash->status[num] == "occupied" && hash->word[num] == word) {
                return num;
            }
            num = (num + 1) % 26;
        }
    } else {
        return num;
    }

    return -1;
}

void insert(Hashtable* hash, std::string word) {
    int check = search(hash, word);

    if (check != -1) {
        return;
    }

    char key = word.back();
    int num = (key - 'a') % 26;
    int ins = num;

    while (hash->status[ins] == "occupied") {
        ins = (ins + 1) % 26;
    }

    hash->word[ins] = word;
    hash->status[ins] = "occupied";
}

void del(Hashtable* hash, std::string word) {
    int check = search(hash, word);

    if (check == -1) {
        return;
    }

    hash->word[check] = "";
    hash->status[check] = "tombstone";
}

int main() {
    Hashtable test;

    for (int i = 0; i < 26; i++) {
        test.status.push_back("never used");
        test.word.push_back("");
    }

    std::string in;
    std::getline(std::cin, in);
    std::istringstream stream(in);
    std::string com;
    std::vector<std::string> commands;

    while (stream >> com) {
        commands.push_back(com);
    }

    for (int i = 0; i < commands.size(); i++) {
        if (commands[i][0] == 'A') {
            std::string word = commands[i].substr(1);
            insert(&test, word);
        } else if (commands[i][0] == 'D') {
            std::string word = commands[i].substr(1);
            del(&test, word);
        }
    }

    for (int i = 0; i < 26; i++) {
        if (test.status[i] == "occupied") {
            std::cout << test.word[i] << " ";
        }
    }

    std::cout << std::endl;
}