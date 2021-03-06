#include "source/sprites/collision.h"
#include "source/library/bank_helpers.h"
#include "source/globals.h"

CODE_BANK(PRG_BANK_SPRITE_COLLISION);
ZEROPAGE_DEF(unsigned char, collisionTemp);

unsigned char test_collision(unsigned char tileId, unsigned char isPlayer) {
    // The top 2 bits of the tile id are the palette color. We don't care about that here, so skip them.
    collisionTemp = tileId & 0x3f;

    switch (collisionTemp) {
        case 2: // Grass
            return 0;
        case 32: // Water
        case 33:
            return (currentLayer == LAYER_DESERT || currentLayer == LAYER_STONE) ? 0 : 1;
        case 26: // Rock
            return currentLayer > LAYER_CALM ? 0 : 1;
        case 25: // tree
            return currentLayer > LAYER_DESERT ? 0 : 1;
        case 29: // fence
            return currentLayer > LAYER_STONE ? 0 : 1;
        case 27: // tree (evergreen)
        case 31: // Rock (permanent)
            return 1; // Eternal tree
        case 28: // pillar
            return currentLayer > LAYER_DESERT ? 1 : 0;
        case 30: // vine
            return (currentLayer == LAYER_CALM || currentLayer > LAYER_DESERT) ? 1 : 0;
        case 35: // flower
            return currentLayer == LAYER_CALM ? 1 : 0;
        case 36: // vine bridge
        case 37: // ditto
            return currentLayer == LAYER_NORMAL || currentLayer == LAYER_DESERT || currentLayer > LAYER_STONE;
        case 38: // Otherworld tiles
            return 0;
        case 39: // Desert tile
            return currentLayer >= LAYER_DESERT ? 1 : 0;
        case 40: // Brikx
            return currentLayer == LAYER_CALM ? 0 : 1;
        case 41: // DKPillar
            return currentLayer == LAYER_DARKSTONE || currentLayer == LAYER_DARKNESS ? 1 : 0;


        // Else continue and use default logic

    }

    if (collisionTemp >= FIRST_SOLID_SPRITE && collisionTemp <= LAST_SOLID_SPRITE) {
        return 1;
    }
    return 0;
}