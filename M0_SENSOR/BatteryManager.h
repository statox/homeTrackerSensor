#pragma once

struct BatteryData {
    float charge;
    float percent;
};

class BatteryManager {
public:
    BatteryManager(int batteryPin);

    void initializeData();
    void updateData();
    bool mustShutdown();

    BatteryData batteryData;

private:
    int batteryPin;
};
