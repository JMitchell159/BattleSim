#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "team.h"

unit_t create_unit(weapon_t primary, weapon_t secondary, int team_id, int health, int speed, float block_chance, float dodge_chance) {
    unit_t unit = {
        .primary = primary,
        .secondary = secondary,
        .team_id = team_id,
        .health = health,
        .speed = speed,
        .bleed_percent = 0.0,
        .poison_percent = 0.0,
        .stun_percent = 0.0,
        .stun_instances = 0,
        .block_chance = block_chance,
        .dodge_chance = dodge_chance
    };
    if(secondary.effect_type == BLOCK) unit.block_chance += secondary.effect_percent;
    return unit;
}

team_t create_team(unit_t* units, char *name, int team_id) {
    team_t team = {
        .units = units,
        .name = name,
        .size = sizeof(units) / sizeof(units[0]),
        .team_id = team_id
    };
    return team;
}

void print_team(team_t t) {
    printf("%s\n", t.name);
    char empty[] = "";
    char line1[4 * t.size + 2];
    strcpy(line1, empty);
    strcat(line1, "=");
    for(int i = 0; i < t.size; i++) {
        strcat(line1, "====");
    }
    strcat(line1, "=\n");
    printf("%s", line1);
    char line2[4 * t.size + 2];
    strcpy(line2, empty);
    strcat(line2, "|");
    for(int i = 0; i < t.size; i++) {
        strcat(line2, "\\|/ ");
    }
    strcat(line2, "|\n");
    printf("%s", line2);
    char line3[4 * t.size + 2];
    strcpy(line3, empty);
    strcat(line3, "|");
    for(int i = 0; i < t.size; i++) {
        strcat(line3, "(_) ");
    }
    strcat(line3, "|\n");
    printf("%s", line3);
    char line4[4 * t.size + 2];
    strcpy(line4, empty);
    strcat(line4, "|");
    for(int i = 0; i < t.size; i++) {
        strcat(line4, "\\|/ ");
    }
    strcat(line4, "|\n");
    printf("%s", line4);
    char line5[4 * t.size + 2];
    strcpy(line5, empty);
    strcat(line5, "|");
    for(int i = 0; i < t.size; i++) {
        strcat(line5, "/ \\ ");
    }
    strcat(line5, "|\n");
    printf("%s", line5);
    char line6[4 * t.size + 2];
    strcpy(line6, empty);
    strcat(line6, "=");
    for(int i = 0; i < t.size; i++) {
        strcat(line6, "====");
    }
    strcat(line6, "=\n");
    printf("%s", line6);
}

unit_t attack(unit_t attacker, bool is_primary, unit_t defender) {
    float to_hit = (float)(rand() % 100 + 1)/100.0;
    float avoid_chance = defender.block_chance + defender.dodge_chance * (1 - defender.block_chance);
    if(avoid_chance >= to_hit) {
        printf("miss\n");
        return defender;
    }

    printf("hit\n");

    if(is_primary) {
        defender.health -= attacker.primary.damage;
        switch(attacker.primary.effect_type) {
            case BLEED:
                defender.bleed_percent += attacker.primary.effect_percent;
                if(defender.bleed_percent >= 1.0) {
                    defender.health -= attacker.primary.effect_damage;
                    defender.bleed_percent -= 1.0;
                }
                break;
            case POISON:
                defender.poison_percent += attacker.primary.effect_percent;
                if(defender.poison_percent > 1.0) defender.poison_percent = 1.0;
                break;
            case STUN:
                defender.stun_percent += attacker.primary.effect_percent;
                if(defender.stun_percent >= 1.0) {
                    defender.stun_instances++;
                    defender.stun_percent -= 1.0;
                }
                break;
        }
        return defender;
    }

    defender.health -= attacker.secondary.damage;
    switch(attacker.secondary.effect_type) {
        case BLEED:
            defender.bleed_percent += attacker.secondary.effect_percent;
            if(defender.bleed_percent >= 1.0) {
                defender.health -= attacker.secondary.effect_damage;
                defender.bleed_percent -= 1.0;
            }
            break;
        case POISON:
            defender.poison_percent += attacker.secondary.effect_percent;
            if(defender.poison_percent > 1.0) defender.poison_percent = 1.0;
            break;
        case STUN:
            defender.stun_percent += attacker.secondary.effect_percent;
            if(defender.stun_percent >= 1.0) {
                defender.stun_instances++;
                defender.stun_percent -= 1.0;
            }
            break;
    }
    return defender;
}