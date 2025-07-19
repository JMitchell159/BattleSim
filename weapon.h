#pragma once

typedef enum WeaponType {
    AXE,
    CLUB,
    DAGGER,
    FIST,
    HAMMER,
    KATANA,
    MACE,
    SHIELD,
    SPEAR,
    SWORD
} weapon_type_t;

typedef enum DamageType {
    BLUNT,
    PIERCING,
    SLASHING
} damage_type_t;

typedef enum EffectType {
    BLEED,
    POISON,
    STUN,
    NONE
} effect_type_t;

typedef struct Weapon {
    weapon_type_t wt;
    damage_type_t dt;
    int num_attacks;
    int damage;
    effect_type_t et;
    int effect_damage;
    float effect_percent;
} weapon_t;

weapon_t create_weapon(weapon_type_t wt, damage_type_t dt, int num_attacks, int damage, effect_type_t et, int effect_damage, float effect_percent);