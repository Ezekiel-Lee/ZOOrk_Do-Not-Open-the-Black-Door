//
// Cthulhu ZOOrk — Main world setup
// 10 rooms across the cursed town of Innsmouth and beyond.
//
// Map:
//
//  [Miskatonic Station] --east--> [Innsmouth Square] --east--> [Marsh Refinery]
//                                        |                           |
//                                      south                       south
//                                        |                           |
//                               [Rotting Docks] <---west--- [Esoteric Order HQ]
//                                        |
//                                      down
//                                        |
//                               [Sea Cave Entrance]
//                                        |
//                                      south
//                                        |
//                              [Deep One Grotto] <--[SanityDoor]--+
//                                        |
//                                      down
//                                        |
//                          [R'lyeh Antechamber] --east--> [Hall of Idols]
//                                        |
//                                      down (DoorItem: "deep-one-idol")
//                                        |
//                              [Chamber of Cthulhu]   <-- FINAL ROOM
//

#include "../header/RoomDefaultEnterCommand.h"
#include "../header/Passage.h"
#include "../header/Door.h"
#include "../header/PhraseDoor.h"
#include "../header/Player.h"
#include "../header/Room.h"
#include "../header/Item.h"
#include "../header/ZOOrkEngine.h"
#include <memory>
#include <iostream>

int main() {

    // ── ROOMS ────────────────────────────────────────────────────────────────

    auto miskatonicStation = std::make_shared<Room>(
        "Miskatonic Station",
        "A crumbling railway terminus smelling of brine and rot. Peeling posters\n"
        "advertise seaside holidays in Innsmouth — a town no sane person visits.\n"
        "Mist curls under the platform lamps. The train that brought you here\n"
        "has already departed."
    );

    auto innsmouthSquare = std::make_shared<Room>(
        "Innsmouth Square",
        "The town square is deserted despite the early hour. Shuttered buildings\n"
        "lean inward as though whispering secrets to one another. A faint,\n"
        "rhythmic chanting drifts from somewhere to the south. A tarnished\n"
        "fountain depicts something fishlike rising from the waves."
    );

    auto marshRefinery = std::make_shared<Room>(
        "Marsh Gold Refinery",
        "The old Marsh family refinery looms over the waterfront. Inside, strange\n"
        "machinery sits idle, its purpose unclear — the moulds are shaped for no\n"
        "human hand. A cultist-robe hangs on a hook by the door."
    );
    marshRefinery->setSanityDrain(5);

    auto rottingDocks = std::make_shared<Room>(
        "The Rotting Docks",
        "Slick black timber and the stench of low tide. The sea here is\n"
        "unnaturally still, and the water is dark beyond any natural explanation.\n"
        "Shapes move far below the surface. A rusted iron ladder descends into a\n"
        "sea cave below. To the east lies the Esoteric Order of Dagon."
    );
    rottingDocks->setSanityDrain(10);

    auto esotericOrder = std::make_shared<Room>(
        "Esoteric Order of Dagon",
        "A meeting hall decorated with blasphemous bas-reliefs of men transforming\n"
        "into something else — something with gills and wide, staring eyes.\n"
        "Candles gutter in a draught from nowhere. A leather-bound journal lies\n"
        "open on the lectern."
    );
    esotericOrder->setSanityDrain(10);

    auto seaCaveEntrance = std::make_shared<Room>(
        "Sea Cave Entrance",
        "Cold salt water drips from stalactites overhead. The cave mouth frames\n"
        "a view of the inky ocean. Bioluminescent fungi cast a sickly green glow.\n"
        "Deeper passages lead south into the earth — or below it."
    );
    seaCaveEntrance->setSanityDrain(5);

    auto deepOneGrotto = std::make_shared<Room>(
        "Deep One Grotto",
        "You have descended into a vast underwater grotto. Carved into every\n"
        "surface are the same repeating glyphs: Ph'nglui mglw'nafh Cthulhu.\n"
        "The air is somehow breathable, though ice-cold. Something huge shifted\n"
        "in the water nearby just a moment ago."
    );
    deepOneGrotto->setSanityDrain(15);

    auto rlyehAntechamber = std::make_shared<Room>(
        "R'lyeh Antechamber",
        "Geometry fails here. Walls meet at impossible angles. The stone is\n"
        "not quarried but grown — or perhaps dreamed. Eldritch carvings writhe\n"
        "if you look away and then back. A corridor leads east to a hall of idols,\n"
        "and a great staircase plunges downward."
    );
    rlyehAntechamber->setSanityDrain(15);

    auto hallOfIdols = std::make_shared<Room>(
        "Hall of Idols",
        "Dozens of statues line the hall — all depicting the same figure:\n"
        "tentacled, vast, and terrible. One idol is smaller than the rest,\n"
        "carved from midnight-black stone, and sits on a plinth you could\n"
        "reach. The air hums with ancient power."
    );
    hallOfIdols->setSanityDrain(10);

    auto chamberOfCthulhu = std::make_shared<Room>(
        "The Chamber of Cthulhu",
        "The ceiling is lost in darkness. At the centre of the room, a cyclopean\n"
        "altar pulses with a faint, rhythmic light — like a heartbeat.\n\n"
        "And then you see it. HIM. Cthulhu stirs in his aeon-long sleep.\n"
        "One vast eye opens slowly. It fixes upon you.\n\n"
        "The weight of eternity presses down. Every truth you have ever known\n"
        "dissolves. The universe is indifferent. And yet — you are still here.\n\n"
        "A hollow in the altar is shaped like a small idol.\n"
        "Use 'use deep-one-idol' to place it — if you carry one."
    );
    chamberOfCthulhu->setSanityDrain(20);

    // ── ITEMS ────────────────────────────────────────────────────────────────

    auto journal = std::make_shared<Item>(
        "journal",
        "A leather journal filled with a frantic hand. The author's name\n"
        "has been scratched out. Use 'read journal' to read it."
    );

    auto necronomicon = std::make_shared<Item>(
        "necronomicon",
        "The dreaded Necronomicon. Its cover is warm to the touch.\n"
        "Use 'read necronomicon' to read it — if you dare."
    );

    auto cultistRobe = std::make_shared<Item>(
        "cultist-robe",
        "A hooded robe bearing the sigil of Dagon. Wearing it might let\n"
        "you pass through certain doors unquestioned."
    );

    auto deepOneIdol = std::make_shared<Item>(
        "deep-one-idol",
        "A palm-sized idol of black stone, slick despite the dryness of the air.\n"
        "It depicts a humanoid figure mid-transformation. It feels important."
    );

    auto flare = std::make_shared<Item>(
        "flare",
        "A red emergency flare. Could be useful if you need light — or an exit signal."
    );

    auto ancientKey = std::make_shared<Item>(
        "ancient-key",
        "A corroded bronze key covered in barnacles. Something is engraved on it:\n"
        "a spiralling eye motif. It must open something nearby."
    );

    auto laudanum = std::make_shared<Item>(
        "laudanum",
        "A small brown bottle of laudanum — a Victorian tincture of opium.\n"
        "The label reads: 'For nervous complaints and sleeplessness.'\n"
        "Use 'use laudanum' to drink it and restore 25 sanity."
    );

    auto prayerBook = std::make_shared<Item>(
        "prayer-book",
        "A worn leather prayer book, its pages soft with use.\n"
        "Familiar words of scripture anchor the mind against the darkness.\n"
        "Use 'use prayer-book' to read aloud and restore 15 sanity."
    );

    // ── PLACE ITEMS IN ROOMS ──────────────────────────────────────────────────

    innsmouthSquare->addItem(flare);
    esotericOrder->addItem(journal);
    esotericOrder->addItem(necronomicon);
    marshRefinery->addItem(cultistRobe);
    seaCaveEntrance->addItem(ancientKey);
    hallOfIdols->addItem(deepOneIdol);
    miskatonicStation->addItem(laudanum);   // starting area — sanity safety net
    rottingDocks->addItem(prayerBook);      // mid-game recovery item

    // ── PASSAGES ─────────────────────────────────────────────────────────────

    // Station <-> Square
    Passage::createBasicPassage(miskatonicStation.get(), innsmouthSquare.get(), "east", true);

    // Square <-> Refinery
    Passage::createBasicPassage(innsmouthSquare.get(), marshRefinery.get(), "east", true);

    // Square <-> Docks
    Passage::createBasicPassage(innsmouthSquare.get(), rottingDocks.get(), "south", true);

    // Refinery <-> Esoteric Order
    Passage::createBasicPassage(marshRefinery.get(), esotericOrder.get(), "south", true);

    // Docks <-> Esoteric Order
    Passage::createBasicPassage(rottingDocks.get(), esotericOrder.get(), "east", true);

    // Docks -> Sea Cave (down)
    Passage::createBasicPassage(rottingDocks.get(), seaCaveEntrance.get(), "down", true);

    // Sea Cave -> Deep One Grotto (south) — DOOR requires cultist-robe
    auto grottoDoor = std::make_shared<Door>(
        "grotto-door",
        "A massive stone door carved with the face of Dagon.",
        seaCaveEntrance.get(), deepOneGrotto.get(),
        "cultist-robe",
        "The stone door will not budge. Carved above it is a warning:\n"
        "NONE SHALL PASS WHO DO NOT BEAR THE MARK OF DAGON.\n"
        "(You need the cultist-robe.)"
    );
    seaCaveEntrance->addPassage("south", grottoDoor);
    Passage::createBasicPassage(deepOneGrotto.get(), seaCaveEntrance.get(), "north", true);

    // Deep One Grotto -> R'lyeh Antechamber (down)
    Passage::createBasicPassage(deepOneGrotto.get(), rlyehAntechamber.get(), "down", true);

    // R'lyeh Antechamber <-> Hall of Idols
    Passage::createBasicPassage(rlyehAntechamber.get(), hallOfIdols.get(), "east", true);

    // R'lyeh Antechamber -> Chamber of Cthulhu (down) — PHRASEDOOR requires "ia-fhtagn"
    // (learned by reading the Necronomicon)
    ZOOrkEngine zoork(miskatonicStation, chamberOfCthulhu);

    auto finalDoor = std::make_shared<PhraseDoor>(
        "final-door",
        "A colossal obsidian gate inscribed with the Elder Sign — inverted.\n"
        "Strange syllables are carved above the arch.",
        rlyehAntechamber.get(), chamberOfCthulhu.get(),
        "ia-fhtagn",
        "The gate does not budge. The carved syllables above seem to demand\n"
        "something — a phrase, spoken aloud, known only to those who have\n"
        "gazed into the Necronomicon.\n"
        "(Read the Necronomicon to learn the phrase, then try again.)",
        zoork.knownPhrases
    );
    rlyehAntechamber->addPassage("down", finalDoor);

    // ── START GAME ───────────────────────────────────────────────────────────
    zoork.run();

    return 0;
}
