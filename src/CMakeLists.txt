add_subdirectory(par)

find_package(range-v3 REQUIRED)

set( LIB_SOURCES 
    Card52.cpp
    Deck52.cpp
    Pot.cpp 
    Nlhe.cpp
    Stack.cpp
    Player.cpp
    HoleCards.cpp
    HandHistory.cpp
    DecisionEngine.cpp
    Board.cpp
    Hand.cpp
    HoldemHand.cpp
    Action.cpp
    Dealer.cpp
    HandRange.cpp
    RatedHand.cpp
    )

set( LIBNAME game)

add_library( ${LIBNAME} SHARED ${LIB_SOURCES} )
target_link_libraries( ${LIBNAME} range-v3::range-v3)