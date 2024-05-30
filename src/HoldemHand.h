#pragma once

#include "Board.h"
#include "HoleCards.h"

#include <array>
#include <optional>
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
    std::array<Rank52,2> findOccurences(int nb) const;
    std::vector<Rank52> getHighCards() const;

    static HoldemHand52 fromString(std::string const& str);

    friend bool operator<(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator==(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator!=(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator>(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator<=(HoldemHand52 const& left, HoldemHand52 const& right);
    friend bool operator>=(HoldemHand52 const& left, HoldemHand52 const& right);
private:

    void classifyHand();
    std::optional<Suit> getFlushSuit(std::vector<std::uint8_t> const& suitOccurences) const;
    std::optional<Rank52> getStraightRank(std::vector<std::uint8_t> const& rankOccurences) const;

    std::vector<Card52> cards_;
    HandRank52 handRank_;
    // members for details of flush and straight
    std::vector<Rank52> relevanthighCards_;
    std::vector<std::uint8_t> rankOccurences_;
    std::vector<std::uint8_t> suitOccurences_; 
};

} // namespace game52