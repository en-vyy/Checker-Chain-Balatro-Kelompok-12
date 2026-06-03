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

GameManager::GameManager() {}

void GameManager::runSession() {
    sessionState.currentBlind = std::make_unique<SmallBlindState>();
    sessionState.totalScore = 0;
    
    while (sessionState.remainingPlays > 0) {
        
        if (sessionState.currentBlind == nullptr) {
            sessionState.ante++;
            std::cout << "\n========================================\n";
            std::cout << " BOSS DIKALAHKAN! MAJU KE ANTE " << sessionState.ante << " \n";
            
            if (sessionState.hasInvestmentTag) {
                sessionState.money += 25;
                sessionState.hasInvestmentTag = false;
                std::cout << " INVESTMENT CAIR! Anda mendapat $25! (Total Uang: $" << sessionState.money << ")\n";
            }
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
        std::cout << " UANG  : $" << sessionState.money << "\n";
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
                    
                    HandRank evaluasiRank = scoringRule.evaluateHand(chosenHand);
                    
                    ScorePayload payload;
                    payload.handRankName = scoringRule.getRankNameStr(evaluasiRank); 
                    
                    int kombinasiChips = scoringRule.getBaseChips(evaluasiRank);
                    int kartuChips = 0;
                    for (const auto& card : chosenHand.cards) {
                        kartuChips += scoringRule.getCardChips(card.rank); 
                    }
                    payload.baseScore = kombinasiChips + kartuChips; 
                    payload.multiplier = scoringRule.getBaseMultiplier(evaluasiRank);
                    payload.playedCards = chosenHand.cards; 

                    modifierManager.applyAllModifiers(payload);

                    int finalScore = payload.baseScore * payload.multiplier;
                    
                    std::cout << "\n>>> [ " << payload.handRankName << " DIMAINKAN! ] <<<\n";
                    std::cout << "Kombinasi Chips: " << kombinasiChips << " | Kartu Chips: " << kartuChips << "\n";
                    std::cout << "Total Base: " << payload.baseScore << " Chips | Mult: " << payload.multiplier << "x\n";
                    std::cout << "SKOR FINAL: " << finalScore << "\n";
                    
                    sessionState.totalScore += finalScore; 
                    sessionState.remainingPlays--; 
                    sessionState.totalPlayedHands++; 
                    
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
                int baseReward = sessionState.currentBlind->getRewardMoney(); 
                int earnedMoney = baseReward + sessionState.remainingPlays;   
                
                sessionState.money += earnedMoney;
                std::cout << "\n MEMBAGIKAN HADIAH \n";
                std::cout << "Base Reward: $" << baseReward << " | Bonus Plays: $" << sessionState.remainingPlays << "\n";
                std::cout << "Anda mendapatkan $" << earnedMoney << " (Total Uang: $" << sessionState.money << ")\n";

                std::string currentName = sessionState.currentBlind->getName();
                if (currentName == "Small Blind") {
                    sessionState.currentBlind = std::make_unique<BigBlindState>();
                } else if (currentName == "Big Blind") {
                    sessionState.currentBlind = std::make_unique<BossBlindState>();
                } else {
                    sessionState.currentBlind = nullptr; 
                }

                bool inShop = true;
                while (inShop) {
                    std::cout << "\n[ T O K O ] ============================\n";
                    std::cout << " Uang Anda: $" << sessionState.money << "\n";
                    std::cout << "----------------------------------------\n";
                    std::cout << " 1. Beli Twin Echo Joker ($4)\n";
                    std::cout << " 2. Beli Bounty Hunter Joker ($5)\n";
                    std::cout << " 3. Lanjut ke Blind Berikutnya (Keluar)\n";
                    std::cout << "========================================\n";
                    
                    std::string shopInput;
                    std::cout << "Pilih barang: ";
                    std::getline(std::cin, shopInput);

                    if (shopInput == "1") {
                        if (sessionState.money >= 4) {
                            sessionState.money -= 4;
                            modifierManager.addModifier(std::make_unique<TwinEchoJoker>());
                            std::cout << "[+] Twin Echo Joker berhasil dibeli dan aktif!\n";
                            std::cout << "Toko ditutup. Melanjutkan perjalanan...\n";
                            inShop = false; // Toko langsung tertutup
                        } else {
                            std::cout << "[X] Uang Anda tidak cukup! Pilih opsi lain.\n";
                        }
                    } else if (shopInput == "2") {
                        if (sessionState.money >= 5) {
                            sessionState.money -= 5;
                            modifierManager.addModifier(std::make_unique<BountyHunterJoker>());
                            std::cout << "[+] Bounty Hunter Joker berhasil dibeli dan aktif!\n";
                            std::cout << "Toko ditutup. Melanjutkan perjalanan...\n";
                            inShop = false; // Toko langsung tertutup
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