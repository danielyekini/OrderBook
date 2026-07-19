#include "matching.hpp"
#include "exchange_models.hpp"

using namespace exchange_models; 

namespace matching {
    ExecutableOrder MatchingEngine::execute_order(ExecutableOrder executable, OrderBook book) { return executable; }
    
    bool MatchingEngine::walk_book() { return true; }

    void MatchingEngine::remove_filled_orders() {}
}