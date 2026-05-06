#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <thread>
#include <chrono>
#ifdef _WIN32
    #include <windows.h>
    inline void sleepMs(int ms){
        Sleep(ms); 
    }
#else
    #include <thread>
    #include <chrono>
    inline void sleepMs(int ms){
        this_thread::sleep_for(chrono::milliseconds(ms));
    }
#endif
inline void enableConsole() {
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    SetConsoleOutputCP(CP_UTF8);
#endif
}
namespace Color {
const string RESET="\033[0m";
const string RED="\033[31m";
const string GREEN="\033[32m";
const string YELLOW="\033[33m";
const string BLUE="\033[34m";
const string MAGENTA="\033[35m";
const string CYAN="\033[36m";
const string WHITE="\033[37m";
const string BOLD="\033[1m";
const string DIM="\033[2m";
}
namespace UI {
    inline void typewrite(const string& text, int delay=20,const string& color="") {
        if(!color.empty()) cout<<color;
        for(char c:text) {
            cout<<c;
            sleepMs(delay);
        }
        if(!color.empty()) cout<<Color::RESET;
        cout<<"\n";
    }

    inline void slow(const string& text,const string& color="") {
        typewrite(text, 32, color);
    }

    inline void print(const string& text,const string& color="") {
        if(!color.empty()) cout<<color;
        cout<<text<<Color::RESET<<"\n";
    }

    inline void divider(char c='-', int len=62) {
        cout<<Color::DIM;
        for(int i=0;i<len;i++) cout<<c;
        cout<<Color::RESET<<"\n";
    }

    inline void header(const string& text) {
        cout<<"\n";
        divider('=');
        cout<<Color::BOLD<<Color::YELLOW<<"  "<<text<<Color::RESET<<"\n";
        divider('=');
        cout<<"\n";
    }
    inline void pressEnter(){
        cout<<Color::DIM<<"\n  [ Press ENTER to continue... ]"<<Color::RESET;
        cin.ignore(10000, '\n');
    }
    inline void clearScreen() {
        cout<<"\033[2J\033[1;1H";
    }
    inline void pause(int ms=600){
        sleepMs(ms);
    }
}

namespace ASCII {

    inline void mansion() {
        cout<<Color::YELLOW<<"  [Mansion]\n"<<Color::RESET;
    }

    inline void victim() {
        cout<<Color::RED<<"  [Victor Cross - Deceased]\n"<<Color::RESET;
    }

    inline void suspectArt(const string& name) {
        cout<<Color::CYAN<<"  ["<<name<<"]\n"<<Color::RESET;
    }

    inline void solvedArt() {
        cout<<Color::GREEN<<"\n  CASE SOLVED\n"<<Color::RESET;
    }

    inline void wrongArt() {
        cout<<Color::RED<<"\n  WRONG ACCUSATION\n"<<Color::RESET;
    }
    inline void casefile() {
        cout<<Color::YELLOW<<"\n  CASE FILE\n"<<Color::RESET;
    }
}