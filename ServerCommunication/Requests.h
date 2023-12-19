#pragma once

enum class Request
{
    SetItem = 1,
    SetItemPrice = 2,
    SetItemSlot = 3,
    DeleteItem = 4,
    BlockItem = 5,
    UnblockItem = 6,
    GetCurrBalance = 7,
    SetBalance = 8,
    GetStatistic = 9,
    GetError = 10,
};
