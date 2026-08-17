#include "Game.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;

// ================= UTIL =================

void Game::cls() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Game::pause() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

int Game::getInt(int lo, int hi) {
    int x;
    while (true) {
        cout << "\nChoice >> ";
        if (cin >> x && x >= lo && x <= hi) {
            cin.ignore(1000, '\n');
            return x;
        }
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void Game::log(const string& msg) {
    battleLog.enqueue(msg);
    if (battleLog.size() > 5) battleLog.dequeue();
}

// ================= UI =================

void Game::drawHBar(const string& lbl, int val, int maxVal, int width, char fill, char empty) {
    if (maxVal <= 0) maxVal = 1;

    int filled = val * width / maxVal;

    cout << lbl << " [";
    for (int i = 0; i < filled; i++) cout << fill;
    for (int i = filled; i < width; i++) cout << empty;
    cout << "] " << val << "/" << maxVal;
}

void Game::drawHerd() {
    cout << "\nNEXT: ";
    Node<Zombie>* cur = herd.head;
    int shown = 0;

    while (cur && shown < 5) {
        cout << cur->data.emoji << " ";
        cur = cur->next;
        shown++;
    }

    if (herd.length > 5)
        cout << "(+" << herd.length - 5 << ")";
    cout << "\n";
}

void Game::drawBattleUI(const Zombie& z) {
    cls();

    cout << "====================================================\n";
    cout << " DAY " << day << " | LEVEL " << player.level
         << " | ZOMBIE " << killedToday << "/" << totalZombiesDay << "\n";
    cout << "====================================================\n\n";

    cout << z.name << " " << z.emoji << " Lv." << z.level << "\n";

    drawHBar("HP ", z.hp, z.maxHp, 20, '#', '-');

    cout << "\nATK: " << z.attack
     << " | DEF: " << z.defense << "\n";

    cout << "SKILL: "
     << z.specialName
     << " (" << z.specialDmg
     << " DMG, "
     << z.specialChance
     << "%)\n";

    drawHerd();

    cout << "\n----------------------------------------------------\n";


    cout << "[ "<<player.name <<" ]" << "\n";

    drawHBar("HP ", player.hp, player.maxHp, 20, '#', '-');
    cout << "\n";

    drawHBar("STM", player.stamina, player.maxStamina, 20, '#', '-');
    cout << "\n";

    drawHBar("EXP", player.exp, player.expNext, 20, '#', '-');
    cout << "\n";

    cout << "ATK: " << player.attack + player.atkBuff
         << " | DEF: " << player.defense + player.defBuff
         << " | MED: " << player.potions << "\n";

    cout << "\n----------------------------------------------------\n";
    cout << "Recent Actions\n";

    Queue<string> tmp = battleLog;
    while (!tmp.empty()) {
        cout << " * " << tmp.front() << "\n";
        tmp.dequeue();
    }

    cout << "\n----------------------------------------------------\n";
    cout << "Skills\n";

    for (int i = 0; i < player.skillCount; i++) {
        Skill& s = player.skills[i];

        cout << "[" << i + 1 << "] " << s.name;

        if (s.currentCD > 0)
            cout << " (CD:" << s.currentCD << ")";
        else if (s.mpCost > 0)
            cout << " (STM:" << s.mpCost << ")";

        cout << "\n";
    }
}

void Game::drawDayIntro() {
    cls();
    cout << "==================== DAY " << day << "/" << maxDays << " ====================\n";
    cout << totalZombiesDay << " zombies detected.\n";
    cout << "Player Level: " << player.level << "\n";
    pause();
}

void Game::drawDaySummary(int expGained, bool leveledUp) {
    cls();

    cout << "================ DAY COMPLETE ================\n";
    cout << "Killed: " << killedToday << "/" << totalZombiesDay << "\n";
    cout << "EXP: +" << expGained << "\n";

    if (leveledUp)
        cout << "LEVEL UP! -> " << player.level << "\n";

    cout << "HP: " << player.hp << "/" << player.maxHp << "\n";

    player.stamina += 20;
    if (player.stamina > player.maxStamina)
        player.stamina = player.maxStamina;

    pause();
}

void Game::drawVictoryScreen() {
    cls();
    cout << "\n========== VICTORY ==========\n";
    cout << "You survived " << maxDays << " days.\n";
    cout << "Final Level: " << player.level << "\n";
}

void Game::drawGameOver(const string& reason) {
    cls();
    cout << "\n========== GAME OVER ==========\n";
    cout << reason << "\n";
    cout << "Survived: " << day - 1 << " days\n";
}

// ================= COMBAT =================

int Game::applySkill(int idx, Zombie& z) {
    Skill& s = player.skills[idx];

    if (s.currentCD > 0) return -999;
    if (player.stamina < s.mpCost) return -999;

    player.stamina -= s.mpCost;
    s.currentCD = s.cooldown;

    if (s.name == "Defend") {
        player.isGuarding = true;
        log("Defending");
        return 0;
    }

    if (s.name == "Use medicines") {
        if (player.potions <= 0) return -999;

        player.potions--;
        player.hp += s.heal;

        if (player.hp > player.maxHp)
            player.hp = player.maxHp;

        log("Used medicine");
        return -s.heal;
    }

    int dmg = s.damage + player.attack;
    int real = dmg - z.defense;

    if (real < 1) real = 1;

    z.hp -= real;

    log("Used " + s.name + " for " + to_string(real) + " dmg");

    return real;
}

bool Game::fightOne(Zombie& z) {
    while (!battleLog.empty()) battleLog.dequeue();

    while (z.hp > 0 && player.hp > 0) {

        drawBattleUI(z);

        int choice = getInt(1, player.skillCount) - 1;

        if (applySkill(choice, z) == -999)
            continue;

        if (z.hp > 0) {

            int dmg = z.attack - player.defense;

            if (player.isGuarding)
                dmg /= 2;

            if (dmg < 1) dmg = 1;

            player.hp -= dmg;

            log(z.name + " dealt " + to_string(dmg));
        }

        player.tickCooldowns();

        player.stamina += 5;
        if (player.stamina > player.maxStamina)
            player.stamina = player.maxStamina;
    }

    if (player.hp <= 0)
        return false;

    killedToday++;
    return true;
}

// ================= GAME FLOW =================

void Game::buildHerd() {
    herd.clear();

    killedToday = 0;

    totalZombiesDay = 3 + day * 2;
    if (totalZombiesDay > 25)
        totalZombiesDay = 25;

    for (int i = 0; i < totalZombiesDay; i++)
        herd.insertBack(makeZombie(day, i));
}

void Game::playDay() {

    buildHerd();
    drawDayIntro();

    int oldLevel = player.level;
    int totalExp = 0;

    while (herd.length > 0 && player.hp > 0) {

        Zombie z = herd.head->data;
        herd.removeAt(0);

        if (!fightOne(z)) {
            drawGameOver("Killed by " + z.name);
            running = false;
            return;
        }

        totalExp += z.expReward;
        player.gainExp(z.expReward);
    }

    bool levelup = player.level > oldLevel;

    drawDaySummary(totalExp, levelup);
}

void Game::run() {

    cls();

    cout << "==============================================\n";
    cout << "           ZOMBIE SURVIVAL RPG\n";
    cout << "==============================================\n";

    cout << "\nEnter your name: ";
    getline(cin, player.name);

    if(player.name.empty())
        player.name = "Player";

    pause();

    while (running && day <= maxDays) {
        playDay();

        if (!running)
            break;

        day++;
    }

    if (running) {
        drawVictoryScreen();
        pause();
    }
}
