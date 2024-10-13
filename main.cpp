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
    int num = (int)key;
    int check = num;
    int end = num - 1;

    if (hash->word[num] != word) {
        while (hash->status[num] != "never used" && end != check) {
            if (hash->status[num] == "occupied" && hash->word[num] == word) {
                return check;
            }

            if (check == 25) {
                check = -1;
            }

            check++;
        }
    } else if (hash->status[num] == "never used") {
        return -1;
    }
    
    return -1;
}

void insert(Hashtable* hash, std::string word) {
    int check = search(hash, word);

    if (check != -1) {
        return;
    }

    int key = word.back();
    int num = (int)key;
    int ins = num;

    while (hash->status[ins] != "never used" || hash->status[ins] != "tombstone") {
        ins++;
    }

    hash->word[ins] = word;
    hash->status[ins] = "occupied";
}

void del(Hashtable* hash, std::string word) {
    int check = search(hash, word);

    if (check == -1) {
        return;
    }

    int key = word.back();
    int num = (int)key;

    hash->word[check] = "";
    hash->status[check] = "tombstone";
}

int main(void) {
    Hashtable* test;

    for (int i = 0; i < 26; i++) {
        test->status.push_back("never used");
        test->word.push_back("");
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
            insert(test, word);
        } else {
            std::string word = commands[i].substr(1);
            insert(test, word);
        }
    }

    for (int i = 0; i < 26; i++) {
        if (test->word[i] == "") {
            continue;
        }
        std::cout << test->word[i] << "";
    }
}