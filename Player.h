#pragma once
#include "UI.h"
using namespace std;
class Player {
private:
    bool evidenceFound[13];
    int accusationsLeft;
    int wrongAccusations;
    static const int TOTAL=13;
    static const int BASE=9;

    string evidenceNames[TOTAL]={
        // Base clues
        "Torn Contract","Whiskey Decanter","Cigarette Butt","Poison Vial","Security Footage",
        "Threatening Texts","Victor's Letter","Stained Handkerchief","Voice Memo",          
        // Meta clues
        "Fingerprint Analysis","Original Footage","Residue Report","Killer's Gloves"       
    };

public:
    Player() {
        accusationsLeft=2;
        wrongAccusations=0;
        for(int i=0; i<TOTAL; i++)
            evidenceFound[i]=false;
    }
    void collect(const string& evName) {
        for(int i=0; i<TOTAL; i++) {
            if(evidenceNames[i]==evName) {
                evidenceFound[i]=true;
                return;
            }
        }
    }
    bool has(const string& evName)const {
        for(int i=0; i<TOTAL; i++) {
            if(evidenceNames[i]==evName)
                return evidenceFound[i];
        }
        return false;
    }
    int baseClueCount()const {
        int count=0;
        for(int i=0; i<BASE; i++)
            if(evidenceFound[i]) count++;
        return count;
    }
    int metaClueCount()const {
        int count=0;
        for(int i=BASE; i<TOTAL; i++)
            if(evidenceFound[i]) count++;
        return count;
    }
    bool hasAllBaseClues()const {
        return baseClueCount()==BASE;
    }
    void showCaseFile()const {
        ASCII::casefile();
        cout<<Color::YELLOW<<"  Base clues:"<<Color::BOLD<<baseClueCount()<<"/9"<<Color::RESET<<"\n";
        cout<<Color::CYAN<<"  Meta-clues:"<<Color::BOLD<<metaClueCount()<<"/4"<<Color::RESET<<"\n";
        cout<<Color::RED<<"  Accusations:"<<Color::BOLD<<accusationsLeft<<" remaining"<<Color::RESET<<"\n\n";
    }
    bool canAccuse()const { return accusationsLeft > 0; }
    void useAccusation()         { if(accusationsLeft > 0) accusationsLeft--; }
    void refundAccusation()      { accusationsLeft++; }
    void addWrongAccusation()    { wrongAccusations++; }
    int  getAccusationsLeft()const { return accusationsLeft; }
    int  getWrongAccusations()const { return wrongAccusations; }
};
