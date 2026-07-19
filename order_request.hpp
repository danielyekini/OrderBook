#pragma once

#include <string>
#include <ctime>
#include <optional>

namespace order_request {

    inline int GlobalOrderSequence = 0;

    enum RequestStatus { PENDING, ACCEPTED, REJECTED };

    enum OrderSide { BID, ASK };

    struct OrderRequest {};

    struct NewOrderRequest : OrderRequest {
        const std::string id;
        const OrderSide side;
        const int qty;
        const std::optional<double> price;
        const std::string participant_code;
        const time_t timestamp;
        RequestStatus status;

        NewOrderRequest(std::string participant_code_, OrderSide order_side_, int quantity_) :
            participant_code(participant_code_),
            side(order_side_), 
            id(generate_uid()), 
            qty(quantity_),
            price(std::nullopt),
            timestamp(time(NULL)),
            status(PENDING) {}
        
        NewOrderRequest(std::string participant_code_, OrderSide order_side_, int quantity_, double price_) :
            participant_code(participant_code_),
            side(order_side_), 
            id(generate_uid()), 
            qty(quantity_),
            price(std::optional<double>{price_}),
            timestamp(time(NULL)),
            status(PENDING) {}

        std::string generate_uid() {
            std::string side_code = (side == BID) ? "BID" : "ASK";
            return participant_code + "_" + "LM" + side_code + "_" + std::to_string(++GlobalOrderSequence);
        } 
    };

    struct ModifyOrderRequest : OrderRequest {
        const std::string id;
        const std::string order_id;
        const int qty;
        const std::string participant_code;
        const time_t ts;
        RequestStatus status;

        ModifyOrderRequest(std::string participant_code_, OrderSide order_id_, int quantity_) :
            participant_code(participant_code_), 
            id(generate_uid()), 
            order_id(order_id),
            qty(quantity_),
            ts(time(NULL)),
            status(PENDING) {}

        std::string generate_uid() {
            return participant_code + "_" + "LM" + "_" + std::to_string(++GlobalOrderSequence);
        } 
    };

    struct CancelOrderRequest {
        const std::string id;
        const std::string order_id;
        const std::string participant_code;
        const time_t ts;
        RequestStatus status;

        CancelOrderRequest(std::string participant_code_, std::string order_id_) : 
            participant_code(participant_code_),
            id(generate_uid()),
            order_id(order_id_),
            ts(time(NULL)),
            status(PENDING) {}

        std::string generate_uid() {}
    };
};

// struct LimitOrderRequest : OrderRequest {
//         const std::string id;
//         const OrderSide side;
//         const int qty;
//         const double price;
//         const std::string participant_code;
//         const time_t ts;
//         RequestStatus status;

//         LimitOrderRequest(std::string participant_code_, OrderSide order_side_, int quantity_, double price_) :
//             participant_code(participant_code_),
//             side(order_side_),  
//             id(generate_uid()), 
//             qty(quantity_), 
//             price(price_),
//             ts(time(NULL)),
//             status(PENDING) {}

//         std::string generate_uid() {
//             std::string side_code = (side == BID) ? "BID" : "ASK";
//             return participant_code + "_" + "LM" + side_code + "_" + std::to_string(++GlobalOrderSequence);
//         } 
//     };

    //     OrderMetadata(OrderSide side_, int qty_, std::string code_)
    //         : side(side_), participant_code(code_) {
    //             if (qty_ <= 0) throw std::invalid_argument("Quantity must be greater than 0");

    //             qty = qty_;
    //             ts = time(NULL);
    //             status = pending;
    //         }

        
        
    //     OrderSide get_side() { return side; }

    //     int get_quantity() { return qty; }

    //     time_t get_timestamp() { return ts; }

    //     std::string get_participant_code() { return participant_code; }
        
    //     OrderStatus get_status() { return status; }

    //     void update_status(OrderStatus new_status) { status = new_status; }

    // private:
    //     OrderSide side;
    //     int qty;
    //     time_t ts;
    //     std::string participant_code;
    //     OrderStatus status;
    // };

    // struct MarketOrder {
    //     int remaining_qty;

    //     MarketOrder(std::string participant_code_, OrderSide order_side_, int quantity_) 
    //         : metadata(order_side_, quantity_, participant_code_) {
    //             std::string side_code = (order_side_ == bid) ? "BID_" : "ASK_";
    //             std::string id_ = participant_code_ + "_" + "MK" + side_code + "_" + std::to_string(++GlobalOrderSequence);

    //             id = id_;
    //             remaining_qty = quantity_;
    //         }

    //     std::string get_id() { return id; }
        
    //     OrderSide side() { return metadata.get_side(); }

    //     int quantity() { return metadata.get_quantity(); }

    //     time_t timestamp() { return metadata.get_timestamp(); }

    //     std::string participant_code() { return metadata.get_participant_code(); }
        
    //     OrderStatus status() { return metadata.get_status(); }

    //     void update_status(OrderStatus new_status) { metadata.update_status(new_status); }

    //     OrderMetadata get_metadata() { return metadata; }

    // private:
    //     std::string id;
    //     OrderMetadata metadata;
    // };

    // struct LimitOrder {
    //     int remaining_qty;
    //     double price;

    //     LimitOrder(std::string participant_code_, OrderSide order_side_, int quantity_, double price_) 
    //         : price(price_), metadata(order_side_, quantity_, participant_code_) {
    //             std::string side_code = (order_side_ == bid) ? "BID_" : "ASK_";
    //             std::string id_ = participant_code_ + "_" + "LM" + side_code + "_" + std::to_string(++GlobalOrderSequence);

    //             id = id_;
    //             remaining_qty = quantity_;
    //         }

    //     std::string get_id() { return id; }
        
    //     OrderSide side() { return metadata.get_side(); }

    //     int quantity() { return metadata.get_quantity(); }

    //     time_t timestamp() { return metadata.get_timestamp(); }

    //     std::string participant_code() { return metadata.get_participant_code(); }
        
    //     OrderStatus status() { return metadata.get_status(); }

    //     void update_status(OrderStatus new_status) { metadata.update_status(new_status); }

    //     OrderMetadata get_metadata() { return metadata; }

    // private:
    //     std::string id;
    //     OrderMetadata metadata;

    // };