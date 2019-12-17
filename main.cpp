#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;
using namespace std::chrono;
#import "trie.cpp"

trie trie;
int wordCountO = 0;
int wordCountL = 0;
int wordCountS = 0;
int uniqueWords = 0;

void insertToTrie(const vector<string>& fileNames) {
    for (const auto& filename : fileNames) {

        //words from file to vector without puncts
        std::string word;

        std::ifstream file(filename);

        while (file >> word) {
            //don't push separate puncts
            if (!(word.size() == 1 && ispunct(word[0]))) {
                wordCountO++;

                int counterChar = 0;
                for (char ch : word) {
                    counterChar++;
                    if (ispunct(ch)) {
                        word.erase(word.begin() + counterChar - 1);
                    }
                }
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                trie.insert(word);
            }
        }
        file.close();
    }
}

//multithread
//insert to trie words from odd position in argv
void insertToTrieLiche(vector<string> fileNames) {
    int arglen = fileNames.size();

    if (arglen % 2 == 0) {
        arglen -= 1;
    }
    for (int i = 0; i < arglen; i += 2) {

        //words from file to vector without puncts
        std::string word;

        string filename = fileNames[i];
        std::ifstream file(filename);

        while (file >> word) {
            //don't push separate puncts
            if (!(word.size() == 1 && ispunct(word[0]))) {
                wordCountL++;

                int counterChar = 0;
                for (char ch : word) {
                    counterChar++;
                    if (ispunct(ch)) {
                        word.erase(word.begin() + counterChar - 1);
                    }
                }
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                trie.insert(word);
            }
        }
        file.close();
    }
}

//multithread
//insert to trie words from even position in argv
void insertToTrieSude(vector<string> fileNames) {
    int arglen = fileNames.size();

    if (arglen % 2 == 1) {
        arglen -= 1;
    }
    for (int i = 1; i < arglen; i += 2) {

        //words from file to vector without puncts
        std::string word;

        string filename = fileNames[i];
        std::ifstream file(filename);

        while (file >> word) {
            //don't push separate puncts
            if (!(word.size() == 1 && ispunct(word[0]))) {
                wordCountS++;

                int counterChar = 0;
                for (char ch : word) {
                    counterChar++;
                    if (ispunct(ch)) {
                        word.erase(word.begin() + counterChar - 1);
                    }
                }
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                trie.insert(word);
            }
        }
        file.close();
    }
}

//sort vector with pairs by frequency(second in pair)
bool sortbysec(const pair<string, int> &a, const pair<string, int> &b) {
    return (a.second > b.second);
}

void resultWrite(){
    std::ofstream outfile("output.txt");

    vector<pair<string, int> > vect = trie.search_by_prefix("");

    std::sort(vect.begin(), vect.end(), sortbysec);

    for (const pair<string, int>& pair: vect) {
        outfile << pair.first << " -> " << pair.second << '\n';
        uniqueWords++;
    }

}

int main(int argc, char *argv[]) {

    int wordCount = 0;
    //output file
    std::ofstream timeOneTh("timeOne.txt", std::ios_base::app);
    std::ofstream timeTwoTh("timeTwo.txt", std::ios_base::app);

    auto start = high_resolution_clock::now();

    string choose(argv[1]);
    ifstream fileNamesFile(argv[2]);
    string line;
    vector<string> fileNames;

    int fileCounter = 0;
    while (std::getline(fileNamesFile, line)) {
        if (!line.empty()) {
            fileNames.push_back(line);
            fileCounter++;
        }
    }

    if (choose == "-two") {
        cout << "\nTWO-THREAD RUN\n";
        thread th(insertToTrieLiche, fileNames);
        insertToTrieSude(fileNames);
        th.join();
        wordCount = wordCountL + wordCountS;
    } else if (choose == "-one") {
        cout << "\nONE-THREAD RUN\n";
        insertToTrie(fileNames);
        wordCount = wordCountO;
    }else if (choose == "--help") {
        cout<<"\nFirst argument: \"-one\" for onethread run or \"-two\" for twothread run\nSecond argument: filename with file paths\n\n";
        return 1;
    } else {
        cerr << "\nPLEASE WRITE CORRECT THREAD MODE IN FIRST ARGUMENT \n ONE-THREAD RUN: -one \n TWO-THREAD RUN -two\n"
             << endl;
        return 0;
    }

    resultWrite();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "\nTime taken for count word frequency: "
         << duration.count() << " milliseconds for " << wordCount <<
         " words (" << uniqueWords << " unique words)" << endl << endl;

    if (choose == "-two") {
        timeTwoTh << " " << duration.count();
    } else if (choose == "-one") {
        timeOneTh << " " << duration.count();
    }

    timeTwoTh.close();
    timeOneTh.close();

    if (wordCount == 0) {
        cout << "PLEASE CHECK CORRECTNESS OF FILE NAMES\n\n";
    }

    std::ifstream timeOne("timeOne.txt");
    std::ifstream timeTwo("timeTwo.txt");

    int timeone;
    int counterOne = 0;
    int totalTimeOne = 0;
    while (timeOne >> timeone) {
        counterOne++;
        totalTimeOne += timeone;
    }

    if (counterOne != 0) {
        int averageOne = totalTimeOne / counterOne;
        cout << "Average time for one-thread run " << averageOne << " in " << counterOne << " times for " << wordCount
             << " words from " << fileCounter << " files." << endl;
    }

    int timetwo;
    int counterTwo = 0;
    int totalTimeTwo = 0;
    while (timeTwo >> timetwo) {
        counterTwo++;
        totalTimeTwo += timetwo;
    }
    if (counterTwo != 0) {
        int averageTwo = totalTimeTwo / counterTwo;
        cout << "Average time for two-thread run " << averageTwo << " in " << counterTwo << " times for " << wordCount
             << " words from " << fileCounter << " files.\n" << endl;
    }
    trie.~trie();
}

//  g++ -std=c++11 main.cpp -o main