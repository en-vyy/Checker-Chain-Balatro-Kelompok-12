#include "HandPlayer.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

std::string HandPlayer::formatRank(int rank) {
    if (rank == 11) return "J";
    if (rank == 12) return "Q";
    if (rank == 13) return "K";
    if (rank == 14) return "A";
    return std::to_string(rank);
}

ChosenHand HandPlayer::playHand(Hand& currentHand) {
    std::string inputLine;
    std::cout << "\n========================================\n";
    std::cout << "          PILIH KARTU DIMAINKAN         \n";
    std::cout << "========================================\n";

    for (size_t i = 0; i < currentHand.cards.size(); i++) {
        std::cout << i + 1 << ":[" << formatRank(currentHand.cards[i].rank)
                  << " " << currentHand.cards[i].suit << "]  ";
        if ((i + 1) % 4 == 0) std::cout << "\n";
    }
    std::cout << "\n\nPilih maksimal 5 kartu (contoh: 1 3 5), lalu Enter.\n";
    std::cout << "----------------------------------------\n";

    std::vector<int> selectedIndices;
    while (true) {
        std::cout << "Masukkan pilihan: ";
        std::getline(std::cin, inputLine);
        
        std::stringstream ss(inputLine);
        int input;
        bool inputValid = true;
        selectedIndices.clear();
        std::vector<bool> isSelected(currentHand.cards.size(), false);

        while (ss >> input) {
            if (selectedIndices.size() >= 5 || input < 1 || input > (int)currentHand.cards.size() || isSelected[input - 1]) {
                inputValid = false;
                break;
            }
            selectedIndices.push_back(input - 1);
            isSelected[input - 1] = true;
        }

        if (inputValid && !selectedIndices.empty()) break;
        std::cout << "[!] Input tidak valid. Pastikan angka benar dan dipisah spasi.\n";
    }

    // Urutkan dari belakang agar saat dihapus, index di depannya tidak bergeser
    std::sort(selectedIndices.rbegin(), selectedIndices.rend());
    
    ChosenHand chosen;
    for (int index : selectedIndices) {
        chosen.cards.push_back(currentHand.cards[index]);
        // Kartu yang dimainkan langsung dihapus dari tangan
        currentHand.cards.erase(currentHand.cards.begin() + index); 
    }
    return chosen;
}

void HandPlayer::discardCards(Hand& currentHand) {
    std::string inputLine;
    std::cout << "\n========================================\n";
    std::cout << "          PILIH KARTU DIBUANG           \n";
    std::cout << "========================================\n";

    for (size_t i = 0; i < currentHand.cards.size(); i++) {
        std::cout << i + 1 << ":[" << formatRank(currentHand.cards[i].rank)
                  << " " << currentHand.cards[i].suit << "]  ";
        if ((i + 1) % 4 == 0) std::cout << "\n";
    }
    std::cout << "\n\nPilih maksimal 5 kartu untuk DIBUANG (contoh: 1 3 5), lalu Enter.\n";
    std::cout << "Kosongkan lalu tekan Enter jika batal membuang.\n";
    std::cout << "----------------------------------------\n";

    std::vector<int> cardsToRemove;
    while (true) {
        std::cout << "Masukkan pilihan: ";
        std::getline(std::cin, inputLine);
        
        if (inputLine.empty()) {
            std::cout << "Batal membuang kartu.\n";
            return; 
        }

        std::stringstream ss(inputLine);
        int input;
        bool inputValid = true;
        cardsToRemove.clear();
        std::vector<bool> isSelected(currentHand.cards.size(), false);

        while (ss >> input) {
            if (cardsToRemove.size() >= 5 || input < 1 || input > (int)currentHand.cards.size() || isSelected[input - 1]) {
                inputValid = false;
                break;
            }
            cardsToRemove.push_back(input - 1);
            isSelected[input - 1] = true;
        }

        if (inputValid && !cardsToRemove.empty()) break;
        std::cout << "[!] Input tidak valid. Pastikan angka benar dan dipisah spasi.\n";
    }

    std::sort(cardsToRemove.rbegin(), cardsToRemove.rend());
    
    std::cout << "\nKartu yang berhasil dibuang: \n";
    for (int index : cardsToRemove) {
        std::cout << "[" << formatRank(currentHand.cards[index].rank) << " " << currentHand.cards[index].suit << "] ";
        currentHand.cards.erase(currentHand.cards.begin() + index);
    }
    std::cout << "\n";
}