#include <string>
#include <map>
#include <iostream>

#include "exchange_models.hpp"
#include "order_request.hpp"
#include "order_book.hpp"
#include "matching.hpp"
#include "exchange.hpp"

using namespace exchange_models;
using namespace order_request;

namespace exchange {

    bool Exchange::process_new_order_request(NewOrderRequest request) {
        bool is_valid = validate_order_request(request.qty, request.price);

        if (!is_valid) {
            request.status = REJECTED;
            return false;
        }

        request.status = ACCEPTED;
        AcceptedOrderRecord record = create_order_record(request);
        ExecutableOrder executable = engine_.execute_order(
            ExecutableOrder(
                record.id,
                record.side,
                record.qty,
                record.price,
                WORKING
            ),
            book_
        );

        if (executable.remaining_qty > 0) {
            book_.add_order(executable);
        }

        record.remaining_quantity = executable.remaining_qty;
        record.status = executable.status;

        return true;
    }

    bool Exchange::process_modify_order_request(ModifyOrderRequest request) {
        /* TODO */

        return true;
    }

    bool Exchange::process_cancel_order_request(CancelOrderRequest request) {
        /* TODO */
        
        return true;
    }

    void Exchange::print_book() {
        std::cout << book_.to_string() << std::endl;
    }

    bool Exchange::validate_order_request(int quantity, std::optional<double> price) {
        if (quantity <= 0) return false;

        return true;
    }

    AcceptedOrderRecord Exchange::create_order_record(NewOrderRequest request) {
        exchange_models::OrderSide side = (request.side == order_request::BID) ? exchange_models::BID : exchange_models::ASK;

        AcceptedOrderRecord record(
            request.id,
            side,
            request.qty,
            std::optional<double>{},
            OrderType::MARKET,
            OrderStatus::PENDING,
            request.participant_code
        );

        order_records_.emplace(record.id, record);

        return record;
    }
}