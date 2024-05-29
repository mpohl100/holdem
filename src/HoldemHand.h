#pragma once

#include "Board.h"
#include "HoleCards.h"

#include <vector>

namespace game52{

class HoldemHand52{
public:
    enum HandRank52{
        HighCard,
        Pair,
        TwoPair,
        Trips,
        Straight,
        Flush,
        FullHouse,
        Quads,
        StraightFlush,
    };

    HoldemHand52(HoleCards const& holeCards, Board const& board);
    HoldemHand52(std::vector<Card52>::iterator begin, std::vector<Card52>::iterator end);
    HoldemHand52() = default;
    HoldemHand52(HoldemHand52 const&) = default;
    HoldemHand52& operator=(HoldemHand52 const&) = default;
    HoldemHand52(HoldemHand52&&) = default;
    HoldemHand52& operator=(HoldemHand52&&) = default;
    
    std::vector<Card52> getCards() const;
    HandRank52 getClassifiedPokerHand() const;

    static HoldemHand52 fromString(std::string const& str);

    friend bool operator<(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator==(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator!=(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator>(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator<=(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator>=(HoldemHand52 const& left, HoldemHand52 const& right);
private:
    std::vector<Card52> cards_;
    HandRank52 handRank_;
};

} // namespace game52