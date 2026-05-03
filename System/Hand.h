#pragma once
#include <vector>
#include <iostream>
#include "Card.h"

// Struktur bawaan dari PDF dosen
struct Hand {
    std::vector<Card> cards;
};

// Jawaban Tugas No 1: Membuat class ChosenHand
class ChosenHand : public Hand {
public:
    // Fungsi untuk memasukkan kartu pilihan
    void addChosenCard(Card card) {
        cards.push_back(card);
    }

    // Fungsi tambahan untuk menampilkan kartu di terminal
    void showChosenCards() const {
        std::cout << "Player plays selected cards: \n";
        for (const auto& c : cards) {
            std::cout << "[" << c.rank << c.suit << "] ";
        }
        std::cout << "\n";
    }
};