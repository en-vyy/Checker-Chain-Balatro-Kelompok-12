#include <iostream>
#include <string>
#include "GameManager.h"
#include "ChosenHand.h"

// --- TAMBAHKAN 2 BARIS INI JIKA BELUM ADA ---
#include "SmallBlindState.h" 
#include "RewardCommand.h"

void GameManager::runSession() {
    std::cout << "=== Run Started ===\n";
    
    // 1. Inisialisasi awal: Mulai dari Small Blind
    sessionState.currentBlind = std::make_unique<SmallBlindState>();
    
    // 2. Game Loop: Berputar terus selama pemain masih punya kesempatan 'Play'
    while (sessionState.remainingPlays > 0) {
        
        // Cek apakah pemain sudah mengalahkan Boss Blind dan tidak ada state selanjutnya
        if (sessionState.currentBlind == nullptr) {
            std::cout << "\nSelamat! Anda telah menyelesaikan semua Blind!\n";
            break;
        }

        // 3. Eksekusi Hadiah yang Tertunda (Command Pattern)
        // Jika sebelumnya pemain menekan SKIP, hadiahnya ada di antrean ini
        for (const auto& command : sessionState.pendingCommands) {
            command->execute(sessionState);
        }
        sessionState.pendingCommands.clear(); // Bersihkan antrean setelah dieksekusi

        // 4. Tampilkan UI Status Saat Ini
        std::cout << "\n========================================\n";
        std::cout << " STATE: " << sessionState.currentBlind->getName() << "\n";
        std::cout << " TARGET SCORE: " << sessionState.currentBlind->getTargetScore() << "\n";
        std::cout << " Remaining Plays: " << sessionState.remainingPlays << "\n";
        std::cout << " Remaining Discards: " << sessionState.remainingDiscards << "\n";
        std::cout << "========================================\n";
        
        // 5. Minta Input Pemain
        std::string input;
        std::cout << "Pilih aksi (1: PLAY, 2: SKIP): ";
        std::getline(std::cin, input);

        if (input == "1") {
            // Pemain memilih PLAY
            sessionState.currentBlind->handlePlay(sessionState);
            
            // --- LOGIKA LAMA ANDA DIMASUKKAN KE SINI ---
            Hand hand = handGenerator.generateHand(); 
            ChosenHand chosenHand = handPlayer.playHand(hand); 
            int score = scoringRule.scoreHand(chosenHand); 
            
            std::cout << "Skor yang didapat dari kartu: " << score << "\n";
            
            // Kurangi nyawa play karena sudah bermain satu tangan
            sessionState.remainingPlays--; 
            
        } else if (input == "2") {
            // Pemain memilih SKIP (State Pattern akan mengatur perpindahan ke Blind berikutnya)
            sessionState.currentBlind->handleSkip(sessionState);
        } else {
            std::cout << "Input tidak valid!\n";
        }
    }
    
    if (sessionState.remainingPlays <= 0) {
        std::cout << "\n[GAME OVER] Anda kehabisan kesempatan Play.\n";
    }
    
    std::cout << "=== Run Ended ===\n";
}