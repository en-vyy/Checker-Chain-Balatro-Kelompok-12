#include <iostream>
#include <string>
#include <memory>
#include "ShopManager.h"
#include "TwinEchoJoker.h"
#include "BountyHunterJoker.h"

void ShopManager::enterShop(RunSessionState& state, ModifierManager& modifierManager) {
    bool inShop = true;
    while (inShop) {
        std::cout << "\n[ T O K O ] ============================\n";
        std::cout << " Uang Anda: $" << state.money << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << " 1. Beli Twin Echo Joker ($4)\n";
        std::cout << " 2. Beli Bounty Hunter Joker ($5)\n";
        std::cout << " 3. Lanjut ke Blind Berikutnya (Keluar)\n";
        std::cout << "========================================\n";
        
        std::string shopInput;
        std::cout << "Pilih barang: ";
        std::getline(std::cin, shopInput);

        if (shopInput == "1") {
            if (state.money >= 4) {
                state.money -= 4;
                modifierManager.addModifier(std::make_unique<TwinEchoJoker>());
                std::cout << "[+] Twin Echo Joker berhasil dibeli dan aktif!\n";
                std::cout << "Toko ditutup. Melanjutkan perjalanan...\n";
                inShop = false; // Langsung menutup toko setelah berhasil beli
            } else {
                std::cout << "[X] Uang Anda tidak cukup! Pilih opsi lain.\n";
            }
        } else if (shopInput == "2") {
            if (state.money >= 5) {
                state.money -= 5;
                modifierManager.addModifier(std::make_unique<BountyHunterJoker>());
                std::cout << "[+] Bounty Hunter Joker berhasil dibeli dan aktif!\n";
                std::cout << "Toko ditutup. Melanjutkan perjalanan...\n";
                inShop = false; // Langsung menutup toko setelah berhasil beli
            } else {
                std::cout << "[X] Uang Anda tidak cukup! Pilih opsi lain.\n";
            }
        } else if (shopInput == "3") {
            std::cout << "Meninggalkan toko...\n";
            inShop = false; 
        } else {
            std::cout << "Input tidak valid!\n";
        }
    }
}