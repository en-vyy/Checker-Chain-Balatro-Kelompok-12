#pragma once
#include "RunSessionState.h"
#include "ModifierManager.h"

class ShopManager {
public:
    // Fungsi utama untuk menjalankan fase toko.
    // Kita mengirimkan state (untuk memotong uang) dan modifierManager (untuk memasukkan Joker).
    void enterShop(RunSessionState& state, ModifierManager& modifierManager);
};