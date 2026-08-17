#pragma once
#include <string>
#include "Player.h"
#include "Zombie.h"
#include "Queue.hpp"
#include "LinkedList.hpp"

class Game {
private:
    Player  player;
    int     day        = 1;
    int     maxDays    = 30;
    bool    running    = true;

    // Đàn zombie trong ngày — LinkedList để duyệt hiển thị hàng chờ
    LinkedList<Zombie> herd;
    int totalZombiesDay = 0;  // tổng số zombie ngày này
    int killedToday     = 0;

    // Log chiến đấu (hiện 4 dòng gần nhất)
    Queue<std::string> battleLog;

public:
    void run();

private:
    // Tiện ích
    void   cls();
    void   pause();
    int    getInt(int lo, int hi);
    void   log(const std::string& msg);

    // Render
    void   drawHBar(const std::string& lbl, int val, int maxVal, int width, char fill, char empty);
    void   drawHerd();
    void   drawBattleUI(const Zombie& z);
    void   drawVictoryScreen();
    void   drawGameOver(const std::string& reason);
    void   drawDaySummary(int expGained, bool leveledUp);
    void   drawDayIntro();

    // Game flow
    void   buildHerd();
    bool   fightOne(Zombie& z);   // trả về true nếu người chơi còn sống
    void   playDay();
    int    applySkill(int skillIdx, Zombie& z);  // trả về dmg dealt (âm = heal)
};
