#include <stdio.h>

#include "weapon.h"

weapon_t create_weapon(weapon_type_t wt, damage_type_t dt, int num_attacks, int damage, effect_type_t et, int effect_damage, float effect_percent) {
    weapon_t w = {
        .weapon_type = wt,
        .damage_type = dt,
        .num_attacks = num_attacks,
        .damage = damage,
        .effect_type = et,
        .effect_damage = effect_damage,
        .effect_percent = effect_percent
    };
    return w;
}

int weapon_rank(weapon_t weapon) {
    int result = 0;
    switch(weapon.effect_type) {
        case POISON:
            return 4;
        case STUN:
            return 3;
        case BLEED:
            return 2;
        default:
            return 1;
    }
}

void print_weapon(weapon_t weapon) {
    printf("Weapon Type: ");
    switch(weapon.weapon_type) {
        case AXE:
            printf("AXE\n");
            break;
        case CLUB:
            printf("CLUB\n");
            break;
        case DAGGER:
            printf("DAGGER\n");
            break;
        case FIST:
            printf("FIST\n");
            break;
        case HAMMER:
            printf("HAMMER\n");
            break;
        case KATANA:
            printf("KATANA\n");
            break;
        case MACE:
            printf("MACE\n");
            break;
        case SHIELD:
            printf("SHIELD\n");
            break;
        case SPEAR:
            printf("SPEAR\n");
            break;
        case SWORD:
            printf("SWORD\n");
            break;
    }
    printf("Damage Type: ");
    switch(weapon.damage_type) {
        case BLUNT:
            printf("BLUNT\n");
            break;
        case PIERCING:
            printf("PIERCING\n");
            break;
        case SLASHING:
            printf("SLASHING\n");
            break;
    }
    printf("Number of Attacks: %d\n", weapon.num_attacks);
    printf("Damage: %d\n", weapon.damage);
    printf("Effect Type: ");
    switch(weapon.effect_type) {
        case BLEED:
            printf("BLEED\n");
            break;
        case BLOCK:
            printf("BLOCK\n");
            break;
        case POISON:
            printf("POISON\n");
            break;
        case STUN:
            printf("STUN\n");
            break;
        default:
            printf("NONE\n");
            break;
    }
    printf("Effect Damage: %d\n", weapon.effect_damage);
    printf("Effect Percent: %.2f\n", weapon.effect_percent);
}