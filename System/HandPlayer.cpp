#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "HandPlayer.h"

// Fungsi bantuan lokal (hanya bisa diakses di file ini)
// untuk mengubah rank menjadi teks Jack-Ace
static std::string formatRank(int rank) {
    switch (rank) {
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        case 14: return "Ace";
        default: return std::to_string(rank);
    }
}

ChosenHand HandPlayer::playHand(const Hand& generatedHand) {
    ChosenHand chosen;
    std::string inputLine;

    std::cout << "\n========================================\n";
    std::cout << "          KARTU DI TANGAN ANDA          \n";
    std::cout << "========================================\n";

    // Menampilkan kartu dengan konversi rank Jack-Ace
    for (size_t i = 0; i < generatedHand.cards.size(); i++) {
        // Memanggil fungsi formatRank di sini
        std::cout << i + 1 << ":[" << formatRank(generatedHand.cards[i].rank)
                   << " " << generatedHand.cards[i].suit << "]  ";
        //Untuk print hasil yang ada di tangan maksimal 4 menyamping
        if ((i + 1) % 4 == 0) std::cout << "\n";
    }
    std::cout << "\n\n";

    std::cout << "Pilih maksimal 5 kartu (contoh: 1 3 5), lalu Enter.\n";
    std::cout << "----------------------------------------\n";

    while (true) {
        std::cout << "Masukkan pilihan: ";
        std::getline(std::cin, inputLine);
        if (inputLine.empty()) continue;

        std::stringstream ss(inputLine);
        int input;
        bool inputValid = true;
        int cardCount = 0;
        
        chosen.cards.clear();
        std::vector<bool> isSelected(generatedHand.cards.size(), false);

        while (ss >> input) {
            cardCount++;
            if (cardCount > 5 || input < 1 || input > (int)generatedHand.cards.size() || isSelected[input - 1]) {
                inputValid = false;
                break;
            }
            chosen.addChosenCard(generatedHand.cards[input - 1]);
            isSelected[input - 1] = true;
        }

        if (inputValid && cardCount > 0) break;
        std::cout << "[!] Input tidak valid atau lebih dari 5 kartu. Silakan ulangi.\n";
    }

    // Menampilkan konfirmasi kartu yang dipilih dengan format yang sama
    std::cout << "\nKartu yang dimainkan: \n";
    for (const auto& c : chosen.cards) {
        std::cout << "[" << formatRank(c.rank) << " " << c.suit << "] ";
    }
    std::cout << "\n";
    
    return chosen;
}