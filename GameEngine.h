#pragma once
#include "Player.h"
#include "Entity.h"
#include "Suspect.h"
using namespace std;
class GameEngine {
private:
    Player player;
    static const int EVIDENCE_COUNT=13;
    Evidence* evidence[EVIDENCE_COUNT];
    static const int SUSPECT_COUNT=4;
    Suspect* suspects[SUSPECT_COUNT];
    static const int ROOM_COUNT=7;
    string rooms[ROOM_COUNT]={
        "Study",
        "Kitchen",
        "Garden",
        "Dressing Room",
        "Projection Room",
        "Garage",
        "Servant's Quarters"
    };
    bool gameOver;
    bool metaUnlocked;
    bool leoAccessible;      
    bool quartersUnlocked;
    bool leoInterrogated;
    bool misdirectionDone;
    bool deadlineWarned;
    void setupEvidence();
    void setupSuspects();
    string toLower(const string& s)const;
    string findSuspectName(const string& input)const;
    Evidence* findEvidence(const string& name);
    Suspect*  findSuspect(const string& name);

    bool allThreeSuspectsInterrogated()const;
    void syncEvidenceToSuspects();

    void tryUnlockMeta();
    void tryUnlockQuarters();
    void tryMisdirection();
    void checkDeadline();

    void showIntro();
    void showHelp();
    void showMap();

    void exploreRoom(const string& input);
    void examineEvidence(const string& input);
    void compareEvidence(const string& input);
    void interrogateSuspect(const string& input);
    void makeAccusation(const string& input);

    void wrongEnding(Suspect* suspect);
    void correctEnding();
    void outOfAccusations();

public:
    GameEngine();
    ~GameEngine();
    void run();
};
