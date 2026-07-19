#pragma once

#include <string>
#include <optional>

#include "order_request.hpp"

namespace exchange_models {
    enum OrderStatus { PENDING, WORKING, PARTIALLY, FILLED, CANCELLED, FAILED };

    enum OrderType { MARKET, LIMIT };

    enum OrderSide { BID, ASK };

    struct AcceptedOrderRecord {
        const std::string id;
        const OrderSide side;
        const int qty;
        int remaining_quantity;
        const std::optional<double> price;
        const OrderType type;
        OrderStatus status;
        const std::string participant_code;
        const time_t created_at;
        const std::optional<time_t> updated_at;

        AcceptedOrderRecord(
            std::string request_id, 
            OrderSide side_,
            int qty_, 
            std::optional<double> price_,
            OrderType type_,
            OrderStatus status_,
            std::string participant_code_
        ) : id(request_id),
        side(side_),
        qty(qty_),
        remaining_quantity(qty),
        price(price_), 
        type(type_), 
        status(status_),
        participant_code(participant_code_),
        created_at(time(NULL)) {}

        std::string generate_uid(std::string base_id) {
            /* TODO */
            std::string id = "TODO";

            return id;
        }
    };

    struct ExecutableOrder {
        const std::string id;
        const std::string order_record_id;
        const OrderSide side;
        int remaining_qty;
        const std::optional<double> price;
        OrderStatus status;

        ExecutableOrder(
            std::string order_record_id_, 
            OrderSide side_,
            int remaining_qty_, 
            std::optional<double> price_,
            OrderStatus status_
        ) : 
        id(generate_uid()),
        order_record_id(order_record_id_),
        side(side_),
        remaining_qty(remaining_qty_), 
        price(price_),
        status(status_) {}

        std::string generate_uid() {
            /* TODO */
            std::string id = "TODO";

            return id;
        }
    };

    struct LiveOrder {
        std::string id;
        std::string order_record_id;
        int remaining_qty;
        double price;
        OrderStatus status;

        LiveOrder(
            std::string order_record_id_,
            int remaining_qty_, 
            double price_,
            OrderStatus status_
        ) : 
        id(generate_uid()),
        order_record_id(order_record_id_),
        remaining_qty(remaining_qty_), 
        price(price_),
        status(status_) {}

        std::string generate_uid() {
            /* TODO */
            std::string id = "TODO";

            return id;
        }
    };

    struct Trade {
        std::string id;
        std::string bid_id;
        std::string ask_id;
        int qty;
        double price;
        time_t ts;

        Trade(
            std::string bid_id_,
            std::string ask_id_,
            int qty_,
            double price_
        ) : 
        id(generate_uid()),
        bid_id(bid_id_),
        ask_id(bid_id_),
        qty(qty_),
        price(price_),
        ts(time(NULL)) {}

        std::string generate_uid() {
            /* TODO */
            std::string id = "TODO";

            return id;
        }
    };
}