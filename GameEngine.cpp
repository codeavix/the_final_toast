#include"GameEngine.h"
#include<iostream>
#include<cctype>
using namespace std;
GameEngine::GameEngine(){
    gameOver=false;
    metaUnlocked=false;
    leoAccessible=false;
    quartersUnlocked=false;
    leoInterrogated=false;
    misdirectionDone=false;
    deadlineWarned=false;
    setupSuspects();
    setupEvidence();
}
GameEngine::~GameEngine() {
    for(int i=0;i<EVIDENCE_COUNT;i++)
        delete evidence[i];
    for(int i=0;i<SUSPECT_COUNT;i++)
        delete suspects[i];
}
void GameEngine::setupSuspects() {
    suspects[0]=new Derek();
    suspects[1]=new Fiona();
    suspects[2]=new Marcus();
    suspects[3]=new Leo();
}
void GameEngine::setupEvidence() {
    evidence[0]=new Evidence(
        "Torn Contract",
        "Victor's signature cancels Derek's screen credit.",
        "Study",
        "A contract, shredded then carefully reassembled — as ifsomeone "
        "wanted it found. Victor Cross removed Derek Mann's name from "
        "'Reckoning' six weeks before release. The film made eighty-two "
        "million dollars. Derek received nothing.",false);
    evidence[1]=new Evidence(
        "Whiskey Decanter",
        "Derek's fingerprints — only his — on Victor's private decanter.",
        "Kitchen",
        "Victor's private crystal decanter. Derek Mann's fingerprints are "
        "clear and complete on the neck and body. No other prints at all. "
        "No smudges. Something about how clean they are bothers you.",false);
    evidence[2]=new Evidence(
        "Cigarette Butt",
        "Derek's rare brand of cigarette — found outside the study window.",
        "Garden",
        "A cigarette butt in the garden, directly below the study window. "
        "English Ovals — a rare British import. You saw a pack in Derek's "
        "jacket pocket when he arrived. He was standing here.",false);
    evidence[3]=new Evidence(
        "Poison Vial",
        "Aconite — found hidden in Fiona's makeup case.",
        "Dressing Room",
        "A small glass vial hidden under the false bottom of Fiona's makeup "
        "case. The residue is aconite — colorless in whiskey and fast-acting. "
        "Fiona's fingerprints are on the outside of the case. Not on the vial.",false);
    evidence[4]=new Evidence(
        "Security Footage",
        "Fiona entering the study at 9:15 PM — ten minutes before death.",
        "Projection Room",
        "The security camera at the study door. Fiona enters at 9:15 PM "
        "and leaves at 9:16 PM — one minute inside. Victor was found dead "
        "at 9:25 PM. There is a two-second jump in the footage at 9:17. "
        "You almost miss it.",false);
    evidence[5]=new Evidence(
        "Threatening Texts",
        "Fiona's message to Victor:'This ends tonight.'",
        "Dressing Room",
        "Fiona's phone left face-up on the vanity. forty-three unanswered "
        "messages to Victor over two months. The last one, sent at 7:00 PM:"
        "'This ends tonight. You will pay forwhat you did.' "
        "Victor read it. He did not reply.",false);
    evidence[6]=new Evidence(
        "Victor's Letter",
        "Victor telling a studio to keep Marcus desperate on purpose.",
        "Projection Room",
        "A printed email, folded and unfolded many times. Victor Cross "
        "to a studio head four years ago:'Keep Webb hungry — he takes "
        "better deals when he is desperate. Do not greenlight anything "
        "he pitches directly.' Someone has been carrying this fortwo weeks.",false);
    evidence[7]=new Evidence(
        "Stained Handkerchief",
        "Marcus's handkerchief with chemical residue near the decanter.",
        "Study",
        "A monogrammed handkerchief — M.W. — near the whiskey cabinet. "
        "There is a chemical residue on the fabric. "
        "The full analysis is still pending.",false);
    evidence[8]=new Evidence(
        "Voice Memo",
        "Marcus's recording:'Tonight Victor dies. I'll make it an accident.'",
        "Garage",
        "Marcus's phone in his unlocked rental car. A voice memo at 6:45 PM:"
        "'Tonight Victor dies. I will make it look like an accident.' "
        "Then laughter. It is not clear ifthis is a plan or dark humour.",false);
    evidence[9]=new Evidence(
        "Fingerprint Analysis",
        "Derek's prints are forensically too perfect — pressed, not gripped.",
        "Study",
        "Comparing the decanter prints against Derek's other prints. "
        "The decanter prints show no natural pressure variation at all. "
        "A person gripping glass always leaves partial smears. These do not. "
        "They were pressed deliberately — rolled finger by finger. "
        "Derek Mann did not touch that decanter.",true);
    evidence[10]=new Evidence(
        "Original Footage",
        "Unedited recording — a gloved figure enters the study at 9:17.",
        "Servant's Quarters",
        "A backup drive hidden behind a loose panel in the servant's quarters. "
        "The original unedited footage:Fiona leaves at 9:16 PM. "
        "A gloved figure enters at 9:17 PM carrying something small. "
        "Exits at 9:19 PM with the decanter. The public recording was edited. "
        "This copy was missed.",true);
    evidence[11]=new Evidence(
        "Residue Report",
        "The handkerchief has strychnine — not the aconite that killed Victor.",
        "Study",
        "Cross-referencing the handkerchief residue with the autopsy results. "
        "Victor Cross was killed by aconite. The residue on Marcus's handkerchief "
        "is strychnine — a completely different compound. "
        "Marcus's handkerchief was planted with the wrong poison.",true);
    evidence[12]=new Evidence(
        "Killer's Gloves",
        "Gloves with traces of all three suspects. Plus a burner phone.",
        "Servant's Quarters",
        "Latex gloves in a sealed bag at the back of the wardrobe. "
        "Derek's tobacco on the right thumb. Fiona's hair in the wrist seam. "
        "Marcus's cologne on the palm. "
        "A burner phone beside them — six weeks of messages, all deleted.",true);
}
string GameEngine::toLower(const string&s)const{
    string result=s;
    for(int i=0;i<(int)result.size();i++)
        result[i]=tolower(result[i]);
    return result;
}
string GameEngine::findSuspectName(const string& input)const{
    string low=toLower(input);
    if(low.find("derek")!=string::npos)return"Derek Mann";
    if(low.find("fiona")!=string::npos)return"Fiona Grey";
    if(low.find("marcus")!=string::npos)return"Marcus Webb";
    if(low.find("leo")!=string::npos)return"Leo Hart";
    return "";
}
Evidence*GameEngine::findEvidence(const string& name){
    string low=toLower(name);
    for(int i=0;i<EVIDENCE_COUNT;i++){
        if(toLower(evidence[i]->getName()).find(low)!=string::npos)
            return evidence[i];
    }
    return nullptr;
}
Suspect* GameEngine::findSuspect(const string& name){
    for(int i=0;i<SUSPECT_COUNT;i++) {
        if(suspects[i]->getName()==name)
            return suspects[i];
    }
    return nullptr;
}
bool GameEngine::allThreeSuspectsInterrogated()const{
    bool derekDone=suspects[0]->isInterrogated();//Derek
    bool fionaDone=suspects[1]->isInterrogated();//Fiona
    bool marcusDone=suspects[2]->isInterrogated();//Marcus
    return derekDone&&fionaDone&&marcusDone;
}
void GameEngine::syncEvidenceToSuspects(){
    if(player.has("Torn Contract"))suspects[0]->unlockQuestion(0);
    if(player.has("Whiskey Decanter"))suspects[0]->unlockQuestion(1);
    if(player.has("Cigarette Butt"))suspects[0]->unlockQuestion(2);
    if(player.has("Poison Vial"))suspects[1]->unlockQuestion(0);
    if(player.has("Security Footage"))suspects[1]->unlockQuestion(1);
    if(player.has("Threatening Texts"))suspects[1]->unlockQuestion(2);
    if(player.has("Victor's Letter"))suspects[2]->unlockQuestion(0);
    if(player.has("Stained Handkerchief"))suspects[2]->unlockQuestion(1);
    if(player.has("Voice Memo"))suspects[2]->unlockQuestion(2);
    if(player.has("Original Footage"))suspects[3]->unlockQuestion(0);
    if(player.has("Killer's Gloves"))suspects[3]->unlockQuestion(1);
    if(player.has("Killer's Gloves"))suspects[3]->unlockQuestion(2);
}
void GameEngine::tryUnlockMeta(){
    if(metaUnlocked)return;
    if(!player.hasAllBaseClues())return;
    if(!allThreeSuspectsInterrogated())return;
    metaUnlocked=true;
    leoAccessible=true;
    cout<<"\n";
    UI::divider('*');
    UI::typewrite("  You sit with everything you have.",28,Color::BOLD);
    UI::pause(500);
    UI::typewrite("  Derek. Fiona. Marcus.",22,Color::DIM);
    UI::typewrite("  Their motives. Their alibis. Their anger.",22,Color::DIM);
    UI::pause(400);
    UI::typewrite("  And something is wrong with all of it.",28,Color::YELLOW);
    UI::pause(300);
    UI::typewrite("  The fingerprints are too clean.",22,Color::CYAN);
    UI::typewrite("  The footage has a gap.",22,Color::CYAN);
    UI::typewrite("  The handkerchief has the wrong poison.",22,Color::CYAN);
    UI::pause(400);
    UI::typewrite("  Three perfect suspects. Too perfect.",30,Color::RED);
    UI::pause(300);
    UI::typewrite("  Someone invisible has been in this house all evening.",25,Color::YELLOW);
    UI::typewrite("  Talk to Leo.",35,Color::GREEN);
    UI::divider('*');
    cout<<"\n";
}
void GameEngine::tryUnlockQuarters(){
    if(quartersUnlocked)return;
    if(!leoInterrogated)return;
    quartersUnlocked=true;
    cout<<"\n";
    UI::divider('*');
    UI::typewrite("  Something about Leo's answers sits wrong.",25,Color::DIM);
    UI::typewrite("  Too composed. Too ready forevery question.",25,Color::YELLOW);
    UI::typewrite("  You think about the servant's quarters.",25,Color::DIM);
    UI::typewrite("  The door is now accessible.",25,Color::GREEN);
    UI::divider('*');
    cout<<"\n";
}
void GameEngine::tryMisdirection(){
    if(misdirectionDone)return;
    if(player.baseClueCount()<3)return;
    bool anyInterrogated=false;
    for(int i=0;i<SUSPECT_COUNT;i++){
        if(suspects[i]->isInterrogated()){
            anyInterrogated=true;
            break;
        }
    }
    if(!anyInterrogated)return;
    misdirectionDone=true;
    cout<<"\n";
    UI::divider();
    cout<<Color::DIM<<"  Leo Hart approaches you quietly.\n"<<Color::RESET;
    UI::pause(400);
    UI::typewrite("  \""+suspects[3]->getMisdirection()+"\"",20,Color::WHITE);
    UI::divider();
    cout<<"\n";
}
void GameEngine::checkDeadline(){
    if(deadlineWarned)return;
    if(player.baseClueCount()<7)return;
    deadlineWarned=true;
    cout<<"\n";
    UI::divider('-');
    UI::typewrite("  A constable appears at the door.",25,Color::DIM);
    UI::typewrite("  'The inspector arrives at first light, detective.",22,Color::YELLOW);
    UI::typewrite("   You have until then to make your case.'",22,Color::YELLOW);
    cout<<Color::RED<<"  [ "<<player.getAccusationsLeft()<<" accusations remaining ]\n"<<Color::RESET;
    UI::divider('-');
    cout<<"\n";
}
void GameEngine::showIntro(){
    UI::clearScreen();
    ASCII::mansion();
    UI::pause(400);
    UI::typewrite("  THE FINAL TOAST",38,Color::BOLD+Color::YELLOW);
    UI::typewrite("  A Murder Mystery",24,Color::DIM);
    UI::divider();
    ASCII::victim();
    UI::slow("  11:47 PM. The Reckoning premiere after-party.",Color::DIM);
    UI::slow("  Victor Cross is dead. Poison in his whiskey decanter.",Color::RED);
    UI::slow("  The mansion is sealed. No one leaves.",Color::DIM);
    UI::slow("  You are the detective.",Color::CYAN);
    UI::divider();
    UI::typewrite("  Four people had reason to want Victor Cross dead.",22,Color::WHITE);
    UI::typewrite("  You have two accusations. Use them carefully.",28,Color::RED);
    UI::divider();
}
void GameEngine::showHelp() {
    UI::header("COMMANDS");
    cout<<Color::CYAN<<"  GO [room]              "<<Color::RESET<<"explore a room\n";
    cout<<Color::CYAN<<"  EXAMINE [evidence]     "<<Color::RESET<<"read evidence in detail\n";
    cout<<Color::CYAN<<"  COMPARE [ev1] / [ev2]  "<<Color::RESET<<"compare two pieces of evidence\n";
    cout<<Color::CYAN<<"  TALK [name]            "<<Color::RESET<<"interrogate a suspect\n";
    cout<<Color::CYAN<<"  ACCUSE [name]          "<<Color::RESET<<"make a formal accusation\n";
    cout<<Color::CYAN<<"  SUSPECTS               "<<Color::RESET<<"list all suspects\n";
    cout<<Color::CYAN<<"  CASEFILE               "<<Color::RESET<<"show evidence progress\n";
    cout<<Color::CYAN<<"  ROOMS                  "<<Color::RESET<<"show the map\n";
    cout<<Color::CYAN<<"  HELP                   "<<Color::RESET<<"this menu\n";
    cout<<Color::CYAN<<"  QUIT                   "<<Color::RESET<<"exit\n\n";
}

void GameEngine::showMap(){
    UI::header("MANSION MAP");
    cout<<Color::YELLOW<<"  UPPER FLOOR\n"<<Color::RESET;
    cout<<Color::DIM<<"  +------------------+------------------+------------------+\n"<<Color::RESET;
    cout<<"  | "<<Color::MAGENTA<<" Dressing Room    "<<Color::RESET<<Color::DIM<<"|"<<Color::RESET;
    cout<<Color::CYAN<<" Projection Room  "<<Color::RESET<<Color::DIM<<"|"<<Color::RESET;
    if(quartersUnlocked)
        cout<<Color::GREEN<<" Servant's Qtrs   "<<Color::RESET;
    else
        cout<<Color::DIM<<" Servant's Qtrs   "<<Color::RESET;
    cout<<Color::DIM<<"|\n"<<Color::RESET;
    cout<<Color::DIM<<"  |  (Fiona's room)  |  (security cam)  |";
    if(quartersUnlocked)
        cout<<Color::GREEN<<"  (Leo's room)    "<<Color::DIM<<"|\n"<<Color::RESET;
    else
        cout<<Color::DIM<<"  [LOCKED]         |\n"<<Color::RESET;
    cout<<Color::DIM<<"  +------------------+------------------+------------------+\n\n"<<Color::RESET;
    cout<<Color::YELLOW<<"  GROUND FLOOR\n"<<Color::RESET;
    cout<<Color::DIM<<"  +------------------+------------------+------------------+\n"<<Color::RESET;
    cout<<"  | "<<Color::BLUE<<" Study            "<<Color::RESET<<Color::DIM<<"|"<<Color::RESET;
    cout<<Color::WHITE<<" Kitchen          "<<Color::RESET<<Color::DIM<<"|"<<Color::RESET;
    cout<<Color::YELLOW<<" Garage           "<<Color::RESET<<Color::DIM<<"|\n"<<Color::RESET;
    cout<<Color::DIM<<"  |  (Victor's study)|  (catering)      |  (Marcus's car)  |\n";
    cout<<"  +------------------+------------------+------------------+\n\n"<<Color::RESET;

    cout<<Color::YELLOW<<"  GROUNDS\n"<<Color::RESET;
    cout<<Color::DIM<<"  +------------------+\n"<<Color::RESET;
    cout<<"  | "<<Color::GREEN<<" Garden           "<<Color::RESET<<Color::DIM<<"|\n"<<Color::RESET;
    cout<<Color::DIM<<"  |  (east hedge)    |\n  +------------------+\n\n"<<Color::RESET;
    cout<<Color::YELLOW<<"  ROOM STATUS\n"<<Color::RESET;

    string roomEvidence[ROOM_COUNT][4]={
        {"Torn Contract", "Stained Handkerchief", "Fingerprint Analysis", "Residue Report"},
        {"Whiskey Decanter", "", "", ""},
        {"Cigarette Butt", "", "", ""},
        {"Poison Vial", "Threatening Texts", "", ""},
        {"Security Footage", "Victor's Letter", "", ""},
        {"Voice Memo", "", "", ""},
        {"Original Footage", "Killer's Gloves", "", ""}
    };

    for(int r=0; r<ROOM_COUNT; r++) {
        bool locked=(rooms[r]=="Servant's Quarters" && !quartersUnlocked);
        int total=0, found=0;

        for(int e=0; e<4; e++) {
            if(roomEvidence[r][e]=="") break;
            total++;
            if(player.has(roomEvidence[r][e])) found++;
        }

        if(locked) {
            cout<<Color::DIM<<"  [locked] "<<rooms[r]<<Color::RESET<<"\n";
        } else if(total==0 || found==0) {
            cout<<Color::DIM<<"  [  ] "<<rooms[r]<<Color::RESET<<"\n";
        } else if(found==total) {
            cout<<Color::GREEN<<"  [+] "<<Color::RESET<<rooms[r]<<Color::DIM<<"  all evidence logged\n"<<Color::RESET;
        } else {
            cout<<Color::YELLOW<<"  [~] "<<Color::RESET<<rooms[r]<<"  "<<found<<"/"<<total<<" clues\n";
        }
    }
    cout<<"\n";
}
void GameEngine::exploreRoom(const string& input) {
    string roomName="";
    string low=toLower(input);
    for(int i=0; i<ROOM_COUNT; i++) {
        if(toLower(rooms[i]).find(low) !=string::npos) {
            roomName=rooms[i];
            break;
        }
    }
    if(roomName=="") {
        UI::print("  That room does not exist.",Color::DIM);
        return;
    }
    if(roomName=="Servant's Quarters" && !quartersUnlocked) {
        UI::typewrite("  The door is locked. You have no reason to go in there yet.", 22,Color::DIM);
        return;
    }
    UI::header(roomName);
    if(roomName=="Study")
        UI::typewrite("Victor's private study. The whiskey cabinet stands open.", 16,Color::DIM);
    else if(roomName=="Kitchen")
        UI::typewrite("The catering staff have cleared out. Surfaces still warm.", 16,Color::DIM);
    else if(roomName=="Garden")
        UI::typewrite("The party overflowed here earlier. The study window is visible from the hedge.", 16,Color::DIM);
    else if(roomName=="Dressing Room")
        UI::typewrite("Fiona's room. Mirrors everywhere. The door was unlocked all evening.", 16,Color::DIM);
    else if(roomName=="Projection Room")
        UI::typewrite("The screening room. The security monitor still runs in the corner.", 16,Color::DIM);
    else if(roomName=="Garage")
        UI::typewrite("Three cars. Marcus Webb's rental is the only one unlocked.", 16,Color::DIM);
    else if(roomName=="Servant's Quarters")
        UI::typewrite("Small. Immaculate. A photograph of Victor Cross on the desk.", 16,Color::DIM);
    cout<<"\n";
    bool anyNew=false;
    for(int i=0; i<EVIDENCE_COUNT; i++) {
        if(evidence[i]->getLocation() !=roomName) continue;
        if(evidence[i]->isMetaClue() && !metaUnlocked) continue;

        if(!evidence[i]->isCollected()) {
            evidence[i]->collect();
            player.collect(evidence[i]->getName());
            cout<<Color::GREEN<<"  [FOUND] "<<Color::RESET;
            cout<<Color::BOLD<<evidence[i]->getName()<<Color::RESET<<"\n";
            cout<<Color::DIM<<"  "<<evidence[i]->getDescription()<<Color::RESET<<"\n";
            anyNew=true;
            UI::pause(200);
        } else {
            cout<<Color::DIM<<"  [already logged] "<<evidence[i]->getName()<<Color::RESET<<"\n";
        }
    }

    if(!anyNew)
        UI::print("  Nothing new here.",Color::DIM);
    syncEvidenceToSuspects();
    tryMisdirection();
    checkDeadline();
    tryUnlockMeta();
}
void GameEngine::examineEvidence(const string& input) {
    Evidence* ev=findEvidence(input);

    if(ev==nullptr) {
        UI::print("  No evidence by that name.",Color::DIM);
        return;
    }
    if(!ev->isCollected()) {
        UI::print("  You have not found that yet.",Color::DIM);
        return;
    }

    ev->examine();
}
void GameEngine::compareEvidence(const string& input) {
    size_t slash=input.find('/');
    if(slash==string::npos) {
        UI::print("  Usage:COMPARE [evidence] / [evidence]",Color::DIM);
        return;
    }

    string nameA=input.substr(0, slash);
    string nameB=input.substr(slash + 1);
    while (!nameA.empty() && nameA.front()==' ') nameA.erase(nameA.begin());
    while (!nameA.empty() && nameA.back()==' ') nameA.pop_back();
    while (!nameB.empty() && nameB.front()==' ') nameB.erase(nameB.begin());
    while (!nameB.empty() && nameB.back()==' ') nameB.pop_back();

    Evidence* evA=findEvidence(nameA);
    Evidence* evB=findEvidence(nameB);

    if(evA==nullptr || !evA->isCollected()) { UI::print("  You do not have:" + nameA,Color::DIM); return; }
    if(evB==nullptr || !evB->isCollected()) { UI::print("  You do not have:" + nameB,Color::DIM); return; }

    UI::divider();
    cout<<Color::BOLD<<Color::CYAN<<"  COMPARING:"<<evA->getName()<<"  &  "<<evB->getName()<<Color::RESET<<"\n";
    UI::divider();

    string a=toLower(evA->getName());
    string b=toLower(evB->getName());

    bool hasA=false;
    bool hasB=false;

    // Whiskey + Cigarette
    hasA=(a.find("whiskey") !=string::npos || a.find("cigarette") !=string::npos);
    hasB=(b.find("whiskey") !=string::npos || b.find("cigarette") !=string::npos);
    if(hasA && hasB && a !=b) {
        UI::typewrite("  Derek's prints on the decanter. His cigarette below the window.", 20,Color::WHITE);
        UI::typewrite("  Motive, presence, and contact with the murder weapon.", 20,Color::WHITE);
        UI::typewrite("  It all fits. Almost too perfectly.", 25,Color::YELLOW);
        UI::typewrite("  Almost.", 40,Color::RED);
        UI::divider(); return;
    }

    // Fingerprint Analysis + Whiskey Decanter
    hasA=(a.find("fingerprint") !=string::npos);
    hasB=(b.find("whiskey") !=string::npos);
    if((hasA && hasB) || (a.find("whiskey") !=string::npos && b.find("fingerprint") !=string::npos)) {
        UI::typewrite("  No natural smearing on the decanter prints.", 20,Color::WHITE);
        UI::typewrite("  A gripped object always shows pressure marks. These do not.", 20,Color::WHITE);
        UI::typewrite("  Someone pressed Derek's fingers there deliberately.", 25,Color::RED);
        UI::divider(); return;
    }

    // Residue Report + Stained Handkerchief
    hasA=(a.find("residue") !=string::npos);
    hasB=(b.find("handkerchief") !=string::npos);
    if((hasA && hasB) || (a.find("handkerchief") !=string::npos && b.find("residue") !=string::npos)) {
        UI::typewrite("  Victor was killed by aconite.", 20,Color::WHITE);
        UI::typewrite("  The residue on Marcus's handkerchief is strychnine.", 25,Color::RED);
        UI::typewrite("  Different poison entirely. It was planted with the wrong compound.", 20,Color::WHITE);
        UI::divider(); return;
    }

    // Security Footage + Original Footage
    hasA=(a.find("security") !=string::npos);
    hasB=(b.find("original") !=string::npos);
    if((hasA && hasB) || (a.find("original") !=string::npos && b.find("security") !=string::npos)) {
        UI::typewrite("  Public footage:Fiona leaves at 9:16.", 20,Color::WHITE);
        UI::typewrite("  Original footage:a gloved figure enters at 9:17 after she left.", 20,Color::WHITE);
        UI::typewrite("  The recording was edited. Fiona did not do this.", 25,Color::RED);
        UI::divider(); return;
    }

    // Killer's Gloves + Original Footage
    hasA=(a.find("killer") !=string::npos || a.find("gloves") !=string::npos);
    hasB=(b.find("original") !=string::npos);
    if((hasA && hasB) || (b.find("killer") !=string::npos && a.find("original") !=string::npos)) {
        UI::typewrite("  The gloves carry traces of all three suspects.", 20,Color::WHITE);
        UI::typewrite("  The footage shows a gloved figure entering the study.", 20,Color::WHITE);
        UI::typewrite("  The same pair of gloves.", 35,Color::RED);
        UI::typewrite("  Who moves through this house completely unseen?", 35,Color::BOLD +Color::YELLOW);
        UI::divider(); return;
    }

    // No match
    UI::typewrite("  You study both carefully. No connection surfaces yet.", 20,Color::DIM);
    UI::divider();
}

void GameEngine::interrogateSuspect(const string& input) {
    string name=findSuspectName(input);

    if(name=="") {
        UI::print("  Who do you want to talk to?",Color::DIM);
        return;
    }

    Suspect* s=findSuspect(name);
    if(s==nullptr) return;

    if(name=="Leo Hart" && !leoAccessible) {
        UI::typewrite("  Leo is attending to guests.", 22,Color::DIM);
        UI::typewrite("  You have no grounds to press him yet.", 22,Color::DIM);
        return;
    }

    if(s->isDetained()) {
        UI::print("  " + name + " has been detained.",Color::DIM);
        return;
    }

    syncEvidenceToSuspects();
    s->interrogate(player.baseClueCount());

    if(name=="Leo Hart") {
        leoInterrogated=true;
        tryUnlockQuarters();
    }

    tryUnlockMeta();
    tryMisdirection();
}

void GameEngine::makeAccusation(const string& input) {
    string name=findSuspectName(input);

    if(name=="") {
        UI::print("  Name a specific suspect.",Color::DIM);
        return;
    }
    if(!player.canAccuse()) {
        outOfAccusations();
        return;
    }

    player.useAccusation();

    UI::header("forMAL ACCUSATION");
    UI::typewrite("  You step forward.", 25,Color::BOLD);
    UI::pause(500);

    Suspect* s=findSuspect(name);
    s->displayProfile();
    UI::pause(300);
    UI::typewrite(s->getAccusedResponse(), 20,Color::WHITE);
    UI::pause(500);

    if(name=="Leo Hart") {
        if(player.metaClueCount() >=2) {
            correctEnding();
        } else {
            UI::divider();
            UI::typewrite("  'You have suspicions, detective. Not proof.'", 22,Color::WHITE);
            UI::typewrite("  'A good lawyer walks me out in twenty minutes.'", 22,Color::DIM);
            UI::typewrite("  The accusation does not stick. Keep digging.", 25,Color::YELLOW);
            player.refundAccusation();
            UI::divider();
        }
    } else {
        wrongEnding(s);
    }
}

void GameEngine::wrongEnding(Suspect* s) {
    ASCII::wrongArt();
    UI::pause(300);

    s->setDetained(true);
    player.addWrongAccusation();

    UI::typewrite("  " + s->getName() + " is detained.", 22,Color::DIM);
    UI::pause(300);
    UI::typewrite(s->getInnocentResponse(), 22,Color::WHITE);
    UI::pause(500);
    cout<<"\n"<<Color::DIM<<"  Across the room, Leo Hart watches quietly.\n"<<Color::RESET;
    UI::pause(400);
    UI::typewrite("  He gives a small sympathetic nod.", 22,Color::DIM);
    UI::typewrite("  'A difficult case,' he says softly. 'Shall I bring you tea?'", 22,Color::WHITE);
    UI::pause(500);

    UI::divider();
    cout<<Color::YELLOW<<"\n  The case is not over. The real killer is still here.\n"<<Color::RESET;
    cout<<Color::RED<<"  [ "<<player.getAccusationsLeft()<<" accusations remaining ]\n"<<Color::RESET;
    UI::divider();
    cout<<"\n";

    if(player.getAccusationsLeft()==0)
        outOfAccusations();
}

void GameEngine::correctEnding() {
    UI::clearScreen();
    ASCII::solvedArt();
    UI::pause(400);

    Suspect* leo=findSuspect("Leo Hart");

    UI::typewrite("  Leo Hart does not run.", 25,Color::DIM);
    UI::typewrite("  Leo Hart does not deny it.", 25,Color::DIM);
    UI::typewrite("  He sits down, very carefully.", 25,Color::DIM);
    UI::pause(600);
    UI::divider();
    UI::typewrite(leo->getKillerConfession(), 22,Color::WHITE);

    UI::pause(500);
    UI::divider();

    cout<<Color::DIM<<"\n  Later, you understand how it was done.\n"<<Color::RESET;
    UI::typewrite(leo->getPlantingStyle(), 20,Color::CYAN);

    UI::pause(600);
    UI::divider();

    cout<<"\n"<<Color::GREEN<<Color::BOLD<<"  Case closed. Killer:Leo Hart\n"<<Color::RESET;
    cout<<Color::DIM;
    cout<<"  Base clues:"<<player.baseClueCount()<<"/9\n";
    cout<<"  Meta-clues:"<<player.metaClueCount()<<"/4\n";
    cout<<"  Wrong guesses:"<<player.getWrongAccusations()<<"\n";
    cout<<Color::RESET;

    if(player.getWrongAccusations()==0)
        UI::typewrite("  Perfect. No innocent person was accused.", 22,Color::GREEN);
    else
        UI::typewrite("  " + to_string(player.getWrongAccusations()) + " innocent person(s) were detained.", 22,Color::YELLOW);

    cout<<"\n";
    gameOver=true;
}
void GameEngine::outOfAccusations() {
    UI::clearScreen();
    ASCII::wrongArt();
    UI::pause(400);
    UI::typewrite("  The inspector arrives at first light.", 25,Color::DIM);
    UI::typewrite("  You have no accusations left.", 25,Color::RED);
    UI::typewrite("  The case closes without a conviction.", 25,Color::DIM);
    UI::divider();
    UI::typewrite("  Leo Hart leaves the mansion the next morning.", 22,Color::DIM);
    UI::typewrite("  He does not look back.", 22,Color::DIM);
    UI::typewrite("  The killer was:Leo Hart", 25,Color::BOLD +Color::RED);
    UI::divider();
    cout<<"\n";
    gameOver=true;
}
void GameEngine::run() {
    showIntro();
    UI::pressEnter();
    showHelp();
    UI::header("THE SUSPECTS");
    for(int i=0; i<SUSPECT_COUNT; i++) {
        suspects[i]->display();
        cout<<"\n";
    }
    UI::divider();

    string line;

    while (!gameOver) {
        cout<<"\n"<<Color::BOLD<<Color::GREEN<<"  DETECTIVE > "<<Color::RESET;
        if(!getline(cin, line)) break;
        while (!line.empty() && line.front()==' ') line.erase(line.begin());
        while (!line.empty() && line.back()==' ') line.pop_back();
        if(line.empty()) continue;

        string cmd=toLower(line);

        if(cmd=="quit" || cmd=="exit") {
            UI::typewrite("  You leave. The case remains open.", 22,Color::DIM);
            break;
        }
        else if(cmd=="help") {
            showHelp();
        }
        else if(cmd=="rooms" || cmd=="map") {
            showMap();
        }
        else if(cmd=="casefile") {
            player.showCaseFile();
        }
        else if(cmd=="suspects") {
            UI::header("SUSPECTS");
            for(int i=0; i<SUSPECT_COUNT; i++) {
                suspects[i]->display();
                cout<<"\n";
            }
        }
        else if(cmd.substr(0, 3)=="go ") {
            exploreRoom(line.substr(3));
        }
        else if(cmd.substr(0, 8)=="examine ") {
            examineEvidence(line.substr(8));
        }
        else if(cmd.substr(0, 8)=="compare ") {
            compareEvidence(line.substr(8));
        }
        else if(cmd.substr(0, 5)=="talk ") {
            interrogateSuspect(line.substr(5));
        }
        else if(cmd.substr(0, 7)=="accuse ") {
            makeAccusation(line.substr(7));
        }
        else {
            UI::print("  Unknown command. Type HELP forthe list.",Color::DIM);
        }
    }
}
