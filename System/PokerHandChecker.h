#pragma once
#include "Hand.h"

enum class HandRank {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE
};

class PokerHandChecker {
public:
    // Pure virtual function: Memaksa child class (programmer mekanik) untuk mengimplementasikan fungsi ini [cite: 564]
    virtual HandRank check(const Hand& hand) = 0;

    // Fungsi untuk menyambungkan rantai linked list
    void setNext(PokerHandChecker* next);

protected:
    // Pointer ke checker selanjutnya. Menggunakan protected agar bisa diakses oleh child class 
    PokerHandChecker* nextChecker = nullptr;
};