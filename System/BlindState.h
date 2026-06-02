#pragma once
#include <string>

struct RunSessionState; // Forward declaration

class BlindState {
public:
    virtual ~BlindState() = default;
    
    virtual std::string getName() = 0;
    virtual int getTargetScore() = 0;
    
    virtual void handlePlay(RunSessionState& state) = 0;
    virtual void handleSkip(RunSessionState& state) = 0;
};