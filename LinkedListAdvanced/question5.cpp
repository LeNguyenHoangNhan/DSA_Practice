#include <iostream>
#include <list>
using std::list;
using std::cout;

class DataLog {
private:
    list<int> logList;
    list<int>::iterator currentState;

public:
    DataLog();
    DataLog(const int &data);
    void addCurrentState(int number);
    void subtractCurrentState(int number);
    void save();
    void undo();
    void redo();

    int getCurrentStateData() {
        return *currentState;
    }

    void printLog() {
        for (auto i = logList.begin(); i != logList.end(); i++) {
            if (i == currentState) cout << "Current state: ";
            cout << "[ " << *i << " ] => ";
        }
        cout << "END_LOG";
    }
};

DataLog::DataLog() {
    /*
     * TODO:  add the first state with 0
     */
    logList.emplace_back(0);
    currentState = logList.begin();
}

DataLog::DataLog(const int &data) {
    /*
     * TODO:  add the first state with data
     */
    logList.push_back(data);
    currentState = logList.begin();
}

void DataLog::addCurrentState(int number) {
    /*
     * TODO: Increase the value of current state by number
     */
    *currentState += number;
}

void DataLog::subtractCurrentState(int number) {
    /*
     * TODO: Decrease the value of current state by number
     */
    *currentState -= number;
}

void DataLog::save() {
    /*
     * TODO: This function will create a new state, copy the data of the currentState
     *       and move the currentState Iterator to this new state. If there are other states behind the 
     *       currentState Iterator, we delete them all before creating a new state.
     */
    for (auto iter = --(logList.end()); iter != currentState;) {
        logList.erase(iter--);
    }
    logList.push_back(*currentState);
    ++currentState;
}

void DataLog::undo() {
    /*
     * TODO: Switch to the previous state of the data
     *       If this is the oldest state in the log, nothing changes
     */
    if (currentState == logList.cbegin()) {
        return;
    }
    --currentState;
}

void DataLog::redo() {
    /*
     * TODO: Switch to the latter state of the data
     *       If this is the latest state in the log, nothing changes
     */
    if (currentState == (--logList.cend())) {
        return;
    }
    ++currentState;
}

int main() {
    DataLog log(10);
    log.save();
    log.addCurrentState(15);
    log.save();
    log.addCurrentState(15);
    log.undo();
    log.printLog();
}
