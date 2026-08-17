#pragma once
#include <string>

struct Zombie {
    std::string name;
    std::string emoji;   // ký tự ASCII đại diện
    int hp;
    int maxHp;
    int attack;
    int defense;
    int expReward;
    int level;

    // Kỹ năng đặc biệt zombie (xác suất kích hoạt)
    std::string specialName;
    int specialDmg;
    int specialChance; // %
};

// Tạo zombie theo ngày/level
inline Zombie makeZombie(int day, int index) {
    Zombie z;
    int tier = (day - 1) / 3; // tier tăng mỗi 3 ngày
    if (tier > 4) tier = 4;

    // Pool zombie theo tier
    struct ZTemplate { const char* name; const char* emoji; int hp; int atk; int def; int exp; const char* spName; int spDmg; int spChance; };

    ZTemplate pool[][4] = {
        // Tier 0
        {
            {"Normal Zombie",  "[Z]",  30,  8, 0, 10, "Bite",    5,  20},
            {"Starved Zombie","[z]",  25,  6, 0,  8, "Scream",    0,  15},
            {"Claw Zombie",    "[Z]",  35, 10, 1, 12, "Slash",   8,  25},
            {"Old Zombie",     "[z]",  20,  5, 0,  7, "Innocent",   3,  10},
        },
        // Tier 1
        {
            {"Running Zombie",    "[R]",  45, 12, 1, 18, "Lunge Forward",   10,  30},
            {"Huge Zombie",      "[B]",  60, 14, 3, 20, "Headfirst",  15,  20},
            {"Poisoned Zombie",     "[P]",  40, 10, 0, 22, "Poison Spray",  12,  35},
            {"Armored Zombie",    "[A]",  55,  9, 5, 19, "Armor", 0,  25},
        },
        // Tier 2
        {
            {"Mutated Zombie","[M]", 70, 16, 2, 30, "Transform", 18,  25},
            {"Screaming Zombie",     "[S]",  65, 18, 1, 32, "Scream",    0,  20},
            {"Acid Zombie",    "[E]",  55, 14, 0, 35, "Explode",   25,  15},
            {"Freezing Zombie",    "[I]",  75, 13, 4, 28, "Icy Breath",  10,  30},
        },
        // Tier 3
        {
            {"Not giving up Zombie",  "[G]",  90, 22, 5, 45, "Cling till the dead",  28,  30},
            {"Insect Zombie",  "[C]", 100, 20, 3, 48, "Insect Swarm",   22,  25},
            {"Doctor Zombie",    "[Y]",  85, 25, 2, 50, "Poison Inject",  20,  40},
            {"King Zombie",     "[K]", 110, 18, 8, 55, "Command",   30,  20},
        },
        // Tier 4 - Boss-like
        {
            {"ENORMOUS ZOMBIE","[X]", 150, 30, 8, 80, "Huge Body Huge HP Bar",  40,  30},
            {"DEMON KING ZOMBIE","[W]", 130, 35, 5, 85, "Soul Capturing",   35,  35},
            {"TITAN ZOMBIE",   "[T]", 180, 28,12, 90, "Smaller than Enormous Zombie",   45,  20},
            {"GOD ZOMBIE",    "[D]", 160, 32,10, 95, "Celestial Strike",  50,  25},
        },
    };

    int idx = index % 4;
    ZTemplate& t = pool[tier][idx];

    z.name        = t.name;
    z.emoji       = t.emoji;
    z.level       = day + tier;
    z.maxHp       = t.hp  + day * 3;
    z.hp          = z.maxHp;
    z.attack      = t.atk + day * 1;
    z.defense     = t.def;
    z.expReward   = t.exp + day * 2;
    z.specialName = t.spName;
    z.specialDmg  = t.spDmg + day / 2;
    z.specialChance = t.spChance;

    return z;
}
