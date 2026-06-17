#include <iostream>
#include <variant>

// Forward declarations for all state types
struct NotRunning;
struct Starting;
struct Started;
struct StartFail;
struct Stopping;
struct Stopped;

// Union of all possible states using std::variant
using State = std::variant<NotRunning, Starting, Started, StartFail, Stopping, Stopped>;

// State definitions - each state is a simple type
struct NotRunning {};
struct Starting {};
struct Started {};
struct StartFail {};
struct Stopping {};
struct Stopped {};

// State machine handler
class IPSecProcessHandler {
public:
    enum RUNNING_STATUS {
        RS_NOTRUNNING = 0,
        RS_STARTING   = 1,
        RS_STARTED    = 2,
        RS_START_FAIL = 3,
        RS_STOPPING   = 4,
        RS_STOPPED    = 5
    };

    IPSecProcessHandler() : state_(NotRunning()) {}

    bool setRunningState(RUNNING_STATUS newStatus) {
        State newState = statusToState(newStatus);

        // Determine if transition is valid and perform it
        bool valid = std::visit([this, &newState](const auto& currentState) -> bool {
            return isValidTransition(currentState, newState);
        }, state_);

        if (valid) {
            RUNNING_STATUS oldStatus = stateToStatus(state_);
            state_ = newState;
            RUNNING_STATUS newStatusResult = stateToStatus(state_);

            std::cout << "IPSecProcessHandler [old : new state] "
                      << oldStatus << " : " << newStatusResult << std::endl;
            return true;
        }

        return false;
    }

private:
    State state_;

    // Convert RUNNING_STATUS enum to State variant
    State statusToState(RUNNING_STATUS status) const {
        switch (status) {
            case RS_NOTRUNNING: return NotRunning();
            case RS_STARTING:   return Starting();
            case RS_STARTED:    return Started();
            case RS_START_FAIL: return StartFail();
            case RS_STOPPING:   return Stopping();
            case RS_STOPPED:    return Stopped();
            default:            return NotRunning();
        }
    }

    // Convert State variant back to RUNNING_STATUS enum
    RUNNING_STATUS stateToStatus(const State& st) const {
        if (std::holds_alternative<NotRunning>(st))  return RS_NOTRUNNING;
        if (std::holds_alternative<Starting>(st))    return RS_STARTING;
        if (std::holds_alternative<Started>(st))     return RS_STARTED;
        if (std::holds_alternative<StartFail>(st))   return RS_START_FAIL;
        if (std::holds_alternative<Stopping>(st))    return RS_STOPPING;
        if (std::holds_alternative<Stopped>(st))     return RS_STOPPED;
        return RS_NOTRUNNING;
    }

    // Validate transitions based on current state
    template<typename CurrentStateType>
    bool isValidTransition(const CurrentStateType&, const State& newState) const {
        using CurrentType = std::decay_t<CurrentStateType>;

        // NotRunning can only transition to Starting
        if constexpr (std::is_same_v<CurrentType, NotRunning>) {
            return std::holds_alternative<Starting>(newState);
        }
        // Starting can transition to Started or StartFail
        else if constexpr (std::is_same_v<CurrentType, Starting>) {
            return std::holds_alternative<Started>(newState) ||
                   std::holds_alternative<StartFail>(newState);
        }
        // Started can transition to StartFail, Stopping, or Stopped
        else if constexpr (std::is_same_v<CurrentType, Started>) {
            return std::holds_alternative<StartFail>(newState) ||
                   std::holds_alternative<Stopping>(newState) ||
                   std::holds_alternative<Stopped>(newState);
        }
        // StartFail can only transition back to NotRunning
        else if constexpr (std::is_same_v<CurrentType, StartFail>) {
            return std::holds_alternative<NotRunning>(newState);
        }
        // Stopping can only transition to Stopped
        else if constexpr (std::is_same_v<CurrentType, Stopping>) {
            return std::holds_alternative<Stopped>(newState);
        }
        // Stopped can only transition to NotRunning
        else if constexpr (std::is_same_v<CurrentType, Stopped>) {
            return std::holds_alternative<NotRunning>(newState);
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
