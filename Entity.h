#pragma once
#include<string>
#include"UI.h"
using namespace std;
class Entity{
protected:
    string name;
    string description;
public:
    Entity(string n,string d){
        name=n;
        description=d;
    }
    virtual ~Entity(){}
    virtual void display()const=0;
    string getName()const{ 
        return name; 
    }
    string getDescription()const{ 
        return description; 
    }
};
class Evidence:public Entity{
private:
    string location;     
    string examineText;  
    bool collected;    
    bool isMeta;       
public:
    Evidence(string n,string desc,string loc,string examTxt,bool meta=false):Entity(n,desc){
        location=loc;
        examineText=examTxt;
        collected=false;
        isMeta=meta;
    }
    void display()const override{
        cout<<Color::CYAN<<"  [EVIDENCE] "<<Color::RESET;
        cout<<Color::BOLD<<name<<Color::RESET<<"\n";
        cout<<Color::DIM<<"  "<<description<<Color::RESET<<"\n";
    }
    void examine()const{
        UI::divider();
        cout<<Color::BOLD<<Color::GREEN<<"  EXAMINING:"<<name<<Color::RESET<<"\n";
        UI::divider();
        UI::typewrite(examineText,16,Color::WHITE);
        UI::divider();
    }
    bool isCollected()const{
        return collected; 
    }
    bool isMetaClue()const{ 
        return isMeta;
    }
    string getLocation()const{
        return location; 
    }
    void collect(){
        collected=true;
    }
};
