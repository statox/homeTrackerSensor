#pragma once

class BoardWatcher {
public:
    BoardWatcher(int maxLoopRunningTimeMS);

    void init();
    void newLoop();
    void timerCallback();

private:
    int maxLoopRunningTimeMS;
    int lastLoopStart;
};
