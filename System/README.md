TTD Balatro Project-Group 12


# 🃏 Technical Design Document — Balatro
### Checker-Chain Balatro · Kelompok 12
> **Bahasa:** C++17 &nbsp;|&nbsp; **Pattern:** Chain of Responsibility, State, Command, Strategy &nbsp;|&nbsp; **Versi:** 1.0

---

## 📋 Daftar Isi

1. [Gambaran Umum](#1-gambaran-umum)
2. [Struktur Direktori](#2-struktur-direktori)
3. [Arsitektur Sistem](#3-arsitektur-sistem)
4. [Sistem Kartu dan Tangan](#4-sistem-kartu-dan-tangan-card--hand-system)
5. [Sistem Evaluasi Kombinasi Poker](#5-sistem-evaluasi-kombinasi-poker)
6. [Sistem Scoring](#6-sistem-scoring)
7. [Sistem Modifier (Joker)](#7-sistem-modifier-joker)
8. [Sistem Blind (State Pattern)](#8-sistem-blind-state-pattern)
9. [Sistem Reward Command](#9-sistem-reward-command-command-pattern)
10. [GameManager — Orkestrator Utama](#10-gamemanager--orkestrator-utama)
11. [Panduan Ekstensi](#11-panduan-ekstensi)
12. [Ringkasan Komponen](#12-ringkasan-komponen)

---

## 1. Gambaran Umum

Balatro adalah sistem evaluasi dan penilaian hand poker berbasis **C++** yang terinspirasi dari permainan roguelike berbasis poker. Program berjalan sebagai aplikasi konsol interaktif di mana pemain dapat memainkan kartu, men-discard kartu, dan mengalahkan tiga jenis Blind untuk maju ke Ante berikutnya.

### Tujuan Sistem
- Mengevaluasi kombinasi kartu poker secara otomatis
- Menghitung skor berbasis **Chips × Multiplier**
- Menerapkan efek Modifier (Joker) secara dinamis
- Mengelola alur permainan melalui sistem Blind bertahap
- Mendukung reward deferred berbasis Command Pattern

### Stack Teknologi

| Komponen | Teknologi / Standar |
|---|---|
| Bahasa Pemrograman | C++17 |
| Manajemen Memori | `std::unique_ptr` (RAII) |
| Randomisasi Deck | `std::shuffle` + `std::mt19937` |
| Pattern Arsitektur | Chain of Responsibility, State, Command, Strategy |
| Build Tool | Kompilasi langsung (`main.exe` disertakan) |

---

## 2. Struktur Direktori

```
Checker-Chain-Balatro-Kelompok-12-main/
│
├── System/                         # Komponen inti & kontrak sistem
│   ├── main.cpp                    # Entry point
│   ├── GameManager.cpp/.h          # Orkestrator utama
│   ├── RunSessionState.h           # Status sesi (ante, score, uang, blind)
│   ├── Card.h                      # Struct data kartu
│   ├── Hand.h                      # Struct kumpulan kartu
│   ├── ChosenHand.h                # Kartu yang dipilih untuk scoring
│   ├── HandGenerator.cpp/.h        # Generator kartu acak
│   ├── HandPlayer.cpp/.h           # Input pemain: play / discard
│   ├── PokerHandChecker.h          # Abstract base checker (Chain of Resp.)
│   ├── ScoringRule.cpp/.h          # Engine evaluasi + kalkulasi skor
│   ├── ScorePayload.h              # Kontainer skor mutable
│   ├── Modifier.h                  # Abstract interface Joker
│   ├── ModifierManager.cpp/.h      # Kelola & terapkan semua Joker aktif
│   ├── BlindState.h                # Abstract interface Blind
│   ├── SmallBlindState.cpp/.h      # Blind pertama setiap ante
│   ├── BigBlindState.cpp/.h        # Blind kedua setiap ante
│   ├── BossBlindState.cpp/.h       # Blind ketiga, tidak bisa di-skip
│   ├── RewardCommand.h             # Interface + implementasi reward Command
│   ├── BlindRule.h/.cpp            # Utilitas cek target skor
│   └── RewardRule.h/.cpp           # Kalkulasi uang reward
│
└── Mechanics/                      # Implementasi konkret mekanik permainan
    ├── FlushFiveChecker.cpp/.h      # Checker: Flush Five
    ├── FlushHouseChecker.cpp/.h     # Checker: Flush House
    ├── FiveOfAKindChecker.cpp/.h    # Checker: Five of a Kind
    ├── RoyalFlushChecker.cpp/.h     # Checker: Royal Flush
    ├── StraightFlushChecker.cpp/.h  # Checker: Straight Flush
    ├── FourOfAKindChecker.cpp/.h    # Checker: Four of a Kind
    ├── FullHouseChecker.cpp/.h      # Checker: Full House
    ├── FlushChecker.cpp/.h          # Checker: Flush
    ├── StraightChecker.cpp/.h       # Checker: Straight
    ├── ThreeOfAKindChecker.cpp/.h   # Checker: Three of a Kind
    ├── TwoPairChecker.cpp/.h        # Checker: Two Pair
    ├── PairChecker.cpp/.h           # Checker: Pair
    ├── HighCardChecker.cpp/.h       # Checker: High Card (fallback)
    ├── TwinEchoJoker.cpp/.h         # Joker: +10 Mult saat Two Pair
    └── BountyHunterJoker.cpp/.h     # Joker: +150 Base Score saat Two Pair
```

> **Prinsip Pemisahan:** `System/` mendefinisikan **kontrak** (interface/abstract class) — tidak boleh diubah sembarangan. `Mechanics/` mendefinisikan **implementasi konkret** — dapat ditambah bebas tanpa menyentuh `System/`.

---

## 3. Arsitektur Sistem

### Runtime Flow

```
main()
  └── GameManager::runSession()
        ├── Setup: SmallBlindState + ModifierManager
        └── Loop Utama:
              ├── Eksekusi PendingCommands
              ├── Tampilkan menu Blind (LAWAN / SKIP)
              │     ├── SKIP ──► BlindState::handleSkip()
              │     │              └── buat RewardCommand → pindah state
              │     └── LAWAN ──► BlindState::handlePlay()
              │                    └── Gameplay Loop
              │                          ├── MAIN KARTU: playHand() → evaluasi
              │                          │     └── ScorePayload → applyAllModifiers()
              │                          └── DISCARD: discardCards() → refill
              └── Blind dikalahkan → Toko → pindah BlindState berikutnya
```

### Design Patterns

| Pattern | Diterapkan Pada | Tujuan |
|---|---|---|
| **Chain of Responsibility** | `PokerHandChecker` → `ScoringRule` | Evaluasi kombinasi dari terkuat ke terlemah tanpa branching `if-else` |
| **State Pattern** | `BlindState` (Small/Big/Boss) | Setiap blind punya perilaku sendiri; transisi tanpa kondisional besar |
| **Command Pattern** | `RewardCommand` + `pendingCommands` | Reward skip blind dapat dieksekusi tertunda (*deferred execution*) |
| **Strategy Pattern** | `Modifier` (TwinEchoJoker, BountyHunterJoker) | Setiap joker punya logika sendiri, dapat diganti/ditambah bebas |

---

## 4. Sistem Kartu dan Tangan (Card & Hand System)

### `Card` — Struct Data Kartu

```cpp
struct Card {
    int  rank;  // 2–14 (14 = As)
    char suit;  // 'H'=Hearts, 'D'=Diamonds, 'C'=Clubs, 'S'=Spades
};
```

| Field | Tipe | Nilai Valid | Keterangan |
|---|---|---|---|
| `rank` | `int` | 2 – 14 | 2–10 = angka; 11=J, 12=Q, 13=K, 14=As |
| `suit` | `char` | `'H','D','C','S'` | Hearts, Diamonds, Clubs, Spades |

---

### `Hand` — Kumpulan Kartu

```cpp
struct Hand {
    std::vector<Card> cards;
};
```

Merupakan struktur dasar yang dipakai oleh `ChosenHand`.

---

### `ChosenHand` — Kartu Terpilih

```cpp
class ChosenHand : public Hand {
public:
    void addChosenCard(Card card);   // Tambah kartu ke pilihan
    void showChosenCards() const;    // Tampilkan kartu ke konsol
};
```

Pemisahan `Hand` dan `ChosenHand` penting karena:
- Pemain bisa memegang banyak kartu (`Hand`) tetapi hanya beberapa yang di-scoring (`ChosenHand`)
- Sisa kartu di `Hand` tetap ada dan dapat diisi ulang setelah PLAY atau DISCARD

---

### `HandGenerator` & `HandPlayer`

```cpp
class HandGenerator {
public:
    Hand generateHand();   // Hasilkan sekumpulan kartu acak
};

class HandPlayer {
public:
    ChosenHand playHand(Hand& currentHand);   // Pilih & mainkan kartu
    void discardCards(Hand& currentHand);     // Buang kartu yang dipilih
};
```

---

## 5. Sistem Evaluasi Kombinasi Poker

### Abstract Class `PokerHandChecker`

Basis dari semua checker. Menggunakan **Chain of Responsibility**: setiap checker memeriksa satu kombinasi, dan jika tidak cocok meneruskan ke checker berikutnya lewat `nextChecker`.

```cpp
class PokerHandChecker {
public:
    virtual HandRank check(const Hand& hand) = 0;   // Pure virtual — wajib diimplementasikan
    void setNext(PokerHandChecker* next);             // Sambung rantai
protected:
    PokerHandChecker* nextChecker = nullptr;
};
```

> **Cara Kerja:** `flushFiveChecker.check(hand)` dipanggil pertama. Jika cocok → kembalikan `HandRank::FLUSH_FIVE`. Jika tidak → teruskan ke `nextChecker`. `HighCardChecker` selalu mengembalikan `HIGH_CARD` sebagai **fallback**, menjamin setiap tangan selalu punya hasil.

---

### Enum `HandRank` & Nilai Skor

| Kombinasi | Enum | Base Chips | Base Mult |
|---|---|:---:|:---:|
| High Card | `HIGH_CARD` | 5 | 1× |
| Pair | `PAIR` | 10 | 2× |
| Two Pair | `TWO_PAIR` | 20 | 2× |
| Three of a Kind | `THREE_OF_A_KIND` | 30 | 3× |
| Straight | `STRAIGHT` | 30 | 3× |
| Flush | `FLUSH` | 35 | 4× |
| Full House | `FULL_HOUSE` | 40 | 4× |
| Four of a Kind | `FOUR_OF_A_KIND` | 60 | 7× |
| Straight Flush | `STRAIGHT_FLUSH` | 100 | 8× |
| Royal Flush | `ROYAL_FLUSH` | 80 | 8× |
| Five of a Kind | `FIVE_OF_A_KIND` | 120 | 12× |
| Flush House | `FLUSH_HOUSE` | 140 | 14× |
| Flush Five | `FLUSH_FIVE` | 150 | 14× |

---

### Urutan Rantai Checker di `ScoringRule`

```cpp
// ScoringRule.cpp — konstruktor (urutan kuat → lemah, JANGAN diubah sembarangan)
flushFiveChecker.setNext(&flushHouseChecker);
flushHouseChecker.setNext(&fiveOfAKindChecker);
fiveOfAKindChecker.setNext(&royalFlushChecker);
royalFlushChecker.setNext(&straightFlushChecker);
straightFlushChecker.setNext(&fourofakindChecker);
fourofakindChecker.setNext(&fullhouseChecker);
fullhouseChecker.setNext(&flushchecker);
flushchecker.setNext(&straightChecker);
straightChecker.setNext(&threeOfAKindChecker);
threeOfAKindChecker.setNext(&twoPairChecker);
twoPairChecker.setNext(&pairChecker);
pairChecker.setNext(&highCardChecker);   // ← fallback
```

---

## 6. Sistem Scoring

### `ScoringRule` — Fungsi-Fungsi Utama

| Fungsi | Return | Deskripsi |
|---|---|---|
| `evaluateHand(hand)` | `HandRank` | Jalankan rantai checker, kembalikan kombinasi terbaik |
| `getBaseChips(rank)` | `int` | Base chip sesuai kombinasi |
| `getBaseMultiplier(rank)` | `int` | Multiplier sesuai kombinasi |
| `getCardChips(rank)` | `int` | Nilai chip per kartu: 2–10 sesuai nilai; J/Q/K = 10; As = 11 |
| `getRankNameStr(rank)` | `string` | Nama kombinasi dalam teks |
| `scoreHand(hand)` | `int` | Shortcut: chips × mult tanpa Joker |

### Formula Skor

```
Base Score  =  Kombinasi Base Chips + Σ(chip tiap kartu yang dimainkan)
               contoh: FLUSH (35) + [7+8+9+10+11] = 35 + 45 = 80

Final Score =  ScorePayload.baseScore × ScorePayload.multiplier
               contoh: 80 chips × 4 mult = 320 skor
```

> Setelah `applyAllModifiers()` dijalankan, `baseScore` dan `multiplier` mungkin sudah dimodifikasi oleh Joker aktif.

### `ScorePayload` — Kontainer Skor Mutable

```cpp
struct ScorePayload {
    std::string       handRankName;   // Nama kombinasi teks
    int               baseScore;      // Total chip (sebelum/sesudah modifier)
    int               multiplier;     // Multiplier (sebelum/sesudah modifier)
    std::vector<Card> playedCards;    // Kartu yang dimainkan (untuk efek Joker tertentu)
};
```

---

## 7. Sistem Modifier (Joker)

### Abstract Class `Modifier`

```cpp
class Modifier {
public:
    virtual std::string getModifierName() const = 0;
    virtual bool canActivate(const ScorePayload& payload) const = 0;
    virtual void applyEffect(ScorePayload& payload) = 0;
};
```

| Fungsi | Deskripsi |
|---|---|
| `getModifierName()` | Nama joker untuk ditampilkan / debug |
| `canActivate(payload)` | Cek kondisi aktivasi — hanya **membaca** payload |
| `applyEffect(payload)` | Modifikasi `baseScore` atau `multiplier` — satu-satunya yang boleh **menulis** |

---

### `ModifierManager`

```cpp
class ModifierManager {
    std::vector<std::unique_ptr<Modifier>> activeModifiers;
public:
    void addModifier(std::unique_ptr<Modifier> modifier);
    void applyAllModifiers(ScorePayload& payload);
};
```

`applyAllModifiers()` mengiterasi semua Modifier → panggil `canActivate()` → jika `true`, panggil `applyEffect()`. Efek diterapkan berurutan sesuai urutan registrasi.

---

### Joker yang Tersedia

| Kelas | File | Kondisi Aktivasi | Efek | Harga |
|---|---|---|---|:---:|
| `TwinEchoJoker` | `TwinEchoJoker.cpp/.h` | `handRankName == "Two Pair"` | +10 Multiplier | $4 |
| `BountyHunterJoker` | `BountyHunterJoker.cpp/.h` | `handRankName == "Two Pair"` | +150 Base Score | $5 |

---

### Cara Menambah Joker Baru

```cpp
// Langkah 1 — Buat file di Mechanics/MyNewJoker.h
class MyNewJoker : public Modifier {
public:
    std::string getModifierName() const override { return "My New Joker"; }

    bool canActivate(const ScorePayload& p) const override {
        return p.handRankName == "Flush";   // kondisi aktivasi
    }

    void applyEffect(ScorePayload& p) override {
        p.multiplier += 5;   // efek yang diterapkan
    }
};
```

```cpp
// Langkah 2 — Daftarkan di GameManager.cpp (menu toko)
modifierManager.addModifier(std::make_unique<MyNewJoker>());
```

---

## 8. Sistem Blind (State Pattern)

### Abstract Class `BlindState`

```cpp
class BlindState {
public:
    virtual std::string getName() = 0;
    virtual int getTargetScore() = 0;
    virtual int getRewardMoney() = 0;
    virtual void handlePlay(RunSessionState& state) = 0;
    virtual void handleSkip(RunSessionState& state) = 0;
};
```

### Ketiga Implementasi Blind

| Kelas | Target Skor | Reward | Efek Skip | Next State |
|---|:---:|:---:|---|---|
| `SmallBlindState` | 300 | $3 | Tambah `InvestmentTagCommand` ke pending | `BigBlindState` |
| `BigBlindState` | 450 | $4 | Tambah `HandyTagCommand` ke pending | `BossBlindState` |
| `BossBlindState` | 600 | $5 | **GAGAL** — Boss tidak bisa di-skip | `nullptr` |

> **Reward uang akhir** = `getRewardMoney()` + sisa `remainingPlays` saat blind dikalahkan.  
> Contoh: kalahkan Big Blind dengan sisa 2 plays → $4 + $2 = **$6**

### Alur Transisi Blind per Ante

```
Ante N:
  SmallBlindState → BigBlindState → BossBlindState → nullptr (Ante Selesai)
                                                          │
                                                          ▼
                                                     ante++
                                                     SmallBlindState (Ante N+1)
                                                     reset: plays=4, discards=3, score=0
```

---

## 9. Sistem Reward Command (Command Pattern)

### Latar Belakang

Ketika pemain meng-skip sebuah Blind, reward tidak selalu langsung aktif. Reward dibungkus sebagai **Command object**, disimpan di `pendingCommands`, dan dieksekusi di awal loop berikutnya.

### Abstract Class `RewardCommand`

```cpp
class RewardCommand {
public:
    virtual void execute(RunSessionState& state) = 0;
};
```

### Command yang Tersedia

| Kelas | Sumber (dari Skip) | Efek saat `execute()` |
|---|---|---|
| `HandyTagCommand` | Big Blind di-skip | `state.money += state.totalPlayedHands × $1` |
| `InvestmentTagCommand` | Small Blind di-skip | `state.hasInvestmentTag = true` → cair $25 saat Boss dikalahkan |

### Siklus Eksekusi

```
1. Player skip Small Blind
   └── SmallBlindState::handleSkip() membuat InvestmentTagCommand
         └── di-push ke state.pendingCommands

2. Di awal loop berikutnya:
   for (auto& cmd : pendingCommands) { cmd->execute(state); }
   pendingCommands.clear();

3. InvestmentTagCommand::execute() → hasInvestmentTag = true
   └── Saat Boss Blind dikalahkan → GameManager membagikan $25
```

### `RunSessionState` — Status Sesi Lengkap

```cpp
struct RunSessionState {
    int  ante              = 1;
    int  totalScore        = 0;
    int  remainingPlays    = 4;
    int  remainingDiscards = 3;
    int  money             = 4;
    int  totalPlayedHands  = 0;    // tracker untuk HandyTag
    bool hasInvestmentTag  = false;

    std::unique_ptr<BlindState>                currentBlind;
    std::vector<std::unique_ptr<RewardCommand>> pendingCommands;
};
```

---

## 10. GameManager — Orkestrator Utama

`GameManager` adalah satu-satunya titik masuk dari `main()`. Ia mengorkestrasi semua sistem tanpa menyentuh detail implementasi masing-masing.

### Atribut

| Atribut | Tipe | Peran |
|---|---|---|
| `handGenerator` | `HandGenerator` | Membuat kartu acak untuk tangan pemain |
| `handPlayer` | `HandPlayer` | Menerima input pemain: PLAY / DISCARD |
| `scoringRule` | `ScoringRule` | Evaluasi kombinasi dan hitung skor |
| `blindRule` | `BlindRule` | Cek apakah target skor tercapai |
| `rewardRule` | `RewardRule` | Kalkulasi uang reward kemenangan blind |
| `sessionState` | `RunSessionState` | Status sesi: ante, score, uang, blind aktif |
| `modifierManager` | `ModifierManager` | Simpan dan aplikasikan semua Joker aktif |

### Pseudocode `runSession()`

```
runSession():
  currentBlind = SmallBlindState

  Loop (remainingPlays > 0):
    Jika currentBlind == nullptr:
      ante++, reset state, buat SmallBlindState baru

    Eksekusi semua pendingCommands → clear

    Tampilkan menu Blind (ante, nama, target, uang)
    Input: 1=LAWAN, 2=SKIP

    Jika SKIP:
      handleSkip() → transisi blind → reset resources

    Jika LAWAN:
      generateHand() → currentHand
      Inner Loop (remainingPlays > 0 AND !blindDefeated):
        Input: 1=MAIN KARTU, 2=DISCARD
        Jika MAIN:
          evaluateHand() → ScorePayload → applyAllModifiers()
          finalScore = baseScore × multiplier
          totalScore += finalScore
          remainingPlays--
        Jika DISCARD:
          discardCards() → refill → remainingDiscards--
        Jika totalScore >= targetScore:
          blindDefeated = true

      Jika blindDefeated:
        Beri reward uang → buka Toko → pindah BlindState berikutnya
```

---

## 11. Ringkasan Komponen

| Komponen | File Utama | Pattern | Tanggung Jawab |
|---|---|---|---|
| `GameManager` | `GameManager.cpp/.h` | Facade | Orkestrasi seluruh alur permainan |
| `Card` / `Hand` | `Card.h` / `Hand.h` | Data Struct | Representasi entitas kartu |
| `ChosenHand` | `ChosenHand.h` | Inheritance | Kartu yang dipilih untuk scoring |
| `HandGenerator` | `HandGenerator.cpp/.h` | Factory | Menghasilkan kartu acak |
| `HandPlayer` | `HandPlayer.cpp/.h` | — | Input pemain: play / discard |
| `PokerHandChecker` | `PokerHandChecker.h` | Chain of Resp. | Base checker — rantai evaluasi |
| `ScoringRule` | `ScoringRule.cpp/.h` | Chain of Resp. | Engine evaluasi + kalkulasi skor |
| `ScorePayload` | `ScorePayload.h` | Data Struct | Kontainer skor mutable |
| `Modifier` | `Modifier.h` | Strategy | Interface semua Joker |
| `ModifierManager` | `ModifierManager.cpp/.h` | Strategy | Kelola dan terapkan semua Joker |
| `BlindState` | `BlindState.h` | State | Interface status Blind |
| `SmallBlindState` | `SmallBlindState.cpp/.h` | State | Blind pertama setiap ante |
| `BigBlindState` | `BigBlindState.cpp/.h` | State | Blind kedua setiap ante |
| `BossBlindState` | `BossBlindState.cpp/.h` | State | Blind ketiga, tidak bisa di-skip |
| `RewardCommand` | `RewardCommand.h` | Command | Interface + impl reward skip |
| `RunSessionState` | `RunSessionState.h` | Data Struct | Status sesi keseluruhan |

---

<div align="center">

**Checker-Chain Balatro · Kelompok 12**  


</div>