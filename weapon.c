#include "weapon.h"

weapon_t create_weapon(weapon_type_t wt, damage_type_t dt, int num_attacks, int damage, effect_type_t et, int effect_damage, float effect_percent) {
    weapon_t w = {
        .wt = wt,
        .dt = dt,
        .num_attacks = num_attacks,
        .damage = damage,
        .et = et,
        .effect_damage = effect_damage,
        .effect_percent = effect_percent
    };
    return w;
}