//
// Created by nicol on 4/04/2020.
// https://www.linkedin.com/in/nick-vd-merwe/
// nick.jvdmerwe@gmail.com
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct sumOfDigits {
    bool operator()(int const &v1, int const &v2) {
        if(digits(v1) == digits(v2)){
            return digits(v1) < digits(v2);
        }
        if (digits(v1) < digits(v2)) {
            return true;
        }
        if (digits(v1) > digits(v2)) {
            return false;
        }
    }

    static int digits(int val) {
        int sum = 0;
        while (val != 0) {
            sum += val % 10;
            val /= 10;
        }
        return sum;
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
        int turnsTaken = 0;
        int maxTurns = balls.size();
        while (turnsTaken < maxTurns) {
            for (int i = 0; i < maxTurnsPerRound
                            && turnsTaken < maxTurns; i++) {
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
    }

    void printScores() {
        cout << "\tscott : " << scottsScore
             << endl
             << "\trusty : " << rustysScore
             << endl << endl;
    }

    void outputScoreToFile(string const &location) {
        ofstream ofs(location, std::ios_base::app);
        ofs << scottsScore << " " << rustysScore
            << endl;
    }

private:
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

    void doRustysMove() {
        rustysScore += *max_element(balls.begin(), balls.end(), sumOfDigits());
        cout << "RUSTY: " << *max_element(balls.begin(), balls.end(), sumOfDigits())
        << " sum of digits " << sumOfDigits::digits(*max_element(balls.begin(), balls.end(), sumOfDigits()))
        << endl;
        balls.erase(max_element(balls.begin(), balls.end(), sumOfDigits()));
    }

    void doScottsTurn() {
        scottsScore += *max_element(balls.begin(), balls.end());
        cout << "SCOTT: " << *max_element(balls.begin(), balls.end())
             << endl;
        balls.erase(max_element(balls.begin(), balls.end()));
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
