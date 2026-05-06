#pragma once
#include "Entity.h"
using namespace std;
class Suspect:public Entity {
private:
    bool interrogated;
    bool detained;

protected:
    string role;
    string motive;
    bool questionUnlocked[3];
    bool questionAsked[3];

public:
    Suspect(string n, string desc, string r, string mot)
:Entity(n, desc) {
        role=r;
        motive=mot;
        interrogated=false;
        detained=false;

        for(int i=0; i<3; i++) {
            questionUnlocked[i]=false;
            questionAsked[i]=false;
        }
    }

    virtual ~Suspect() {}
    virtual string getQuestion(int i)const=0;
    virtual string getResponse(int i)const=0;
    virtual string getIdleResponse()const=0;
    virtual string getAccusedResponse()const=0;
    virtual string getInnocentResponse()const=0;
    virtual string getKillerConfession()const=0;
    virtual string getMisdirection()const=0;
    virtual string getPlantingStyle()const=0;
    virtual void displayProfile()const=0;

    void display()const override {
        cout<<Color::BOLD<<"  "<<name<<Color::RESET;
        if(detained)
            cout<<Color::RED<<"  [DETAINED]"<<Color::RESET;
        cout<<Color::DIM<<"  ("<<role<<")"<<Color::RESET<<"\n";
        cout<<"  "<<description<<"\n";
    }

    void unlockQuestion(int index) {
        if(index >=0 && index<3)
            questionUnlocked[index]=true;
    }

    void interrogate(int totalEvidence) {
       interrogated=true;
       ASCII::suspectArt(name);
       UI::header("INTERROGATING:" +name);
       UI::typewrite(getIdleResponse(),20,Color::DIM);
       while (true) {
           cout<<"\n";
           UI::print("  Available questions:",Color::YELLOW);
           int count=0;
           int indexMap[3];
           for(int i=0;i<3;i++){
               if(questionUnlocked[i]&&!questionAsked[i]) {
                   indexMap[count]=i;
                   count++;
                   cout<<"  "<<count<<". "<<getQuestion(i)<<"\n";
               }
           }
           for(int i=0;i<3;i++) {
               if(questionAsked[i])
                   cout<<Color::DIM<<"  [asked] "<<getQuestion(i)<<Color::RESET<<"\n";
           }
           if(count==0){
               UI::print("  No questions unlocked yet. Find more evidence.",
Color::DIM);
               break;
           }
           cout<<Color::DIM<<"  0. Leave\n"<<Color::RESET;
           cout<<"\n"<<Color::CYAN<<"  > "<<Color::RESET;
           int choice;
           if(!(cin>>choice)){
               cin.clear();
               cin.ignore(1000,'\n');
               continue;
           }
           cin.ignore(1000,'\n');
           if(choice==0)break;
           if(choice<1||choice>count)continue;
           int qIndex=indexMap[choice-1];
           questionAsked[qIndex]=true;
           UI::divider();
           UI::typewrite(getResponse(qIndex),20,Color::WHITE);
           UI::divider();
       }
   }
   bool isInterrogated()const{
    return interrogated;
   } 
   bool isDetained()const{
    return detained;
   }
   string getRole()const{
    return role;
   } 
   void setDetained(bool v){
    detained=v;
   }
};

class Derek:public Suspect {
public:
    Derek():Suspect(
        "Derek Mann",
        "Quiet. Precise. Watches people like he is taking notes.",
        "Screenwriter",
        "Victor stole Derek's script — drawn from his father's death — "
        "and claimed it as his own creative vision fortwo years."
    ) {}

    string getQuestion(int i)const override {
        if(i==0) return "About the torn contract in the study...";
        if(i==1) return "Your fingerprints are on the decanter.";
        if(i==2) return "You were in the garden below the study window.";
        return "";
    }

    string getResponse(int i)const override {
        if(i==0) return
            "Victor removed my credit six weeks before release. After four years. "
            "The script was my father's story — his illness, his death. "
            "Victor stood at every press event claiming it as his own imagination. "
            "My father's death became Victor's creative vision.";
        if(i==1) return
            "That is impossible. I never touched the decanter. "
            "Look at those prints properly — no smearing, no pressure variation. "
            "A person holding glass leaves partials. Those were pressed deliberately. "
            "Someone put them there.";
        if(i==2) return
            "Yes I was there. I needed air. I smoke when I cannot sleep. "
            "I saw Fiona go in and come out. I saw someone go in after her. "
            "I could not see who. The light was wrong.";
        return "";
    }

    string getIdleResponse()const override {
        return "Derek looks up slowly. His coffee sits untouched. "
               "'I know why you are here,' he says. 'Everyone knows.'";
    }

    string getAccusedResponse()const override {
        return "Derek goes very still. 'You are wrong.' He does not crumble. "
               "He looks at you with something like pity. "
               "'You are wrong and you know it. Keep looking.'";
    }

    string getInnocentResponse()const override {
        return "'I told you it was not me. Whoever did this is still in that house.'";
    }

    string getKillerConfession()const override {
        return "'You found the flaw.' He almost smiles. "
               "'Four years writing that script taught me to plan every scene. "
               "I planned this one forsix months. Every plant, every misdirection — "
               "it was a script. Victor always said I had no instinct fordrama. "
               "Tonight proved him wrong.'";
    }

    string getMisdirection()const override {
        return "I saw Marcus near the kitchen earlier. Before the party started. "
               "He was alone in there fora long time.";
    }

    string getPlantingStyle()const override {
        return "Meticulous and over-prepared. Every planted detail is "
               "technically correct — which is the flaw. Real evidence is messy. "
               "His plants read like a screenplay:too clean, too purposeful.";
    }

    void displayProfile()const override {
        ASCII::suspectArt("Derek Mann");
        cout<<Color::BLUE;
        cout<<"  DEREK MANN — Screenwriter, 42.\n";
        cout<<"  Wrote the script forReckoning over four years.\n";
        cout<<"  Script was drawn from his own father's illness and death.\n";
        cout<<"  Victor removed his credit six weeks before release\n";
        cout<<"  and claimed the story as his own. Film made 82 million.\n";
        cout<<Color::RESET;
    }
};
class Fiona:public Suspect {
public:
    Fiona():Suspect(
        "Fiona Grey",
        "Composed. Precise. Watches every exit.",
        "Lead Actress",
        "Victor blacklisted her then promised her career back ifshe "
        "stayed silent. She waited five years. Tonight he gave her "
        "promised role to someone else. She found out at 6:30 PM."
    ) {}

    string getQuestion(int i)const override {
        if(i==0) return "The poison vial found in your dressing room.";
        if(i==1) return "You were seen entering the study at 9:15 PM.";
        if(i==2) return "You threatened him by text. 'This ends tonight.'";
        return "";
    }

    string getResponse(int i)const override {
        if(i==0) return
            "That is not mine. The door was unlocked all evening. "
            "My fingerprints are on the case — not on the vial itself. "
            "Someone put it there to be found.";
        if(i==1) return
            "Yes. I went to confront him about the casting. "
            "He told me the role was filled. Said it without apology. "
            "I was inside less than two minutes. Then I left.";
        if(i==2) return
            "I sent that at seven o'clock. Three hours before he died. "
            "I meant I was going to the press with what he did to me. "
            "ifI planned murder would I announce it in writing first?";
        return "";
    }

    string getIdleResponse()const override {
        return "Fiona stands at the window. She turns slowly. "
               "'I have been expecting someone,' she says. 'Ask what you need.'";
    }

    string getAccusedResponse()const override {
        return "'You are making a mistake.' Not a plea. A statement. "
               "'I have been accused by powerful men before. "
               "It did not end well forthem.'";
    }

    string getInnocentResponse()const override {
        return "'I told you exactly what happened. Find who actually did this "
               "before they walk out of this house.'";
    }

    string getKillerConfession()const override {
        return "'Five years.' Her voice is completely flat. "
               "'Five years I protected him. Waited. "
               "I found out about the casting at six-thirty. "
               "I had two hours to decide. I decided.' "
               "A pause. 'I am not sorry.'";
    }

    string getMisdirection()const override {
        return "Derek was asking the catering staff about Victor's private "
               "whiskey bottle earlier. Specifically which one was his. "
               "I thought it was odd.";
    }

    string getPlantingStyle()const override {
        return "Fast and instinctive. Her plants are almost correct but she "
               "moved quickly and trusted her composure to carry her. "
               "One detail has a timestamp that does not survive scrutiny.";
    }

    void displayProfile()const override {
        ASCII::suspectArt("Fiona Grey");
        cout<<Color::MAGENTA;
        cout<<"  FIONA GREY — Lead Actress, 34.\n";
        cout<<"  Victor blacklisted her five years ago.\n";
        cout<<"  Offered her career back in exchange forsilence.\n";
        cout<<"  She waited. Tonight he gave her role to someone else.\n";
        cout<<"  She found out at 6:30 PM — ninety minutes before the party.\n";
        cout<<Color::RESET;
    }
};
class Marcus:public Suspect {
public:
    Marcus():Suspect(
        "Marcus Webb",
        "Barely contained. Drinks steadily. Laughs at wrong moments.",
        "Director",
        "Victor spent six years quietly blocking Marcus from every major "
        "project to keep him desperate and cheap. Marcus found out "
        "two weeks ago through a forwarded email."
    ) {}
    string getQuestion(int i)const override {
        if(i==0) return "Victor's letter — keeping you hungry on purpose.";
        if(i==1) return "Your handkerchief was found near the decanter.";
        if(i==2) return "The voice memo on your phone. 'Tonight Victor dies.'";
        return "";
    }
    string getResponse(int i)const override {
        if(i==0) return
            "Two weeks ago someone forwarded me an email. "
            "Victor to a studio head four years ago:'Keep Webb hungry — "
            "he takes better deals when desperate.' "
            "Six years of my career was a management strategy.";
        if(i==1) return
            "I confronted Victor before the party. Screamed at him for"
            "twenty minutes. He was completely calm. The handkerchief "
            "must have fallen then — I was near the cabinet. "
            "I did not touch the decanter.";
        if(i==2) return
            "Dark humour. My editor and I talk like that. "
            "ifI was planning something I would not record it on my own phone. "
            "My car was unlocked. Someone found that memo deliberately.";
        return "";
    }
    string getIdleResponse()const override {
        return "Marcus has a drink in his hand. He does not pretend. "
               "'I hated the man,' he says immediately. 'Ask what you want.'";
    }
    string getAccusedResponse()const override {
        return "Marcus laughs — short and bitter. 'Of course. The angry director.' "
               "He sets down his glass. 'I did not do it. "
               "But I understand why you think I did.'";
    }

    string getInnocentResponse()const override {
        return "'I told you my car was unlocked. Someone found that memo on purpose. "
               "You had everything you needed and still picked me.'";
    }

    string getKillerConfession()const override {
        return "'Fourteen days.' He is almost calm now. "
               "'I kept thinking I would talk myself out of it. I did not.' "
               "He looks at his hands. 'Six years. He thought of me as a line item. "
               "I decided to be something he could not budget for.'";
    }

    string getMisdirection()const override {
        return "Fiona was in Victor's study before the party started. "
               "I saw her go in. She looked like she was searching forsomething.";
    }

    string getPlantingStyle()const override {
        return "Theatrical. Almost cinematic. His planted evidence is arranged "
               "formaximum dramatic impact — exactly where a director would "
               "put it fora scene. Real criminals do not frame others "
               "with this kind of visual instinct. That is the tell.";
    }

    void displayProfile()const override {
        ASCII::suspectArt("Marcus Webb");
        cout<<Color::YELLOW;
        cout<<"  MARCUS WEBB — Director, 51.\n";
        cout<<"  Victor quietly blocked him from every major project\n";
        cout<<"  forsix years to keep him desperate and available cheap.\n";
        cout<<"  Marcus found out two weeks ago via a forwarded email.\n";
        cout<<"  Has not worked in eighteen months.\n";
        cout<<Color::RESET;
    }
};
class Leo:public Suspect {
public:
    Leo():Suspect(
        "Leo Hart",
        "Still. Patient. Seems to be everywhere and nowhere at once.",
        "Butler",
        "Served Victor Cross forthirty years. Found out he was quietly "
        "removed from the will by reading a letter not meant forhim."
    ) {}

    string getQuestion(int i)const override {
        if(i==0) return "The original security footage — you are on it.";
        if(i==1) return "The gloves in your quarters. Three suspects' traces.";
        if(i==2) return "Why, Leo?";
        return "";
    }

    string getResponse(int i)const override {
        if(i==0) return
            "'You found the backup drive.' A pause. "
            "'I was thorough. I missed one copy. "
            "Yes — I edited the recording. Twelve seconds. "
            "Enough to change the story.'";
        if(i==1) return
            "'Derek's tobacco. Fiona's hair. Marcus's cologne. Yes. "
            "I was careful about which traces I left where. "
            "Not careful enough, it seems.'";
        if(i==2) return
            "'Thirty years. I found the letter on a Tuesday. "
            "He was in the next room. I finished setting the table. "
            "I served him his drink. I went to bed. "
            "And I understood that I had given everything to a man "
            "who had simply forgotten I existed. "
            "Not malice. Just forgetting. "
            "That was the part I could not survive.'";
        return "";
    }

    string getIdleResponse()const override {
        return "Leo stands at the edge of the room, hands clasped. "
               "'Of course, detective. I will help however I can.'";
    }

    string getAccusedResponse()const override {
        return "Leo is quiet fora long time. "
               "Then:'You found everything.' "
               "It is not a question. He sits down carefully. "
               "'What would you like to know?'";
    }

    string getInnocentResponse()const override {
        return ""; // Leo is never innocent
    }

    string getKillerConfession()const override {
        return "'I gave him thirty years.' His voice does not change. "
               "'I found the letter on a Tuesday evening. "
               "I served him his drink and said nothing. "
               "Three weeks deciding. Six weeks preparing. "
               "I studied all of them — Derek's bitterness, "
               "Fiona's anger, Marcus's rage. "
               "I gave you three perfect suspects. You almost stopped. "
               "You did not.' He looks at you. 'I respect that.'";
    }

    string getMisdirection()const override {
        return "I do not wish to speak out of turn — but one of the guests "
               "was asking about Mr Cross's private whiskey bottle earlier. "
               "Specifically which decanter was his.";
    }

    string getPlantingStyle()const override {
        return "Invisible and patient. Thirty years moving through this house "
               "unseen made him the perfect planter. His work is the cleanest. "
               "But that invisibility is itself the tell — there is no record "
               "of Leo being anywhere specific that evening. "
               "forthe man running the party, that is impossible.";
    }

    void displayProfile()const override {
        ASCII::suspectArt("Leo Hart");
        cout<<Color::WHITE;
        cout<<"  LEO HART — Butler, 54.\n";
        cout<<"  Has served Victor Cross forthirty years.\n";
        cout<<"  No family. No property. Victor was his entire world.\n";
        cout<<"  Quietly removed from the will without being told.\n";
        cout<<"  Appears to have no motive whatsoever.\n";
        cout<<Color::RESET;
    }
};
