#include "HoldemHand.h"

#include <range/v3/all.hpp>

#include <algorithm>

namespace game52 {

HoldemHand52::HoldemHand52(HoleCards const &holeCards, Board const &board)
    : cards_(holeCards.getCards()) {
  cards_.insert(cards_.end(), board.getCards().begin(), board.getCards().end());
  std::sort(cards_.begin(), cards_.end());
  handRank_ = HandRank52::HighCard;
}

HoldemHand52::HoldemHand52(std::vector<Card52>::iterator begin, std::vector<Card52>::iterator end)
    : cards_{begin, end} {
  std::sort(cards_.begin(), cards_.end());
  handRank_ = HandRank52::HighCard;
}

std::vector<Card52> HoldemHand52::getCards() const { return cards_; }

HoldemHand52::HandRank52 HoldemHand52::getClassifiedPokerHand() const {
  return handRank_;
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

bool operator<(HoldemHand52 const& left, HoldemHand52 const& right)
{
    return true;
}
bool operator==(HoldemHand52 const& left, HoldemHand52 const& right)
{
    return !(left < right) && !(right < left);
}

bool operator!=(HoldemHand52 const& left, HoldemHand52 const& right)
{
    return !(left == right);
}

bool operator>(HoldemHand52 const& left, HoldemHand52 const& right)
{
    return right < left;
}

bool operator<=(HoldemHand52 const& left, HoldemHand52 const& right)
{
    return !(left > right);
}

bool operator>=(HoldemHand52 const& left, HoldemHand52 const& right)
{
    return !(left < right);
}

} // namespace game52