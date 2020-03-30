#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class myPriorityQueue {
public:
    myPriorityQueue() : data{} {}

////////////////////////////////////////////////////////////////////////////////

    void insert(int &val) {
        data.push_back(val);
        floatUp(data.size() - 1, greater<int>());
    }

    template<class T>
    void insert(int &val, T comp) {
        data.push_back(val);
        floatUp(data.size() - 1, comp);
    }

    int getTop() const {
        return data[0];
    }

    void deleteTop() {
        // delete the top with the bottom
        data[0] = data[data.size() - 1];
        // remove the bottom
        data.erase(data.end() - 1);
        // now re-heapify to get the position right
    }

    int size() const {
        return data.size();
    }

private:
    vector<int> data;

    template<class T>
    void floatUp(int index, T comp) {
        while (index / 2 > 0) {
            if (comp(data[index], data[index / 2])) {
                swap(data[index], data[index / 2]);
            }
            index /= 2;
        }
    }
};

class rustysBrain {
public:
    bool operator()(const int &v1, const int &v2) {
        if (sumDigits(v1) > sumDigits(v2)) {
            return true;
        }
        return v1 > v2;
    }

private:
    static int sumDigits(int val) {
        int sum = 0;
        while (val != 0) {
            sum += val % 10;
            val /= 10;
        }
        return sum;
    }
};

class match{
public:
    match(vector<int> balls, int maxTurns){

    }
private:
    vector<int> balls;
    int maxTurns;
};

int main(int argc, char * argv[]) {
    if(argc < 1){
        std::cout << "Error: an input and an output file is required."
                  << std::endl
                  << "Call the program like `program.exe input.txt output.txt`"
                  << std::endl;
    }

}
















