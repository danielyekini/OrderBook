#pragma once

#include <string>

#include "exchange_models.hpp"
#include "order_book.hpp"

using namespace exchange_models;
using namespace order_book;

namespace matching {
    class MatchingEngine {
    public:
        MatchingEngine() = default;

        ExecutableOrder execute_order(ExecutableOrder executable, OrderBook book);
    private:
        bool walk_book();

        void remove_filled_orders();
    };
}