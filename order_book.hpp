#pragma once

#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include "exchange_models.hpp"

using namespace exchange_models;

namespace order_book 
{
    class OrderBook {
    public:
        OrderBook() = default;

        bool add_order(ExecutableOrder executable);

        bool remove_order(std::string order_id);

        std::map<double, std::list<LiveOrder>> bids();

        std::map<double, std::list<LiveOrder>> asks();

        double best_ask();

        double best_bid();

        int best_ask_size();

        int best_bid_size();

        int volume();

        int size();

        void record_trade(std::string bid_id, std::string ask_id, int qty, double price);

        std::string trade_history_to_string();

        std::string to_string();

    private:
        struct OrderLocation {
            exchange_models::OrderSide side;
            double price_level;
            std::list<LiveOrder>::iterator it;
        };

        std::map<double, std::list<LiveOrder>> bids_;
        std::map<double, std::list<LiveOrder>> asks_;
        std::unordered_map<std::string, OrderLocation> address_book_;
        std::unordered_map<std::string, Trade> trade_log_;
        
        LiveOrder locate_live_order(std::string order_id);

        int volume_at_price(std::map<double, std::list<LiveOrder>> book, double price);
    };
}
