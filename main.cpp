#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;

class AdjacencyList {
private:
    map<int, vector<pair<string, vector<string>>>> graph;
public:
    void insert(int year, string name, vector<string> genre);
    void printAll();
    vector<int> timeSpan();
    vector<string> movieGenre();
    vector<string> findYear(int year);
    vector<string> findGenre(string genre);
    map<int, pair<string, vector<string>>> findName(string name);
    void printTimeSpan();
    void print(vector<string> temp);
    void printFindName(map<int, pair<string, vector<string>>> nameList);
};

void AdjacencyList::insert(int year, string name, vector<string> genre) {
    for (int i = 0; i < genre.size(); i++) {
        if (!graph.count(year)) {
            vector<string> temp;
            temp.push_back(name);
            graph[year].push_back(make_pair(genre[i], temp));
        }
        else {
            bool genreFound = false;
            int genreLoc;
            for (int j = 0; j < graph[year].size(); j++) {
                if (graph[year][j].first == genre[i]) {
                    genreFound = true;
                    genreLoc = j;
                }
            }
            if (genreFound) {
                graph[year][genreLoc].second.push_back(name);
            }
            else {
                vector<string> temp;
                temp.push_back(name);
                graph[year].push_back(make_pair(genre[i], temp));
            }
        }
    }
}

void AdjacencyList::printAll() {
    for (auto i = graph.begin(); i != graph.end(); i++) {
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            for (auto k = j->second.begin(); k != j->second.end(); k++) {
                cout << i->first << "   " << j->first << "   " << *k << endl;
            }
        }
    }
}

vector<int> AdjacencyList::timeSpan() {
    vector<int> temp;
    for (auto i = graph.begin(); i != graph.end(); i++) {
        temp.push_back(i->first);
    }
    return temp;
}

vector<string> AdjacencyList::movieGenre() {
    vector<string> temp;
    set<string> temp1;
    for (auto i = graph.begin(); i != graph.end(); i++) {
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            temp1.insert(j->first);
        }
    }
    for (auto i = temp1.begin(); i != temp1.end(); i++) {
        temp.push_back(*i);
    }
    return temp;
}

vector<string> AdjacencyList::findYear(int year) {
    vector<string> temp;
    set<string> nameSet;

    if (graph.count(year)) {
        for (auto i = graph[year].begin(); i != graph[year].end(); i++) {
            for(auto j = i->second.begin(); j != i->second.end(); j++) {
                nameSet.insert(*j);
            }
        }
        for (auto i = nameSet.begin(); i != nameSet.end(); i++) {
            temp.push_back(*i);
        }
        return temp;
    }
    temp.push_back("Year Not Found");
    return temp;
}

vector<string> AdjacencyList::findGenre(string genre) {
    vector<string> temp;
    set<string> nameSet;
    bool genreFound = false;

    for (auto i = graph.begin(); i != graph.end(); i++) {
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            if (j->first == genre) {
                genreFound = true;
                for (auto k = j->second.begin(); k != j->second.end(); k++) {
                    nameSet.insert(*k);
                }
            }
        }
    }

    if (genreFound) {
        for (auto i = nameSet.begin(); i != nameSet.end(); i++) {
            temp.push_back(*i);
        }
        return temp;
    }
    temp.push_back("Genre Not Found");
    return temp;
}

map<int, pair<string, vector<string>>> AdjacencyList::  findName(string name) {
    map<int, pair<string, vector<string>>> nameList;
    bool nameFound = false;

    for (auto i = graph.begin(); i != graph.end(); i++) {
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            for (auto k = j->second.begin(); k != j->second.end(); k++) {
                if (*k == name) {
                    nameFound = true;

                    if (nameList[i->first].first != name) {
                        vector<string> temp;
                        temp.push_back(j->first);
                        nameList[i->first] = make_pair(name, temp);
                    }
                    else {
                        nameList[i->first].second.push_back(j->first);
                    }
                }
            }
        }
    }

    if (nameFound) {
        return nameList;
    }
    else {
        map<int, pair<string, vector<string>>> notFound;
        vector<string> temp;
        notFound[-1] = make_pair("Name Not Found", temp);
        return notFound;
    }
}

void AdjacencyList::printTimeSpan() {
    vector<int> temp = timeSpan();
    for (int i = 0; i < temp.size() - 1; i++) {
        cout << temp[i] << '|';
    }
    cout << temp.back() << endl;
}

void AdjacencyList::print(vector<string> temp) {
    for (int i = 0; i < temp.size() - 1; i++) {
        cout << temp[i] << '|';
    }
    cout << temp.back() << endl;
}

void AdjacencyList::printFindName(map<int, pair<string, vector<string>>> nameList) {
    if (nameList.count(-1)) {
        cout << "Name Not Found" << endl;
    }
    else {
        for (auto i = nameList.begin(); i != nameList.end(); i++) {
            cout << i->first << "   " << i->second.first << "   ";
            for (int j = 0; j < i->second.second.size() - 1; j++) {
                cout << i->second.second[j] << '|';
            }
            cout << i->second.second.back() << endl;
        }
    }
}

class AdjacencyMatrix {
private:
    vector<string> graph[140][29];
    map<string, int> label;
    map<int, string> reverseLabel;
    int labelCount;
public:
    AdjacencyMatrix();
    void insert(int year, string name, vector<string> genre);
    void printAll();
    vector<int> timeSpan();
    vector<string> movieGenre();
    vector<string> findYear(int year);
    vector<string> findGenre(string genre);
    map<int, pair<string, vector<string>>> findName(string name);
    void printTimeSpan();
    void print(vector<string> temp);
    void printFindName(map<int, pair<string, vector<string>>> nameList);
};

AdjacencyMatrix::AdjacencyMatrix() {
    labelCount = 0;
    vector<string> temp;
    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 29; j++) {
            graph[i][j] = temp;
        }
    }
}

void AdjacencyMatrix::insert(int year, string name, vector<string> genre) {
    int yearTemp;
    if (year == 0) {
        yearTemp = 0;
    }
    else {
        yearTemp = year - 1890;
    }

    for (int i = 0; i < genre.size(); i++) {
        if (!label.count(genre[i])) {
            label[genre[i]] = labelCount;
            reverseLabel[labelCount++] = genre[i];
        }
        graph[yearTemp][label[genre[i]]].push_back(name);
    }
}

void AdjacencyMatrix::printAll() {
    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 29; j++) {
            if (!graph[i][j].empty()) {
                for (int k = 0; k < graph[i][j].size(); k++) {
                    if (i == 0) {
                        cout << "Unknown Year" << "   ";
                    }
                    else {
                        cout << i + 1890 << "   ";
                    }
                    cout << reverseLabel[j] << "   " << graph[i][j][k] << endl;
                }
            }
        }
    }
}

vector<int> AdjacencyMatrix::timeSpan() {
    vector<int> temp;
    for (int i = 0; i < 140; i++) {
        bool yearExist = false;
        for (int j = 0; j < 29; j++) {
            if (!graph[i][j].empty()) {
                yearExist = true;
            }
        }
        if (yearExist) {
            temp.push_back(i + 1890);
        }
    }
    return temp;
}

vector<string> AdjacencyMatrix::movieGenre() {
    vector<string> temp;
    for (int i = 0; i < 29; i++) {
        bool genreExist = false;
        for (int j = 0; j < 140; j++) {
            if (!graph[j][i].empty()) {
                genreExist = true;
            }
        }
        if (genreExist) {
            temp.push_back(reverseLabel[i]);
        }
    }
    return temp;
}

vector<string> AdjacencyMatrix::findYear(int year) {
    vector<string> temp;
    set<string> nameSet;

    for (int i = 0; i < 29; i++) {
        if (!graph[year - 1890][i].empty()) {
            for (int j = 0; j < graph[year - 1890][i].size(); j++) {
                nameSet.insert(graph[year - 1890][i][j]);
            }
        }
    }

    for (auto i = nameSet.begin(); i != nameSet.end(); i++) {
        temp.push_back(*i);
    }

    if (temp.empty()) {
        temp.push_back("Year Not Found");
    }

    return temp;
}

vector<string> AdjacencyMatrix::findGenre(string genre) {
    vector<string> temp;
    set<string> nameSet;

    if (!label.count(genre)) {
        temp.push_back("Genre Not Found");
        return temp;
    }

    for (int i = 0; i < 140; i++) {
        if (!graph[i][label[genre]].empty()) {
            for (int j = 0; j < graph[i][label[genre]].size(); j++) {
                nameSet.insert(graph[i][label[genre]][j]);
            }
        }
    }

    for (auto i = nameSet.begin(); i != nameSet.end(); i++) {
        temp.push_back(*i);
    }
    return temp;
}

map<int, pair<string, vector<string>>> AdjacencyMatrix::findName(string name) {
    map<int, pair<string, vector<string>>> nameList;
    bool nameFound = false;

    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 29; j++) {
            for (int k = 0; k < graph[i][j].size(); k++) {
                if (graph[i][j][k] == name) {
                    nameFound = true;
                    int temp;

                    if (i == 0) {
                        temp = 0;
                    }
                    else {
                        temp = i + 1890;
                    }

                    if (nameList[temp].first != name) {
                        vector<string> one;
                        one.push_back(reverseLabel[j]);
                        nameList[temp] = make_pair(name, one);
                    }
                    else {
                        nameList[temp].second.push_back(reverseLabel[j]);
                    }
                }
            }
        }
    }

    if (nameFound) {
        return nameList;
    }
    else {
        map<int, pair<string, vector<string>>> notFound;
        vector<string> temp;
        notFound[-1] = make_pair("Name Not Found", temp);
        return notFound;
    }
}

void AdjacencyMatrix::printTimeSpan() {
    vector<int> temp = timeSpan();
    for (int i = 0; i < temp.size() - 1; i++) {
        cout << temp[i] << '|';
    }
    cout << temp.back() << endl;
}

void AdjacencyMatrix::print(vector<string> temp) {
    for (int i = 0; i < temp.size() - 1; i++) {
        cout << temp[i] << '|';
    }
    cout << temp.back() << endl;
}

void AdjacencyMatrix::printFindName(map<int, pair<string, vector<string>>> nameList) {
    if (nameList.count(-1)) {
        cout << "Name Not Found" << endl;
    }
    else {
        for (auto i = nameList.begin(); i != nameList.end(); i++) {
            cout << i->first << "   " << i->second.first << "   ";
            for (int j = 0; j < i->second.second.size() - 1; j++) {
                cout << i->second.second[j] << '|';
            }
            cout << i->second.second.back() << endl;
        }
    }
}

int main() {
    ifstream infile("C:/Users/jacw4/CLionProjects/Project3/text.txt");
    AdjacencyList list;
    AdjacencyMatrix matrix;
    string line, id, name, type, year, temp;
    int time;
    getline(infile, temp);

    while (getline(infile, line)) {
        vector<string> genre;
        stringstream ss(line);

        getline(ss, id, '\t');
        getline(ss, temp, '\t');
        getline(ss, name, '\t');
        getline(ss, temp, '\t');
        getline(ss, temp, '\t');
        getline(ss, year, '\t');
        getline(ss, temp, '\t');
        getline(ss, temp, '\t');
        getline(ss, type);

        id = id.substr(2,7);
        if (year == "\\N") {
            time = 0000;
        }
        else {
            time = stoi(year);
        }

        stringstream gen(type);
        while (getline(gen, temp, ',')) {
            if (temp == "\\N") {
                temp = "Unclassified";
            }
            genre.push_back(temp);
        }

        list.insert(time, name, genre);
        matrix.insert(time, name, genre);
    }

    list.printTimeSpan();
    list.print(list.movieGenre());
    list.print(list.findYear(2014));
//    list.print(list.findGenre("Comedy"));
    list.printFindName(list.findName("Miss Jerry"));
//    matrix.printTimeSpan();
//    matrix.print(matrix.movieGenre());
//    matrix.print(matrix.findYear(1894));
//    matrix.print(matrix.findGenre("Comedy"));
//    matrix.printFindName(matrix.findName("Miss Jerry"));
}

