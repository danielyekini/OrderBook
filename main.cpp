#include <iostream>
#include <map>
#include <list>
#include <string>
#include "exchange_models.hpp"
#include "order_request.hpp"
#include "order_book.hpp"
#include "matching.hpp"
#include "exchange.hpp"

using namespace order_request;
using namespace exchange;

int main()
{
    std::string pt_code = "PT1";
    NewOrderRequest new_order = NewOrderRequest(pt_code, order_request::ASK, 20, 196.7);
    Exchange client = Exchange();
    
    client.process_new_order_request(new_order);

    client.print_book();

    return 0;
}
