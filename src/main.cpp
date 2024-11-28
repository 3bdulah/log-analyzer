#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class CustomHashTable {
private:
    struct Entry {
        string filename;
        int visits;
    };

    vector < list < Entry >> table;
    size_t size;

    size_t hashFunction(const string& key) const {
        const size_t prime = 31;
        size_t hash = 0;

        for (char c : key) {
            hash = (hash * prime) + static_cast<size_t>(c);
        }

        return hash % size;
    }

public:
    CustomHashTable(size_t tableSize) : size(tableSize), table(tableSize) {}

    void insert(const string& filename) {
        size_t index = hashFunction(filename) % size;
        auto& bucket = table[index];

        auto it = find_if(bucket.begin(), bucket.end(),
                          [&](const Entry& entry) { return entry.filename == filename; });

        if (it != bucket.end()) {
            it->visits++;
        }
        else {
            bucket.push_back({ filename, 1 });
        }
    }

    void printTopVisitedPages(int topN) const {
        vector < pair < string, int >> allPages;

        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                allPages.emplace_back(entry.filename, entry.visits);
            }
        }

        sort(allPages.begin(), allPages.end(),
             [](const auto& a, const auto& b) {
                 return a.second > b.second;
             });

        cout << "Top " << topN << " most visited web pages:" << endl;

        for (int i = 0; i < min(topN, static_cast<int>(allPages.size())); ++i) {
            cout << allPages[i].first << " " << allPages[i].second << " of total visits " << endl;
        }
    }
};

class WebLogAnalyzer {
private:
    CustomHashTable customHashTable;
    unordered_map < string, int > unorderedMap;

public:
    WebLogAnalyzer(size_t tableSize) : customHashTable(tableSize) {}

    void processLogFileCustom(const string& filePath) {
        ifstream logFile(filePath);

        if (!logFile.is_open()) {
            cerr << "Error opening file: " << filePath << endl;
            return;
        }

        string line;
        while (getline(logFile, line)) {
            string filename = extractFilename(line);
            if (!filename.empty()) {
                customHashTable.insert(filename);
            }
        }

        logFile.close();
    }

    void processLogFileUnorderedMap(const string& filePath) {
        ifstream logFile(filePath);

        if (!logFile.is_open()) {
            cerr << "Error opening file: " << filePath << endl;
            return;
        }

        string line;
        while (getline(logFile, line)) {
            string filename = extractFilename(line);
            if (!filename.empty()) {
                unorderedMap[filename]++;
            }
        }

        logFile.close();
    }

    void printTopVisitedPagesCustom(int topN) const {
        customHashTable.printTopVisitedPages(topN);
    }

    void printTopVisitedPagesUnorderedMap(int topN) const {
        vector < pair < string, int >> allPages(unorderedMap.begin(), unorderedMap.end());

        sort(allPages.begin(), allPages.end(),
             [](const auto& a, const auto& b) {
                 return a.second > b.second;
             });

        cout << "Top " << topN << " most visited web pages using unordered_map:" << endl;

        for (int i = 0; i < min(topN, static_cast<int>(allPages.size())); ++i) {
            cout << allPages[i].first << " " << allPages[i].second << " of total visits " << endl;
        }
    }

    string extractFilename(const string& line) const {
        size_t startPos = line.find("\"GET ") + 5;
        size_t endPos = line.find(" HTTP/");

        if (startPos != string::npos && endPos != string::npos) {
            return line.substr(startPos, endPos - startPos);
        }

        return "";
    }
};

int main() {
    const string filePath = "logs/access_log";
    const size_t tableSize = 100;

    WebLogAnalyzer webLogAnalyzer(tableSize);

    clock_t start = clock();
    webLogAnalyzer.processLogFileCustom(filePath);
    webLogAnalyzer.printTopVisitedPagesCustom(10);
    clock_t end = clock();
    double elapsed_seconds = double(end - start) / CLOCKS_PER_SEC;
    cout << "\nTotal Elapsed Time for Custom Hash Table: " << elapsed_seconds << " seconds" << "\n" << endl;

    start = clock();
    webLogAnalyzer.processLogFileUnorderedMap(filePath);
    webLogAnalyzer.printTopVisitedPagesUnorderedMap(10);
    end = clock();
    double elapsed_seconds2 = double(end - start) / CLOCKS_PER_SEC;
    cout << "\nTotal Elapsed Time By Using Unordered_map : " << elapsed_seconds2 << " seconds" << "\n" << endl;

    return 0;
}