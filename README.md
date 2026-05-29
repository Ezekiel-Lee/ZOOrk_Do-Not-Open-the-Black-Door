# ZOOrk — A Cthulhu Mythos Text Adventure

> *Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn.*

A C++ text adventure built on the ZOOrk framework, set in the cursed town of Innsmouth. Explore 10 rooms across a Lovecraftian world, manage your sanity, and uncover one of three possible endings.

---

## Build Instructions

### Requirements
- CMake 3.23 or later
- A C++20-compatible compiler (GCC 10+, Clang 12+, MSVC 2019+)

### Build & Run

```bash
cd ZOOrk_fixed
cmake -B build
cmake --build build
./build/ZOOrk
```

On Windows, the compiled binary `main.exe` is included for convenience and can be run directly.

---

## How to Play

| Command | Description |
|---|---|
| `go <direction>` | Move in a direction (`north`, `south`, `east`, `west`, `up`, `down`) |
| `look` | Describe the current room and list items |
| `look <item>` / `examine <item>` | Inspect a specific item |
| `take <item>` / `get <item>` | Pick up an item from the room |
| `drop <item>` | Drop an item into the current room |
| `inventory` / `inv` / `i` | List items you are carrying |
| `sanity` / `status` | Check your current sanity level |
| `read <item>` | Read a readable item (journal, necronomicon) |
| `use <item>` | Use an item from your inventory |
| `quit` / `exit` | Quit the game |

Directions can be abbreviated: `n`, `s`, `e`, `w`, `u`, `d`.

---

## World Map

```
[Miskatonic Station] --east--> [Innsmouth Square] --east--> [Marsh Refinery]
                                       |                           |
                                     south                       south
                                       |                           |
                              [Rotting Docks] <---west--- [Esoteric Order HQ]
                                       |
                                     down
                                       |
                              [Sea Cave Entrance]
                                       |
                              south (requires cultist-robe)
                                       |
                              [Deep One Grotto]
                                       |
                                     down
                                       |
                          [R'lyeh Antechamber] --east--> [Hall of Idols]
                                       |
                              down (requires phrase: ia-fhtagn)
                                       |
                            [Chamber of Cthulhu]  ← FINAL ROOM
```

---

## Sanity System

Your sanity starts at **100** and decreases as you explore deeper locations. If it reaches **0**, madness takes hold and the game ends.

| Sanity | Status |
|---|---|
| 80 – 100 | Stable |
| 60 – 79 | Unsettled |
| 40 – 59 | Disturbed |
| 20 – 39 | Unravelling |
| 1 – 19 | Critical |
| 0 | **Insanity — Bad Ending** |

### Sanity Recovery Items

| Item | Effect | Uses |
|---|---|---|
| `laudanum` | +25 sanity | 1 |
| `prayer-book` | +15 sanity | 3 |
| `flare` | +5 sanity | 1 |

---

## Endings

There are three possible endings:

- **Bad Ending** — Your sanity reaches 0. The void claims you.
- **Normal Ending** — You reach the Chamber of Cthulhu without the idol.
- **True Ending** — Reach the Chamber with the `deep-one-idol` and `use deep-one-idol`.

---

## Key Items & Puzzles

- **cultist-robe** — Found in Marsh Refinery. Required to pass the stone door into Deep One Grotto.
- **necronomicon** — Found in Esoteric Order HQ. Reading it costs 20 sanity but teaches the phrase `ia-fhtagn`, needed to open the final gate.
- **deep-one-idol** — Found in Hall of Idols. Use it in the Chamber of Cthulhu for the True Ending.
- **journal** — Found in Esoteric Order HQ. Contains a warning from a previous visitor.
- **ancient-key** — Found in Sea Cave Entrance. Corroded and barnacled, it opens nothing. 
  Human logic has no place in Cthulhu's domain.

---

## Project Structure

```
ZOOrk_fixed/
├── CMakeLists.txt
├── cpp/
│   ├── main.cpp               # World setup — rooms, items, passages
│   ├── ZOOrkEngine.cpp        # Game loop and command handling
│   ├── Room.cpp               # Room with item and passage management
│   ├── Passage.cpp            # Basic passageway
│   ├── Door.cpp               # Item-locked door (extends Passage)
│   ├── PhraseDoor.cpp         # Phrase-locked door (extends Passage)
│   ├── Player.cpp             # Singleton player with sanity system
│   ├── Character.cpp          # Base character with inventory
│   ├── Item.cpp               # Interactable item
│   └── ...
└── header/
    └── ...                    # Corresponding header files
```


