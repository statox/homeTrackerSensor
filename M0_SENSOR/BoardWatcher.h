#pragma once

class BoardWatcher {
public:
    BoardWatcher(int maxLoopRunningTimeMS);

    void init();
    void newLoop();
    void timerCallback();

    int currentLoopTime();
private:
    int maxLoopRunningTimeMS;
    int lastLoopStart;
};
