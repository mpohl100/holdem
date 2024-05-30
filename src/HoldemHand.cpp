#include "HoldemHand.h"

#include <range/v3/all.hpp>

#include <algorithm>

namespace game52 {

HoldemHand52::HoldemHand52(HoleCards const &holeCards, Board const &board)
    : cards_(holeCards.getCards()) {
  cards_.insert(cards_.end(), board.getCards().begin(), board.getCards().end());
  std::sort(cards_.begin(), cards_.end());
  classifyHand();
}

HoldemHand52::HoldemHand52(std::vector<Card52>::iterator begin,
                           std::vector<Card52>::iterator end)
    : cards_{begin, end} {
  std::sort(cards_.begin(), cards_.end());
  classifyHand();
}

std::vector<Card52> HoldemHand52::getCards() const { return cards_; }

HoldemHand52::HandRank52 HoldemHand52::getClassifiedPokerHand() const {
  return handRank_;
}

std::array<Rank52, 2> HoldemHand52::findOccurences(int nb) const {
  return {Rank52::Ace, Rank52::Ace};
}
std::vector<Rank52> HoldemHand52::getHighCards() const {
  return {Rank52::Ace, Rank52::Ace};
}

HoldemHand52 HoldemHand52::fromString(std::string const &str) {
  auto cards = str | ranges::views::split(' ') |
               ranges::views::transform([](auto &&rng) {
                 return std::string(&*rng.begin(), std::ranges::distance(rng));
               });
  std::vector<Card52> hand;
  for (auto card : cards)
    hand.push_back(Card52(card));
  return HoldemHand52(hand.begin(), hand.end());
}

void classifyHand() {
  for(const auto& card : cards_){
    ++rankOccurences_[static_cast<std::uint8_t>(card.getRank() + 1)];
    if(card.getRank() == Rank52::Ace)
      ++rankOccurences_[0];
    ++suitOccurences_[static_cast<std::uint8_t>(card.getSuit())];
  }

  auto flushSuit = getFlushSuit(suitOccurences_);
  auto straightRank = getStraightRank(rankOccurences_);

}

std::optional<Suit> HoldemHand52::getFlushSuit(std::vector<std::uint8_t> const& suitOccurences) const {
  auto flushSuit = std::find(suitOccurences.begin(), suitOccurences.end(), 5);
  if(flushSuit != suitOccurences.end())
    return static_cast<Suit>(std::distance(flushSuit, suitOccurences.begin()));
  return std::nullopt;
}


std::optional<Rank52> HoldemHand52::getStraightRank(std::vector<std::uint8_t> const& rankOccurences) const
{
  size_t neighboursCount = 0;
  std::optional<Rank52> currentStartRank = std::nullopt;
  for(size_t i = rankOccurences.size() - 1; i >= 0; --i){
    if(neighboursCount == 4){
      break;
    }
    if(rankOccurences[i] > 0){
      if(currentStartRank == std::nullopt){
        currentStartRank = static_cast<Rank52>(i-1);
        neighboursCount = 1;
      }else{
        ++neightboursCount;
      }
    }
    else{
      neighboursCount = 0;
      currentStartRank = std::nullopt;
    }
  }
  return currentStartRank;
}

bool compareHighCards(std::vector<Rank52> const &l,
                      std::vector<Rank52> const &r) {
  return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}

bool operator<(HoldemHand52 const &l, HoldemHand52 const &r) {
  if (l.handRank_ != r.handRank_)
    return l.handRank_ < r.handRank_;
  // detailed looking into the higher hand

  // high card
  if (l.handRank_ == HoldemHand52::HighCard) {
    return compareHighCards(l.getHighCards(), r.getHighCards());
  }
  if (l.handRank_ == HoldemHand52::Pair) {
    auto lpairRank = l.findOccurences(2);
    auto rPairRank = r.findOccurences(2);
    if (lpairRank[0] != rPairRank[0])
      return lpairRank[0] < rPairRank[0];
    return compareHighCards(
        l.getHighCards(),
        r.getHighCards()); // if pairs are even, the higher card wins
  }
  if (l.handRank_ == HoldemHand52::TwoPair) {
    auto lpairRank = l.findOccurences(2);
    auto rPairRank = r.findOccurences(2);
    if (lpairRank[0] != rPairRank[0])
      return lpairRank[0] < rPairRank[0];
    if (lpairRank[1] != rPairRank[1])
      return lpairRank[1] < rPairRank[1];
    return compareHighCards(
        l.getHighCards(),
        r.getHighCards()); // if pairs are even, the higher card wins
  }
  if (l.handRank_ == HoldemHand52::Trips) {
    auto lpairRank = l.findOccurences(3);
    auto rPairRank = r.findOccurences(3);
    if (lpairRank[0] != rPairRank[0])
      return lpairRank[0] < rPairRank[0];
    return compareHighCards(
        l.getHighCards(),
        r.getHighCards()); // if trips are even, the higher card wins
  }
  if (l.handRank_ == HoldemHand52::Straight) {
    // not easy you have to take wheel into account
    int lSum = l.sum();
    if (lSum == Ace + Deuce + Three + Four + Five)
      lSum -= Ace;
    int rSum = r.sum();
    if (rSum == Ace + Deuce + Three + Four + Five)
      rSum -= Ace;
    return lSum < rSum;
  }
  if (l.handRank_ == HoldemHand52::Flush) {
    return compareHighCards(l.getHighCards(), r.getHighCards());
  }
  if (l.handRank_ == HoldemHand52::FullHouse) {
    // check trips
    auto lpairRank = l.findOccurences(3);
    auto rPairRank = r.findOccurences(3);
    if (lpairRank[0] != rPairRank[0])
      return lpairRank[0] < rPairRank[0];
    // check pair
    lpairRank = l.findOccurences(2);
    rPairRank = r.findOccurences(2);
    if (lpairRank[0] != rPairRank[0])
      return lpairRank[0] < rPairRank[0];
    return compareHighCards(l.getHighCards(), r.getHighCards());
  }
  if (l.handRank_ == HoldemHand52::Quads) {
    auto lpairRank = l.findOccurences(4);
    auto rPairRank = r.findOccurences(4);
    if (lpairRank[0] != rPairRank[0])
      return lpairRank[0] < rPairRank[0];
    return compareHighCards(l.getHighCards(), r.getHighCards());
  }
  if (l.handRank_ == HoldemHand52::StraightFlush) {
    int lSum = l.sum();
    if (lSum == Ace + Deuce + Three + Four + Five)
      lSum -= Ace;
    int rSum = r.sum();
    if (rSum == Ace + Deuce + Three + Four + Five)
      rSum -= Ace;
    return lSum < rSum;
  }
  // we shouldn't come here
  throw std::runtime_error(
      "programming error: reached end of classified hand operator<.");
  return false;
}
bool operator==(HoldemHand52 const &left, HoldemHand52 const &right) {
  return !(left < right) && !(right < left);
}

bool operator!=(HoldemHand52 const &left, HoldemHand52 const &right) {
  return !(left == right);
}

bool operator>(HoldemHand52 const &left, HoldemHand52 const &right) {
  return right < left;
}

bool operator<=(HoldemHand52 const &left, HoldemHand52 const &right) {
  return !(left > right);
}

bool operator>=(HoldemHand52 const &left, HoldemHand52 const &right) {
  return !(left < right);
}

} // namespace game52