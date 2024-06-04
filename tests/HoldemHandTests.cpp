#include <catch2/catch_all.hpp>

#include "HoldemHand.h"
#include <vector>

using namespace game52;

namespace {

TEST_CASE("HoldemHands", "[holdem_hand]") {
    SECTION("HandRanks"){ 
            CHECK(HoldemHand52::fromString("Kh Td 2c 3s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::HighCard);
            CHECK(HoldemHand52::fromString("Ah Td 2c 3s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::HighCard);
            CHECK(HoldemHand52::fromString("Kh 2h 2c Qs Jd").getClassifiedPokerHand() == HoldemHand52::HandRank52::Pair);
            CHECK(HoldemHand52::fromString("Ah 2h 2c 3s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::Pair);
            CHECK(HoldemHand52::fromString("Ah 2h 2c 4s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::Pair);
            CHECK(HoldemHand52::fromString("Ah Td Tc 3s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::Pair);
            CHECK(HoldemHand52::fromString("Ah Ad 2c 3s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::Pair);
            CHECK(HoldemHand52::fromString("Qh Qd 2c 2s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::TwoPair);
            CHECK(HoldemHand52::fromString("Qh Qd Jc Js 6d").getClassifiedPokerHand() == HoldemHand52::HandRank52::TwoPair);
            CHECK(HoldemHand52::fromString("Ah Ad 2c 2s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::TwoPair);
            CHECK(HoldemHand52::fromString("Ah 2d 2c 2s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::Trips);
            CHECK(HoldemHand52::fromString("Ah Ad Ac 2s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::Trips);
            CHECK(HoldemHand52::fromString("Ah Ad Ac 3s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::Trips);
            CHECK(HoldemHand52::fromString("Ah 2d 3c 4s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::Straight);
            CHECK(HoldemHand52::fromString("2d 3c 4s 5d 6c").getClassifiedPokerHand() == HoldemHand52::HandRank52::Straight);
            CHECK(HoldemHand52::fromString("Ah 2h Kh 4h 5h").getClassifiedPokerHand() == HoldemHand52::HandRank52::Flush);
            CHECK(HoldemHand52::fromString("Ah 2h Kh 6h 5h").getClassifiedPokerHand() == HoldemHand52::HandRank52::Flush);
            CHECK(HoldemHand52::fromString("5h 2d 2c 2s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::FullHouse);
            CHECK(HoldemHand52::fromString("6h 2d 2c 2s 6d").getClassifiedPokerHand() == HoldemHand52::HandRank52::FullHouse);
            CHECK(HoldemHand52::fromString("5h 3d 3c 3s 5d").getClassifiedPokerHand() == HoldemHand52::HandRank52::FullHouse);
            CHECK(HoldemHand52::fromString("5h 2d 2c 2s 2h").getClassifiedPokerHand() == HoldemHand52::HandRank52::Quads);
            CHECK(HoldemHand52::fromString("5h 3d 3c 3s 3h").getClassifiedPokerHand() == HoldemHand52::HandRank52::Quads);
            CHECK(HoldemHand52::fromString("Ah 2h 3h 4h 5h").getClassifiedPokerHand() == HoldemHand52::HandRank52::StraightFlush);
            CHECK(HoldemHand52::fromString("2h 3h 4h 5h 6h").getClassifiedPokerHand() == HoldemHand52::HandRank52::StraightFlush);
            CHECK(HoldemHand52::fromString("Th Jh Qh Kh Ah").getClassifiedPokerHand() == HoldemHand52::HandRank52::StraightFlush);
    }
    SECTION("HandsSorted") {
        std::vector<HoldemHand52> hands{
            HoldemHand52::fromString("Kh Td 2c 3s 5d"),
            HoldemHand52::fromString("Ah Td 2c 3s 5d"),
            HoldemHand52::fromString("Kh 2h 2c Qs Jd"),
            HoldemHand52::fromString("Ah 2h 2c 3s 5d"),
            HoldemHand52::fromString("Ah 2h 2c Ks 5d"),
            HoldemHand52::fromString("Ah 2h 2c Ks Qd"),
            HoldemHand52::fromString("Ah Td Tc 3s 5d"),
            HoldemHand52::fromString("Ah Ad 2c 3s 5d"),
            HoldemHand52::fromString("Qh Qd 2c 2s 5d"),
            HoldemHand52::fromString("Qh Qd Jc Js 6d"),
            HoldemHand52::fromString("Ah Ad 2c 2s 5d"),
            HoldemHand52::fromString("Ah 2d 2c 2s 5d"),
            HoldemHand52::fromString("Ah Ad Ac 2s 5d"),
            HoldemHand52::fromString("Ah Ad Ac 3s 5d"),
            HoldemHand52::fromString("Ah 2d 3c 4s 5d"),
            HoldemHand52::fromString("2d 3c 4s 5d 6c"),
            HoldemHand52::fromString("Ah 2h Kh 4h 5h"),
            HoldemHand52::fromString("Ah 2h Kh 6h 5h"),
            HoldemHand52::fromString("5h 2d 2c 2s 5d"),
            HoldemHand52::fromString("6h 2d 2c 2s 6d"),
            HoldemHand52::fromString("5h 3d 3c 3s 5d"),
            HoldemHand52::fromString("5h 2d 2c 2s 2h"),
            HoldemHand52::fromString("5h 3d 3c 3s 3h"),
            HoldemHand52::fromString("Ah 2h 3h 4h 5h"),
            HoldemHand52::fromString("2h 3h 4h 5h 6h"),
            HoldemHand52::fromString("Th Jh Qh Kh Ah"),
        };
        CHECK(std::is_sorted(hands.begin(), hands.end()));
    }
    SECTION("Equality"){
        CHECK(HoldemHand52::fromString("Ah Kc 2h 7s Td") == HoldemHand52::fromString("Ac Kc 2h 7d Ts"));
        CHECK(HoldemHand52::fromString("Ah 2c 2h 7s Td") == HoldemHand52::fromString("Ac 2s 2h 7d Ts"));
        CHECK(HoldemHand52::fromString("Ah 2c 2h 7s 7d") == HoldemHand52::fromString("Ac 2c 2h 7d 7c"));
        CHECK(HoldemHand52::fromString("Ah Kc 2h 2s 2d") == HoldemHand52::fromString("Ah Kh 2h 2d 2s"));
        CHECK(HoldemHand52::fromString("Ah 2c 3h 4s 5d") == HoldemHand52::fromString("Ac 2c 3h 4d 5s"));
        CHECK(HoldemHand52::fromString("Ah Kh 3h 4h 5h") == HoldemHand52::fromString("As Ks 3s 4s 5s"));
        CHECK(HoldemHand52::fromString("2h 2c 2d 4s 4d") == HoldemHand52::fromString("2s 2c 2h 4c 4s"));
        CHECK(HoldemHand52::fromString("2h 2c 2d 2s 4d") == HoldemHand52::fromString("2s 2c 2h 2d 4s"));
        CHECK(HoldemHand52::fromString("Ah 2h 3h 4h 5h") == HoldemHand52::fromString("As 2s 3s 4s 5s"));
        CHECK(HoldemHand52::fromString("2h 3h 4h 5h 6h") == HoldemHand52::fromString("2s 3s 4s 5s 6s"));           
    }
    SECTION("SixCardHands"){
        const auto straightFlush = HoldemHand52::fromString("Ah 2h 3h 4h 5h 6s");
        CHECK(straightFlush.getClassifiedPokerHand() == HoldemHand52::HandRank52::StraightFlush);
        CHECK(straightFlush.getHighCards() == std::vector<Rank52>{Rank52::Five});

        const auto highStraightFlush = HoldemHand52::fromString("Th Jh Qh Kh Ah 9s");
        CHECK(highStraightFlush.getClassifiedPokerHand() == HoldemHand52::HandRank52::StraightFlush);
        CHECK(highStraightFlush.getHighCards() == std::vector<Rank52>{Rank52::Ace});

        const auto quadsHighCard = HoldemHand52::fromString("Ah 2h 2c 2s 2d As");
        CHECK(quadsHighCard.getClassifiedPokerHand() == HoldemHand52::HandRank52::Quads);
        CHECK(quadsHighCard.getHighCards() == std::vector<Rank52>{Rank52::Ace});

        const auto quadsHighCard2 = HoldemHand52::fromString("Qh 2h 2c 2s 2d Ks");
        CHECK(quadsHighCard2.getClassifiedPokerHand() == HoldemHand52::HandRank52::Quads);
        CHECK(quadsHighCard2.getHighCards() == std::vector<Rank52>{Rank52::Ace});

        const auto fullHouse = HoldemHand52::fromString("5h 2d 2c 2s 5d 5c");
        CHECK(fullHouse.getClassifiedPokerHand() == HoldemHand52::HandRank52::FullHouse);
        CHECK(fullHouse.getRanksMattering() == std::vector<Rank52>{Rank52::Five, Rank52::Deuce});

        const auto twoPair = HoldemHand52::fromString("5h 2d 2c 6s 5d 6c");
        CHECK(twoPair.getClassifiedPokerHand() == HoldemHand52::HandRank52::TwoPair);
        CHECK(twoPair.getRanksMattering() == std::vector<Rank52>{Rank52::Six, Rank52::Five});
        CHECK(twoPair.getHighCards() == std::vector<Rank52>{Rank52::Deuce});

        const auto twoPair2 = HoldemHand52::fromString("5h 2d Kc 6s 5d 6c");
        CHECK(twoPair2.getClassifiedPokerHand() == HoldemHand52::HandRank52::TwoPair);
        CHECK(twoPair2.getRanksMattering() == std::vector<Rank52>{Rank52::Six, Rank52::Five});
        CHECK(twoPair2.getHighCards() == std::vector<Rank52>{Rank52::King});
    }
    SECTION("SevenCardHands"){
        const auto straightFlush = HoldemHand52::fromString("Ah 2h 3h 4h 5h 6s 7s");
        CHECK(straightFlush.getClassifiedPokerHand() == HoldemHand52::HandRank52::StraightFlush);
        CHECK(straightFlush.getHighCards() == std::vector<Rank52>{Rank52::Five});

        const auto highStraightFlush = HoldemHand52::fromString("Th Jh Qh Kh Ah 9s 8s");
        CHECK(highStraightFlush.getClassifiedPokerHand() == HoldemHand52::HandRank52::StraightFlush);
        CHECK(highStraightFlush.getHighCards() == std::vector<Rank52>{Rank52::Ace});

        const auto quadsHighCard = HoldemHand52::fromString("Ah 2h 2c 2s 2d As Ac");
        CHECK(quadsHighCard.getClassifiedPokerHand() == HoldemHand52::HandRank52::Quads);
        CHECK(quadsHighCard.getHighCards() == std::vector<Rank52>{Rank52::Ace});

        const auto quadsHighCard2 = HoldemHand52::fromString("Qh 2h 2c 2s 2d Ks Jd");
        CHECK(quadsHighCard2.getClassifiedPokerHand() == HoldemHand52::HandRank52::Quads);
        CHECK(quadsHighCard2.getHighCards() == std::vector<Rank52>{Rank52::Ace});

        const auto fullHouse = HoldemHand52::fromString("5h 2d 2c 2s 5d 4s 4d");
        CHECK(fullHouse.getClassifiedPokerHand() == HoldemHand52::HandRank52::FullHouse);
        CHECK(fullHouse.getRanksMattering() == std::vector<Rank52>{Rank52::Five, Rank52::Deuce});

        const auto twoPair = HoldemHand52::fromString("5h 2d 2c 6s 5d 6c Ah");
        CHECK(twoPair.getClassifiedPokerHand() == HoldemHand52::HandRank52::TwoPair);
        CHECK(twoPair.getRanksMattering() == std::vector<Rank52>{Rank52::Six, Rank52::Five});
        CHECK(twoPair.getHighCards() == std::vector<Rank52>{Rank52::Deuce});

        const auto twoPair2 = HoldemHand52::fromString("5h 2d Kc 6s 5d 6c Qh");
        CHECK(twoPair2.getClassifiedPokerHand() == HoldemHand52::HandRank52::TwoPair);
        CHECK(twoPair2.getRanksMattering() == std::vector<Rank52>{Rank52::Six, Rank52::Five});
        CHECK(twoPair2.getHighCards() == std::vector<Rank52>{Rank52::King});
    }
}

}

