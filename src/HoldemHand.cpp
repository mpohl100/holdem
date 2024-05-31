#include "HoldemHand.h"

#include <range/v3/all.hpp>

#include <algorithm>
#include <iostream>

namespace {
bool compareHighCards(std::vector<game52::Rank52> const &l,
                      std::vector<game52::Rank52> const &r) {
  return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}
} // namespace

namespace game52 {

HoldemHand52::HoldemHand52(HoleCards const &holeCards, Board const &board)
    : cards_(holeCards.getCards()),
      rankOccurences_(static_cast<size_t>(Rank52::Ace) + 2, 0),
      suitOccurences_(4, 0) {
  cards_.insert(cards_.end(), board.getCards().begin(), board.getCards().end());
  std::sort(cards_.begin(), cards_.end());
  classifyHand();
}

HoldemHand52::HoldemHand52(std::vector<Card52>::iterator begin,
                           std::vector<Card52>::iterator end)
    : cards_({begin, end}),
      rankOccurences_(static_cast<size_t>(Rank52::Ace) + 2, 0),
      suitOccurences_(4, 0) {
  std::sort(cards_.begin(), cards_.end());
  classifyHand();
}

std::vector<Card52> HoldemHand52::getCards() const { return cards_; }

HoldemHand52::HandRank52 HoldemHand52::getClassifiedPokerHand() const {
  return handRank_;
}

std::array<Rank52, 2> HoldemHand52::findOccurences(int nb) const {
  std::array<Rank52, 2> result;
  size_t count = 0;
  for (int i = static_cast<int>(rankOccurences_.size() - 1); i >= 0; --i) {
    if (rankOccurences_[i] == nb) {
      result[count] = static_cast<Rank52>(i - 1);
      ++count;
    }
    if (count == 2) {
      break;
    }
  }
  return result;
}

std::vector<Rank52>
getFirstNHighCards(std::vector<std::uint8_t> const &rankOccurences, size_t N,
                   std::vector<Card52> const &cards) {
  auto highCards = std::vector<Rank52>{};
  highCards.reserve(N);
  for (int i = static_cast<int>(rankOccurences.size() - 1); i >= 0; --i) {
    if (rankOccurences[static_cast<size_t>(i)] == 1) {
      highCards.push_back(static_cast<Rank52>(i - 1));
    }
    if (highCards.size() == N) {
      break;
    }
  }
  return highCards;
}

std::vector<Rank52> HoldemHand52::getHighCards() const {
  switch (handRank_) {
  case HighCard: {
    auto highCards = std::vector<Rank52>{};
    highCards.reserve(5);
    for (auto card : cards_ | ranges::views::reverse) {
      highCards.push_back(card.rank());
      if (highCards.size() == 5) {
        break;
      }
    }
    return highCards;
  }
  case Pair: {
    return getFirstNHighCards(rankOccurences_, 3, cards_);
  }
  case TwoPair: {
    return getFirstNHighCards(rankOccurences_, 1, cards_);
  }
  case Trips: {
    return getFirstNHighCards(rankOccurences_, 2, cards_);
  }
  case Straight: {
    auto straightRank = getStraightRank(rankOccurences_);
    auto highCards = std::vector<Rank52>{};
    highCards.reserve(5);
    auto rank = *straightRank;
    return {rank};
  }
  case Flush: {
    auto flushSuit = getFlushSuit(suitOccurences_);
    auto highCards = std::vector<Rank52>{};
    for (auto card : cards_) {
      if(card.suit() != *flushSuit){
        continue;
      }
      highCards.push_back(card.rank());
      if (highCards.size() == 5) {
        break;
      }
    }
    std::cout << "Flush ranks:\n";
    for(const auto& rank : highCards){
      std::cout << rank << " ";
    }
    std::cout << '\n';
    std::sort(highCards.begin(), highCards.end());
    std::reverse(highCards.begin(), highCards.end());
    return highCards;
  }
  case FullHouse: {
    return {};
  }
  case Quads: {
    return getFirstNHighCards(rankOccurences_, 1, cards_);
  }
  case StraightFlush: {
    auto straightRank = getStraightRank(rankOccurences_);
    return {*straightRank};
  }
  }
  return {};
}

int HoldemHand52::sum() const {
  auto highCards = getHighCards();
  int sum = 0;
  for (auto card : highCards) {
    sum += card;
  }
  return sum;
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

void HoldemHand52::classifyHand() {
  // we will use the rankOccurences_ and suitOccurences_ to classify the hand
  size_t differentRanks = 0;
  size_t ranksSize = rankOccurences_.size();
  size_t suitsSize = suitOccurences_.size();
  for (const auto &card : cards_) {
    auto &rank = rankOccurences_[static_cast<std::uint8_t>(card.rank() + 1)];
    rank++;
    if (rank == 1) {
      ++differentRanks;
    }
    if (card.rank() == Rank52::Ace) {
      ++rankOccurences_[0];
    }
    ++suitOccurences_[static_cast<std::uint8_t>(card.suit())];
  }

  auto flushSuit = getFlushSuit(suitOccurences_);
  auto straightRank = getStraightRank(rankOccurences_);
  if (differentRanks == cards_.size() && !flushSuit && !straightRank) {
    handRank_ = HighCard;
    return;
  }
  if (differentRanks == cards_.size() - 1 && !flushSuit && !straightRank) {
    handRank_ = Pair;
    return;
  }
  if (differentRanks == cards_.size() - 2 && !flushSuit && !straightRank) {
    // either it is trips or two pair
    for (int i = static_cast<int>(rankOccurences_.size() - 1); i >= 0; --i) {
      if (rankOccurences_[i] == 3) {
        handRank_ = Trips;
        return;
      }
    }
    handRank_ = TwoPair;
    return;
  }
  if (differentRanks == cards_.size() - 3 && !flushSuit && !straightRank) {
    // it could be quads or full house or trips or three pair
    for (int i = static_cast<int>(rankOccurences_.size() - 1); i >= 0; --i) {
      if (rankOccurences_[i] == 4) {
        handRank_ = Quads;
        return;
      } else if (rankOccurences_[i] == 3) {
        handRank_ = FullHouse;
        return;
      }
    }
    handRank_ = TwoPair;
    return;
  }
  if (flushSuit && !straightRank) {
    handRank_ = Flush;
    return;
  }
  if (straightRank && !flushSuit) {
    handRank_ = Straight;
    return;
  }
  if (straightRank && flushSuit) {
    auto rank = *straightRank;
    auto suit = *flushSuit;
    for (size_t i = 0; i < 5; ++i) {
      auto card = std::find(cards_.begin(), cards_.end(), Card52(rank, suit));
      if (card == cards_.end()) {
        handRank_ = Flush;
      }
      if (rank == Rank52::Deuce) {
        rank = Rank52::Ace;
      } else {
        rank = static_cast<Rank52>(static_cast<std::uint8_t>(rank) - 1);
      }
    }
    handRank_ = StraightFlush;
    return;
  }
}

std::optional<Suit> HoldemHand52::getFlushSuit(
    std::vector<std::uint8_t> const &suitOccurences) const {
  auto flushSuit = std::find_if(suitOccurences.begin(), suitOccurences.end(),
                                [](auto occurence) { return occurence >= 5; });
  if (flushSuit != suitOccurences.end())
    return static_cast<Suit>(std::distance(flushSuit, suitOccurences.begin()));
  return std::nullopt;
}

std::optional<Rank52> HoldemHand52::getStraightRank(
    std::vector<std::uint8_t> const &rankOccurences) const {
  size_t neighboursCount = 0;
  std::optional<Rank52> currentStartRank = std::nullopt;
  for (int i = static_cast<int>(rankOccurences.size() - 1); i >= 0; --i) {
    if (neighboursCount == 4) {
      return currentStartRank;
    }
    if (rankOccurences[i] > 0) {
      if (currentStartRank == std::nullopt) {
        currentStartRank = static_cast<Rank52>(i - 1);
        neighboursCount = 1;
      } else {
        ++neighboursCount;
      }
    } else {
      neighboursCount = 0;
      currentStartRank = std::nullopt;
    }
  }
  return std::nullopt;
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
    auto leftHighCards = l.getHighCards();
    auto rightHighCards = r.getHighCards();
    std::cout << "Left high cards\n";
    for(const auto& rank : leftHighCards){
      std::cout << rank << " ";
    }
    std::cout << "\nright high cards\n";
    for(const auto& rank : rightHighCards){
      std::cout << rank << " ";
    }
    std::cout << '\n';
    return compareHighCards(leftHighCards, rightHighCards);
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