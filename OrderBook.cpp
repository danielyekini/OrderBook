#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <iterator>
#include <sstream>
#include <stdexcept>

#include "order_book.hpp"

using namespace exchange_models;

namespace order_book {
    bool OrderBook::add_order(ExecutableOrder executable) {
        if (executable.remaining_qty <= 0) return false;

        auto book = (executable.side == BID) ? bids_ : asks_;
        LiveOrder live_order = LiveOrder(
            executable.order_record_id,
            executable.remaining_qty,
            *executable.price,
            executable.status
        );
        std::list<LiveOrder> level = book[live_order.price];
        level.push_back(live_order);

        auto it = std::prev(level.end());
        address_book_[live_order.id] = OrderLocation{
            executable.side,
            live_order.price,
            it
        };

        return true;
    }

    bool OrderBook::remove_order(std::string order_id) {
        if (address_book_.find(order_id) == address_book_.end())
            return false;
        
        OrderLocation addr = address_book_[order_id];
        auto book = (addr.side == BID) ? bids_ : asks_;
        book[addr.price_level].erase(addr.it);

        return true;
    }

    std::map<double, std::list<LiveOrder>> OrderBook::bids() { return bids_; }

    std::map<double, std::list<LiveOrder>> OrderBook::asks() { return asks_; }

    double OrderBook::best_ask() {
        std::list<LiveOrder> book_top = asks_.begin()->second;
        LiveOrder best_ask = book_top.front();
        return best_ask.price;
    }

    double OrderBook::best_bid() {
        std::list<LiveOrder> book_top = bids_.end()->second;
        LiveOrder best_bid = book_top.front();
        return best_bid.price;
    }

    int OrderBook::best_ask_size() {
        std::list<LiveOrder> book_top = asks_.begin()->second;
        int size = 0;

        for (auto order : book_top) {
            size += order.remaining_qty;
        }

        return size;
    }

    int OrderBook::best_bid_size() {
        std::list<LiveOrder> book_top = bids_.end()->second;
        int size = 0;

        for (auto order : book_top) {
            size += order.remaining_qty;
        }

        return size;
    }

    int OrderBook::volume() {
        int total_vol = 0;
        for (auto entry : address_book_) {
            LiveOrder order = locate_live_order(entry.first);
            total_vol += order.remaining_qty;
        }
        return total_vol;
    }

    int OrderBook::size() { return address_book_.size(); }

    void OrderBook::record_trade(std::string bid_id, std::string ask_id, int qty, double price) {
        Trade trade = Trade(bid_id, ask_id, qty, price);
        trade_log_.emplace(trade.id, trade);
    }

    std::string OrderBook::trade_history_to_string() {
        std::stringstream trade_ss;
        trade_ss << "\n------------------------- TRADE HISTORY -------------------------\n";
        trade_ss << "Timestamp                   BID ID     ASK ID     Price  Qty\n";
        trade_ss << "  Price      Qty\n";
        for (auto trade : trade_log_) {
            Trade trade_data = trade.second;
            double timestamp = trade_data.ts;
            std::string bid_id = trade_data.bid_id;
            std::string ask_id = trade_data.ask_id;
            double price = trade_data.price;
            int qty = trade_data.qty;
            trade_ss << timestamp << "                   " << bid_id << "  " << ask_id << "  " << price << "  " << qty << "\n";
        }
        trade_ss << "----------------------------------------------------------------\n";
        
        return trade_ss.str();
    }

    std::string OrderBook::to_string() {
        std::stringstream book_ss;
        book_ss << "\n-------------------- ORDER BOOK --------------------\n";
        book_ss << "                 ASK (Sell)\n";
        book_ss << "  Price      Qty\n";
        for (auto price_level : asks_) {
            double price = price_level.first;
            int volume = volume_at_price(asks_, price);
            book_ss << "  " << price << "      " << volume << "\n";
        }
        book_ss << "---------------- MID ----------------\n";
        for (auto price_level : bids_) {
            double price = price_level.first;
            int volume = volume_at_price(bids_, price);
            book_ss << "  " << price << "      " << volume << "\n";
        }
        book_ss << "                 BID (Buy)\n";
        book_ss << "----------------------------------------------------\n";
        
        return book_ss.str();
    }

    LiveOrder OrderBook::locate_live_order(std::string order_id) {
        if (address_book_.find(order_id) == address_book_.end())
            throw std::invalid_argument("Order is not live");

        OrderLocation addr = address_book_[order_id];
        auto book = (addr.side == BID) ? bids_ : asks_;

        return *addr.it;
    }

    int OrderBook::volume_at_price(std::map<double, std::list<LiveOrder>> book, double price) {
        std::list<LiveOrder> orders = book[price];
        int volume = 0;
        for (LiveOrder order : orders) volume += order.remaining_qty;

        return volume;
    }
}


        // double get_spread() {
        //     double best_bid = get_best_bid();
        //     double best_ask = get_best_ask();

        //     return best_ask - best_bid;
        // }

        // double get_mid_price() {
        //     double best_bid = get_best_bid();
        //     double best_ask = get_best_ask();

        //     return (best_ask + best_bid) / 2;
        // }
        // OrderMetadata get_order(std::string order_id) {
        //     OrderLocation addr = locate_order(order_id);
        //     return *addr.it;
        // }

        // bool modify_order(std::string order_id, double new_price = NULL, int new_qty = NULL) {
        //     LiveOrder* order = locate_live_order(order_id);

        //     if (order == nullptr)
        //         throw std::runtime_error("Inactive orders cannot be modified");

        //     if (order.quantity())

        //     if (new_qty && new_qty > 0) order.get_qty() = new_qty;

        //     if (new_price) {
        //         bool order_removed = remove_order(order);

        //         if (!order_removed) throw std::runtime_error("Failed to modify order");

        //         order.price = new_price;
        //         // TODO: Re-process order

        //     }
        // }