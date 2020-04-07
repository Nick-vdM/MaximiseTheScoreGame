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

class rustysBall {
    // basically just a pair<int, int*> because
    // the comparator in that case is broken, but
    // we still want to use the state of the ball
public:
    explicit rustysBall(int &val) {
        valuePointer = &val;
        sumOfDigits = getSumOfDigits(val);
    }

    rustysBall &operator=(const int &other) {
        if (*valuePointer == other) return *this;
        *valuePointer = other;
        sumOfDigits = other;
        return *this;
    }

    rustysBall &operator=(const int &&other) {
        if (*valuePointer == other) return *this;
        *valuePointer = other;
        sumOfDigits = other;
        return *this;
    }

    operator int() const { return *valuePointer; }

    int sumOfDigits;
    int *valuePointer;

    // have to override all the comparators
    friend bool operator<(const rustysBall &r1, const rustysBall &r2);

    friend bool operator>(const rustysBall &r1, const rustysBall &r2);

    friend bool operator==(const rustysBall &r1, const int &i);

    // useful for debugging
    friend ostream &operator<<(std::ostream &os, const rustysBall &obj);

    static int getSumOfDigits(int val) {
        int sum = 0;
        while (val != 0) {
            sum += val % 10;
            val /= 10;
        }
        return sum;
    }
};

bool operator<(const rustysBall &r1, const rustysBall &r2) {
    if (r1.sumOfDigits < r2.sumOfDigits) {
        return true;
    }
    if (r1.sumOfDigits > r2.sumOfDigits) {
        return false;
    }
    return *r1.valuePointer < *r2.valuePointer;
}

bool operator>(const rustysBall &r1, const rustysBall &r2) {
    if (r1.sumOfDigits > r2.sumOfDigits) {
        return true;
    }
    if (r1.sumOfDigits < r2.sumOfDigits) {
        return false;
    }
    return *r1.valuePointer > *r2.valuePointer;
}

bool operator==(const rustysBall &r1, const int &i) {
    // allows us to compare it to integers
    return *r1.valuePointer == i;
}

ostream &operator<<(std::ostream &os, const rustysBall &obj) {
    return os << *obj.valuePointer;
}

template<class T>
class priorityQueue {
public:
    priorityQueue() = default; // so empty versions can exist

    // only allow l-value inputData because we need the pointers
    explicit priorityQueue(vector<T> &inputData) {
        data.reserve(inputData.size());
        for (auto &val : inputData) {
            data.push_back(&val);
        }
        for (int i = data.size() / 2 - 1; i >= 0; i--) {
            floatDown(i);
        }
    }

////////////////////////////////////////////////////////////////////////////////

    void insert(T &val) {
        data.push_back(&val);
        floatUp(data.size() - 1);
    }

    int getTop() {
        // in case its empty maxNode will cause sigseg
        if (data.empty()) return 0;
        int top = getMaxNode();
        return static_cast<int>(*data[top]);
    }

    void deleteTop() {
        if (data.empty()) return; // there is nothing to delete
//        printData();
        int top = getMaxNode();
        *data[top] = 0; // set the value to pointer so
        // the other player can't add it
        // replace the top with the bottom
        data[0] = data[data.size() - 1];
        // remove the bottom
        data.erase(data.end() - 1);
        // now re-heapify to get the position right
        floatDown(0);
    }

    void printData() {
//        for (int i = 0; i < data.size(); i += 5){
//            for(int j = i; j < i + 5; j++){
//                cout << *data[j] << " ";
//            }
//            cout << endl;
//        }
        int val = *data[0];
        if (val == 0) val = *data[getMaxChild(0)];
        cout << "\tpopping " << val << endl << "===========" << endl;

    }

private:
    vector<T *> data;

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
        if (left < data.size() && *data[left] == 0) {
            left = getMaxChild(left);
        }
        if (right < data.size() && *data[right] == 0) {
            right = getMaxChild(right);
        }
        // check that both children exist
        if (right >= data.size()) {
            return left;
        }
        if (left >= data.size()) {
            return right;
        }

        // if one of them is zero float it down and return getMaxChild

        // otherwise return the bigger child
        if (*data[left] > *data[right]) {
            return left;
        }
        return right;
    }

    int getMaxNode() {
        if (*data[0] == 0) {
            return getMaxChild(0);
        }
        return 0;
    }

    void floatUp(int index) {
        int parent = getParent(index);
        while (parent >= 0) {
            if (*data[index] > *data[parent]) {
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
            if (*data[index] < *data[maxChildIndex]) {
                swap(data[index], data[maxChildIndex]);
            } else {
                return;
            }
            index = maxChildIndex;
            maxChildIndex = getMaxChild(index);
        }
    }
};


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
        // we will initialise the queues during the game
    }

    void playOut() {
        auto startClock = std::chrono::high_resolution_clock::now();

        // ==================MEASURED TIME=========================
        // every turn takes out a ball so we can use that
        // for the total max turns
        scottsPriorities = priorityQueue<int>(balls);
        auto rustysBalls = getDigitSumPairVector(balls);
        rustysPriorities = priorityQueue<rustysBall>(rustysBalls);
        int turnsTaken = 0;
        while (turnsTaken < balls.size()) {
            for (int i = 0; i < maxTurnsPerRound
                            && turnsTaken < balls.size(); i++) {
                if (scottsTurn) {
//                    cout << "SCOTT" << endl;
                    doScottsTurn();
                    turnsTaken++;
                } else {
//                    cout << "RUSTY" << endl;
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
        std::cout << "Took " << fixed << microseconds / 1000000 << " seconds "
                                                                   "to find "
                  << endl
                  << "\tscott : " << scottsScore
                  << endl
                  << "\trusty : " << rustysScore
                  << endl;
    }

    void outputScoreToFile(string const &location) {
        ofstream ofs(location, std::ios_base::app);
        ofs << scottsScore << " " << rustysScore
            << endl;
    }

private:
    priorityQueue<int> scottsPriorities;
    priorityQueue<rustysBall> rustysPriorities;
    vector<int> balls;

    static istringstream getStringstreamOfLine(ifstream &inputFile) {
        string line;
        getline(inputFile, line);
        return istringstream(line);
    }

    int maxTurnsPerRound;

    bool scottsTurn;

    size_t rustysScore{0};
    size_t scottsScore{0};

    double microseconds{};

    vector<rustysBall> static getDigitSumPairVector(vector<int> &vals) {
        vector<rustysBall> rustysBalls;
        rustysBalls.reserve(vals.size());
        for (auto &v : vals) {
            rustysBalls.emplace_back(v);
        }
        return rustysBalls;
    }


    void doRustysMove() {
        rustysScore += rustysPriorities.getTop();
//        cout << "RUSTY: " << rustysPriorities.getTop()
//             << " sum of digits "
//             << rustysBall::getSumOfDigits(rustysPriorities.getTop())
//             << endl;
        rustysPriorities.deleteTop();
    }

    void doScottsTurn() {
        scottsScore += scottsPriorities.getTop();
//        cout << "SCOTT: " << scottsPriorities.getTop() << endl;
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
    for (int i = 0; i < testCases; i++) {
        // it only read up to the end of the line so we have to ignore
        ifs.ignore(numeric_limits<streamsize>::max(), ifs.widen('\n'));
        match m(ifs);
        m.playOut();

        m.printScores();
        if (argc > 2) {
            // output it to the file as well
            m.outputScoreToFile(argv[2]);
        }
    }
}
