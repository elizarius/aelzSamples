#include <iostream>

// State machine handler
class IPSecProcessHandler {
public:
    enum RUNNING_STATE {
        RS_NOTRUNNING = 0,
        RS_STARTING   = 1,
        RS_STARTED    = 2,
        RS_START_FAIL = 3,
        RS_STOPPING   = 4,
        RS_STOPPED    = 5
    };

    IPSecProcessHandler() : state_(RS_NOTRUNNING) {}

    bool setRunningState(RUNNING_STATE newState) {
        if (!isValidTransition(state_, newState)) {
            return false;
        }

        std::cout << "IPSecProcessHandler [old : new state] "
                  << state_ << " : " << newState << std::endl;
        state_ = newState;
        return true;
    }

private:
    RUNNING_STATE state_;

    // Validate transitions based on current state
    bool isValidTransition(RUNNING_STATE from, RUNNING_STATE to) const {
        switch (from) {
            case RS_NOTRUNNING: return to == RS_STARTING;
            case RS_STARTING:   return to == RS_STARTED || to == RS_START_FAIL;
            case RS_STARTED:    return to == RS_START_FAIL || to == RS_STOPPING || to == RS_STOPPED;
            case RS_START_FAIL: return to == RS_NOTRUNNING;
            case RS_STOPPING:   return to == RS_STOPPED;
            case RS_STOPPED:    return to == RS_NOTRUNNING;
        }
        return false;
    }
};

int main() {
    IPSecProcessHandler ph;

    // Test sequence: same as original
    // Expectations:
    //  0:1
    //  1:2
    //  2:3
    //  3:0
    //  0:1
    //  1:2
    //  2:4
    //  4:5

    ph.setRunningState(IPSecProcessHandler::RS_STARTING);
    ph.setRunningState(IPSecProcessHandler::RS_STARTED);
    ph.setRunningState(IPSecProcessHandler::RS_START_FAIL);
    ph.setRunningState(IPSecProcessHandler::RS_NOTRUNNING);
    ph.setRunningState(IPSecProcessHandler::RS_STARTING);
    ph.setRunningState(IPSecProcessHandler::RS_STARTED);
    ph.setRunningState(IPSecProcessHandler::RS_STOPPING);
    ph.setRunningState(IPSecProcessHandler::RS_STOPPED);

    return 0;
}
