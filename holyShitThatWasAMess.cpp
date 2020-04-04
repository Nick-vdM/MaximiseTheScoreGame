//
// Created by nicol on 4/04/2020.
// https://www.linkedin.com/in/nick-vd-merwe/
// nick.jvdmerwe@gmail.com
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include<unordered_map>

using namespace std;

struct scottsBrain {
    scottsBrain() {}

    scottsBrain(vector<int> &data) {}

    bool greater(int &v1, int &v2) {
        return v1 > v2;
    }

    bool less(int &v1, int &v2) {
        return v1 < v2;
    }
};

struct rustysBrain {
    rustysBrain() = default;

    rustysBrain(vector<int> &data) {
        for (auto &val : data) {
            sumOfDigits[val] = sumDigits(val);
        }
    }

    bool greater(int &v1, int &v2) {
        // compare digits
        if (sumOfDigits[v1] > sumOfDigits[v2]) {
            return true;
        }
        if (sumOfDigits[v1] < sumOfDigits[v2]) {
            return false;
        }
        // in the case they're equal return the larger one
        return v1 > v2;
    }

    bool less(int &v1, int &v2) {
        // compare digits
        if (sumOfDigits[v1] < sumOfDigits[v2]) {
            return true;
        }
        if (sumOfDigits[v1] > sumOfDigits[v2]) {
            return false;
        }
        // in the case they're equal return the larger one
        return v1 < v2;
    }

    // stores the sum of digits of each pointer
    unordered_map<int, int> sumOfDigits;

    int sumDigits(int val) {
        int sum = 0;
        while (val != 0) {
            sum += val % 10;
            val /= 10;
        }
        return sum;
    }
};

template<class comparator>
class priorityQueue {
public:
    priorityQueue() {} // so empty versions can exist

    explicit priorityQueue(comparator const &compare)
            : data{}, compare(compare) {}

    explicit priorityQueue(comparator const &&compare)
            : data{}, compare(compare) {}

    // only allow l-value inputData because we need the pointers
    priorityQueue(vector<int> &inputData, comparator &&compare)
            : compare(compare) {
        data.reserve(inputData.size());
        for (auto &val : inputData) {
            insert(val);
        }
    }

    priorityQueue(vector<int> &inputData, comparator &compare)
            : compare(compare) {
        data.reserve(inputData.size());
        for (auto &val : inputData) {
            insert(val);
        }
    }
////////////////////////////////////////////////////////////////////////////////

    void insert(int &val) {
        data.push_back(&val);
        floatUp(data.size() - 1);
    }

    int getTop() {
        if (*data[0] == 0) deleteTop();
        if (data.empty()) return 0; // its empty now and using
        // zero won't change scores
        return *data[0];
    }

    void deleteTop() {
        if (data.empty()) return; // there is nothing to delete
        *data[0] = 0; // set the value to pointer so
        // the other player can't add it

        // replace the top with the bottom
        data[0] = data[data.size() - 1];
        // remove the bottom
        data.erase(data.end() - 1);
        // now re-heapify to get the position right
        floatDown(0);
    }

    void printData() {
        for (auto &v : data) {
            cout << *v << endl;
        }
    }

protected:
    vector<int *> data;
    comparator compare;

    // change these into functions to improve readability
    // since our vector's index starts at 0 these formulas are slightly
    // different to normal
    static int getLeftChild(int parent) {
        return parent * 2 + 1;
    }

    static int getRightChild(int parent) {
        return parent * 2 + 2;
    }

    static int getParent(int child) {
        // swap back to index starts at one, go to parent in that form,
        // swap back
        return (child + 1) / 2 - 1;
    }

    int getMaxChild(int index) {
        int left = getLeftChild(index);
        int right = getRightChild(index);
        // check that both children exist
        if (right >= data.size()) {
            return left;
        }
        // otherwise return the bigger child
        if (compare.greater(*data[left], *data[right])) {
            return left;
        }
        return right;
    }

    void floatUp(int index) {
        int parent = getParent(index);
        while (parent >= 0) {
            if (compare.greater(*data[index], *data[parent])) {
                swap(data[index], data[parent]);
            } else {
                return; // position was found
            }
            index = parent;
            parent = getParent(index);
        }
    }

    void floatDown(int index) {
        int maxChildIndex = getMaxChild(index);
        // while there still are children
        while (maxChildIndex < data.size()) {
            if (compare.less(*data[index], *data[maxChildIndex])) {
                swap(data[index], data[maxChildIndex]);
            } else {
                return; // position was found
            }
            index = maxChildIndex;
            maxChildIndex = getMaxChild(index);
        }
    }
};

istringstream getStringstreamOfLine(ifstream &inputFile) {
    string line;
    getline(inputFile, line);
    return istringstream(line);
}

class match {
public:
    match(ifstream &inputFile) {
        int numberOfBalls; // just store this locally
        auto iss = getStringstreamOfLine(inputFile);
        iss >> numberOfBalls >> maxTurnsPerRound;

        iss = getStringstreamOfLine(inputFile);
        balls.reserve(numberOfBalls);

        int ball;
        for (int j = 0; j < numberOfBalls; j++) {
            iss >> ball;
            balls.push_back(ball);
        }

        string coin = "";
        inputFile >> coin;
        scottsTurn = (coin == "HEADS");

        scottsPriorities = priorityQueue<scottsBrain>(
                balls, scottsBrain());
        rustysPriorities = priorityQueue<rustysBrain>(
                balls, rustysBrain(balls));
    }

    void playOut() {
        auto startClock = std::chrono::high_resolution_clock::now();

        // ==================MEASURED TIME=========================
        // every turn takes out a ball so we can use that
        // for the total max turns
        int turnsTaken = 0;
        while (turnsTaken < balls.size()) {
            for (int i = 0; i < maxTurnsPerRound
                            && turnsTaken < balls.size(); i++) {
                if (scottsTurn) {
                    doScottsTurn();
                    turnsTaken++;
                } else {
                    doRustysMove();
                    turnsTaken++;
                }
            }
            // flip flop
            scottsTurn = !scottsTurn;
        }
        // ========================================================
        auto endClock = std::chrono::high_resolution_clock::now();
        microseconds =
                std::chrono::duration_cast<std::chrono::microseconds>
                        (endClock - startClock).count();
    }

    void printScores() {
        std::cout << "Took " << microseconds / 1000000 << " seconds to find "
                  << endl
                  << "\tscott : " << scottsScore
                  << endl
                  << "\trusty : " << rustysScore;
    }

    void outputScoreToFile(string const &location) {
        ofstream ofs(location, std::ios_base::app);
        ofs << scottsScore << " " << rustysScore
            << endl;
    }

private:
    priorityQueue<scottsBrain> scottsPriorities;
    priorityQueue<rustysBrain> rustysPriorities;
    vector<int> balls;

    int maxTurnsPerRound;

    bool scottsTurn;

    size_t rustysScore{0};
    size_t scottsScore{0};

    double microseconds{};

    void doRustysMove() {
        rustysScore += rustysPriorities.getTop();
        rustysPriorities.deleteTop();
    }

    void doScottsTurn() {
        scottsScore += scottsPriorities.getTop();
        scottsPriorities.deleteTop();
    }
};

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Error: an input and an output file is required."
                  << std::endl
                  << "Call the program like `program.exe input.txt output.txt`"
                  << std::endl
                  << "or `program.exe input.txt`"
                  << std::endl;
    }

    int testCases;
    ifstream ifs(argv[1]);
    ifs >> testCases;
    // it only read up to the end of the line so we have to ignore
    ifs.ignore(numeric_limits<streamsize>::max(), ifs.widen('\n'));
    for (int i = 0; i < testCases; i++) {
        match m(ifs);
        m.playOut();

        m.printScores();
        if (argc > 2) {
            // output it to the file as well
            m.outputScoreToFile(argv[2]);
        }
    }
}
