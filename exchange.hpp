#pragma once

#include <string>
#include <map>
#include <iostream>

#include "exchange_models.hpp"
#include "order_request.hpp"
#include "order_book.hpp"
#include "matching.hpp"
#include "exchange.hpp"

using namespace order_request;

namespace exchange {
    class ExchangeClient {};

    class Exchange {
    public:
        Exchange() = default;

        bool process_new_order_request(NewOrderRequest request);

        bool process_modify_order_request(ModifyOrderRequest request);

        bool process_cancel_order_request(CancelOrderRequest request);

        void print_book();
    private:
        order_book::OrderBook book_;
        matching::MatchingEngine engine_;
        std::map<std::string, AcceptedOrderRecord> order_records_;

        bool validate_order_request(int quantity, std::optional<double> price);

        AcceptedOrderRecord create_order_record(NewOrderRequest request);
    };
}