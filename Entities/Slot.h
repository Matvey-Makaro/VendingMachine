#ifndef SLOT_H
#define SLOT_H

#include "Item.h"

struct Slot
{
    int id;
    Item item;
    int count;
    bool blocked = false;
    int sold = 0;
};

#endif // SLOT_H
