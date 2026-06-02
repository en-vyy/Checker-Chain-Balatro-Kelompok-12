#include <iostream>
#include <string>
#include "GameManager.h"
#include "ChosenHand.h"
#include "SmallBlindState.h" 
#include "BigBlindState.h"   // Wajib di-include untuk transisi level
#include "BossBlindState.h"  // Wajib di-include untuk transisi level
#include "RewardCommand.h"   

void GameManager::runSession() {
    sessionState.currentBlind = std::make_unique<SmallBlindState>();
    sessionState.totalScore = 0;
    
    // ==========================================
    // PHASE 1: OUTER LOOP (MENU PEMILIHAN BLIND)
    // ==========================================
    while (sessionState.remainingPlays > 0) {
        
        // --- NAIK ANTE ---
        if (sessionState.currentBlind == nullptr) {
            sessionState.ante++;
            std::cout << "\n========================================\n";
            std::cout << "🎉 BOSS DIKALAHKAN! MAJU KE ANTE " << sessionState.ante << " 🎉\n";
            std::cout << "========================================\n";
            
            sessionState.currentBlind = std::make_unique<SmallBlindState>();
            sessionState.remainingPlays = 4;
            sessionState.remainingDiscards = 3;
            sessionState.totalScore = 0; 
        }

        // Eksekusi hadiah dari SKIP sebelumnya
        for (const auto& command : sessionState.pendingCommands) {
            command->execute(sessionState);
        }
        sessionState.pendingCommands.clear();

        // Tampilan Layar Menu Blind
        std::cout << "\n[ MENU BLIND ] =========================\n";
        std::cout << " ANTE: " << sessionState.ante << "\n";
        std::cout << " STATE: " << sessionState.currentBlind->getName() << "\n";
        std::cout << " TARGET: " << sessionState.currentBlind->getTargetScore() << "\n";
        std::cout << "========================================\n";
        
        std::string blindInput;
        std::cout << "Aksi (1: LAWAN BLIND, 2: SKIP BLIND): ";
        std::getline(std::cin, blindInput);

        if (blindInput == "2") {
            // [SKIP BLIND]
            sessionState.currentBlind->handleSkip(sessionState);
            sessionState.remainingPlays = 4;
            sessionState.remainingDiscards = 3;
            sessionState.totalScore = 0;
            continue; // Kembali ke awal loop untuk memuat Blind baru

        } else if (blindInput == "1") {
            // [LAWAN BLIND]
            sessionState.currentBlind->handlePlay(sessionState);
            
            // Dealer membagikan 8 kartu BARU setiap kali pemain duduk di meja
            Hand currentHand = handGenerator.generateHand(); 
            bool blindDefeated = false;
            
            // ==========================================
            // PHASE 2: INNER LOOP (MEJA PERMAINAN)
            // ==========================================
            while (sessionState.remainingPlays > 0 && !blindDefeated) {
                std::cout << "\n[ MEJA PERMAINAN ] ---------------------\n";
                std::cout << " TARGET: " << sessionState.currentBlind->getTargetScore() << " | SKOR: " << sessionState.totalScore << "\n";
                std::cout << " Plays: " << sessionState.remainingPlays << " | Discards: " << sessionState.remainingDiscards << "\n";
                std::cout << "----------------------------------------\n";
                
                std::string tableInput;
                std::cout << "Aksi Meja (1: MAIN KARTU, 2: DISCARD KARTU): ";
                std::getline(std::cin, tableInput);

                if (tableInput == "1") {
                    // --- PLAY CARDS ---
                    ChosenHand chosenHand = handPlayer.playHand(currentHand); 
                    int score = scoringRule.scoreHand(chosenHand); 
                    
                    std::cout << "Skor yang didapat: " << score << "\n";
                    sessionState.totalScore += score; 
                    sessionState.remainingPlays--; 
                    
                    // Tarik kartu baru dari dek
                    if (currentHand.cards.size() < 8) {
                        Hand refillCards = handGenerator.generateHand();
                        int drawn = 0;
                        while (currentHand.cards.size() < 8 && !refillCards.cards.empty()) {
                            currentHand.cards.push_back(refillCards.cards.back());
                            refillCards.cards.pop_back();
                            drawn++;
                        }
                        std::cout << "[+] " << drawn << " kartu ditarik dari dek.\n";
                    }

                    // Cek Kemenangan
                    if (sessionState.totalScore >= sessionState.currentBlind->getTargetScore()) {
                        std::cout << "\n[!] TARGET SKOR TERCAPAI! Anda menang di Blind ini.\n";
                        blindDefeated = true; // Ini akan memutus inner loop meja permainan
                    }
                    
                } else if (tableInput == "2") {
                    // --- DISCARD CARDS ---
                    if (sessionState.remainingDiscards > 0) {
                        int sizeBefore = currentHand.cards.size();
                        handPlayer.discardCards(currentHand);
                        
                        // Jika pemain benar-benar membuang kartu (tidak membatalkan)
                        if (currentHand.cards.size() < sizeBefore) {
                            sessionState.remainingDiscards--;
                            
                            // Tarik kartu pengganti
                            Hand refillCards = handGenerator.generateHand();
                            int drawn = 0;
                            while (currentHand.cards.size() < 8 && !refillCards.cards.empty()) {
                                currentHand.cards.push_back(refillCards.cards.back());
                                refillCards.cards.pop_back();
                                drawn++;
                            }
                            std::cout << "[+] " << drawn << " kartu pengganti telah ditarik!\n";
                        }
                    } else {
                        std::cout << "\n[X] GAGAL: Anda tidak memiliki sisa Discard!\n";
                    }
                } else {
                    std::cout << "Input tidak valid!\n";
                }
            } // --- END OF PHASE 2 ---

            // Transisi Level setelah keluar dari Meja Permainan karena Menang
            if (blindDefeated) {
                std::string currentName = sessionState.currentBlind->getName();
                if (currentName == "Small Blind") {
                    sessionState.currentBlind = std::make_unique<BigBlindState>();
                } else if (currentName == "Big Blind") {
                    sessionState.currentBlind = std::make_unique<BossBlindState>();
                } else {
                    sessionState.currentBlind = nullptr; // Boss kalah, memicu Next Ante
                }
                
                sessionState.remainingPlays = 4;
                sessionState.remainingDiscards = 3;
                sessionState.totalScore = 0;
            }

        } else {
            std::cout << "Input tidak valid!\n";
        }
    } // --- END OF PHASE 1 ---
    
    if (sessionState.remainingPlays <= 0) {
        std::cout << "\n[GAME OVER] Anda kehabisan kesempatan Play sebelum mencapai target skor.\n";
    }
    
    std::cout << "=== Run Ended ===\n";
}