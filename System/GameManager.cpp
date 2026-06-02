#include <iostream>
#include <string>
#include "GameManager.h"
#include "ChosenHand.h"
#include "SmallBlindState.h" 
#include "BigBlindState.h"   
#include "BossBlindState.h"  
#include "RewardCommand.h"   
#include "TwinEchoJoker.h"
#include "BountyHunterJoker.h"

// ==========================================
// SETUP AWAL JOKER KELOMPOK 12
// ==========================================
GameManager::GameManager() {
    modifierManager.addModifier(std::make_unique<TwinEchoJoker>());
    modifierManager.addModifier(std::make_unique<BountyHunterJoker>());
}

void GameManager::runSession() {
    sessionState.currentBlind = std::make_unique<SmallBlindState>();
    sessionState.totalScore = 0;
    
    while (sessionState.remainingPlays > 0) {
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

        for (const auto& command : sessionState.pendingCommands) {
            command->execute(sessionState);
        }
        sessionState.pendingCommands.clear();

        std::cout << "\n[ MENU BLIND ] =========================\n";
        std::cout << " ANTE: " << sessionState.ante << "\n";
        std::cout << " STATE: " << sessionState.currentBlind->getName() << "\n";
        std::cout << " TARGET: " << sessionState.currentBlind->getTargetScore() << "\n";
        std::cout << "========================================\n";
        
        std::string blindInput;
        std::cout << "Aksi (1: LAWAN BLIND, 2: SKIP BLIND): ";
        std::getline(std::cin, blindInput);

        if (blindInput == "2") {
            sessionState.currentBlind->handleSkip(sessionState);
            sessionState.remainingPlays = 4;
            sessionState.remainingDiscards = 3;
            sessionState.totalScore = 0;
            continue; 

        } else if (blindInput == "1") {
            sessionState.currentBlind->handlePlay(sessionState);
            Hand currentHand = handGenerator.generateHand(); 
            bool blindDefeated = false;
            
            while (sessionState.remainingPlays > 0 && !blindDefeated) {
                std::cout << "\n[ MEJA PERMAINAN ] ---------------------\n";
                std::cout << " TARGET: " << sessionState.currentBlind->getTargetScore() << " | SKOR: " << sessionState.totalScore << "\n";
                std::cout << " Plays: " << sessionState.remainingPlays << " | Discards: " << sessionState.remainingDiscards << "\n";
                std::cout << "----------------------------------------\n";
                
                std::string tableInput;
                std::cout << "Aksi Meja (1: MAIN KARTU, 2: DISCARD KARTU): ";
                std::getline(std::cin, tableInput);

                if (tableInput == "1") {
                    ChosenHand chosenHand = handPlayer.playHand(currentHand); 
                    
                    // ==========================================
                    // INTEGRASI DINAMIS SISTEM JOKER & SCORING
                    // ==========================================
                    int skorMurni = scoringRule.scoreHand(chosenHand); 
                    std::string namaKombinasi = scoringRule.getRankName(chosenHand);
                    
                    ScorePayload payload;
                    payload.handRankName = namaKombinasi; 
                    payload.baseScore = skorMurni;
                    payload.multiplier = 1;
                    payload.playedCards = chosenHand.cards; 

                    // Panggil Joker Observer
                    modifierManager.applyAllModifiers(payload);

                    int finalScore = payload.baseScore * payload.multiplier;
                    
                    std::cout << "\n>>> [ " << payload.handRankName << " DIMAINKAN! ] <<<\n";
                    std::cout << "Base: " << payload.baseScore << " | Mult: " << payload.multiplier << "\n";
                    std::cout << "SKOR FINAL: " << finalScore << "\n";
                    
                    sessionState.totalScore += finalScore; 
                    sessionState.remainingPlays--; 
                    // ==========================================
                    
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

                    if (sessionState.totalScore >= sessionState.currentBlind->getTargetScore()) {
                        std::cout << "\n[!] TARGET SKOR TERCAPAI! Anda menang di Blind ini.\n";
                        blindDefeated = true; 
                    }
                    
                } else if (tableInput == "2") {
                    if (sessionState.remainingDiscards > 0) {
                        int sizeBefore = currentHand.cards.size();
                        handPlayer.discardCards(currentHand);
                        
                        if (currentHand.cards.size() < sizeBefore) {
                            sessionState.remainingDiscards--;
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
            } 

            if (blindDefeated) {
                std::string currentName = sessionState.currentBlind->getName();
                if (currentName == "Small Blind") {
                    sessionState.currentBlind = std::make_unique<BigBlindState>();
                } else if (currentName == "Big Blind") {
                    sessionState.currentBlind = std::make_unique<BossBlindState>();
                } else {
                    sessionState.currentBlind = nullptr; 
                }
                
                sessionState.remainingPlays = 4;
                sessionState.remainingDiscards = 3;
                sessionState.totalScore = 0;
            }

        } else {
            std::cout << "Input tidak valid!\n";
        }
    } 
    
    if (sessionState.remainingPlays <= 0) {
        std::cout << "\n[GAME OVER] Anda kehabisan kesempatan Play sebelum mencapai target skor.\n";
    }
    
    std::cout << "=== Run Ended ===\n";
}