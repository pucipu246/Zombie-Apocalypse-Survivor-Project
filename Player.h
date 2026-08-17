#pragma once
#include <string>

struct Skill {
    std::string name;
    std::string desc;
    int damage;      // 0 = không gây damage trực tiếp
    int heal;        // HP hồi phục
    int mpCost;      // 0 = không cần MP (game này dùng "Stamina" thay MP)
    int cooldown;    // số lượt cooldown
    int currentCD;   // còn lại bao nhiêu lượt
};

struct Player {
    std::string name;
    int level   = 1;
    int exp     = 0;
    int expNext = 30;  // exp cần để lên cấp

    int hp;
    int maxHp   = 100;
    int stamina;
    int maxStamina = 50;

    int attack  = 12;
    int defense = 2;
    int speed   = 10;

    int potions = 3;   // thuốc hồi máu (+40HP mỗi cái)

    // Danh sách skill (tối đa 6)
    Skill skills[6];
    int skillCount = 0;

    // Guard: giảm 50% sát thương lượt này
    bool isGuarding = false;

    // Buff/debuff tạm thời
    int atkBuff  = 0;  // cộng thêm vào attack (tắt sau lượt)
    int defBuff  = 0;

    Player() {
        name    = "Player";
        hp      = maxHp;
        stamina = maxStamina;
        // Skill mặc định cấp 1
        addSkill({"Normal attack", "Normal attack",           15, 0,  0, 0, 0});
        addSkill({"Defend",   "Reduce enemy's damage by 50%",   0, 0,  0, 2, 0});
        addSkill({"Use medicines",  "Heal 40 HP",         0,40,  0, 3, 0});
    }

    void addSkill(const Skill& s) {
        if (skillCount < 6) skills[skillCount++] = s;
    }

    // Gọi khi lên cấp
    void onLevelUp() {
        maxHp      += 15;
        hp          = maxHp;
        maxStamina += 5;
        stamina     = maxStamina;
        attack     += 3;
        defense    += 1;

        // Mở skill theo cấp
        if (level == 2)  addSkill({"Shoot",    "Long range, +5 speed",       22, 0, 10, 1, 0});
        if (level == 3)  addSkill({"Throw bomb", "Area damage x2",  30, 0, 20, 2, 0});
        if (level == 4)  addSkill({"Rage",    "Recieve 10 ATK for one move", 0, 0, 15, 3, 0});
        if (level == 5)  addSkill({"Deadly",   "Critical shot with x3 dmg!",     45, 0, 30, 4, 0});
        if (level >= 6)  addSkill({"Celestial Dance",    "Heal and attack with 20 dmg", 20, 25, 25, 3, 0});
    }

    void gainExp(int e) {
        exp += e;
        while (exp >= expNext) {
            exp    -= expNext;
            level++;
            expNext = 30 + level * 20;
            onLevelUp();
        }
    }

    void tickCooldowns() {
        for (int i = 0; i < skillCount; i++)
            if (skills[i].currentCD > 0) skills[i].currentCD--;
        isGuarding = false;
        atkBuff    = 0;
        defBuff    = 0;
    }
};
