#pragma once
#include "CppScripts.h"

struct ActivityTimer {
    std::string name;
    float_t updateInterval;
    float_t stopTime;
    float_t runTime = 0;
};

class ActivityManager : public CppScripts::Script {
public:
    static bool IsPlayerInActivity(Entity *self, LWOOBJID playerID);
    static void UpdatePlayer(Entity *self, LWOOBJID playerID, bool remove = false);
    static void SetActivityScore(Entity *self, LWOOBJID playerID, uint32_t score);
    static void SetActivityValue(Entity *self, LWOOBJID playerID, uint32_t valueIndex, float_t value);
    static float_t GetActivityValue(Entity *self, LWOOBJID playerID, uint32_t valueIndex) ;
    static bool TakeActivityCost(const Entity* self, LWOOBJID playerID);
    static uint32_t GetActivityID(const Entity* self);
    /**
    * Stops the activity, awards the player loot, then saves and shows the leaderboard
    * @param self - Self pointer to the Entity Activity
    * @param playerID - LWOOBJID of the player who is stopping the activity
    * @param score - Score for the activity, this will be waves in survival
    * @param value1 - Activity time or Max Streak for GF SG
    * @param value2 - Score for BaseWavesServer or Percent for GF SG
    * @param value3 - Unused
    * @param value4 - Unused
    * @param quit - If the activity was quit before completion
    */
    void StopActivity(Entity* self, LWOOBJID playerID, uint32_t score, uint32_t value1 = 0, uint32_t value2 = 0, uint32_t value3 = 0, uint32_t value4 = 0, bool quit = false);
    virtual uint32_t CalculateActivityRating(Entity* self, LWOOBJID playerID);
    static void GetLeaderboardData(Entity *self, LWOOBJID playerID, uint32_t activityID, uint32_t numResults = 0);
    //void FreezePlayer(Entity *self, const LWOOBJID playerID, const bool state) const;

    // Activity timer
    void OnTimerDone(Entity *self, std::string timerName) override;
    virtual void OnActivityTimerDone(Entity* self, const std::string& name) {};
    virtual void OnActivityTimerUpdate(Entity* self, const std::string& name, float_t timeRemaining, float_t elapsedTime) {};
    void ActivityTimerStart(Entity *self, const std::string& timerName, float_t updateInterval, float_t stopTime = -1.0f);
    void ActivityTimerReset(Entity *self, const std::string& timerName);
    void ActivityTimerStop(Entity* self, const std::string& timerName);
    void ActivityTimerStopAllTimers(Entity* self);
    float_t ActivityTimerGetRemainingTime(Entity *self, const std::string& timerName) const;
    float_t ActivityTimerGetCurrentTime(Entity *self, const std::string& timerName) const;
    int32_t GetGameID(Entity* self) const;
private:
    std::string GetPrefixedName(const std::string& name) const;
    [[nodiscard]] ActivityTimer* GetTimer(const std::string& name) const;
    std::vector<ActivityTimer*> activeTimers {};
    std::string TimerPrefix = "ActivityTimer";
};
