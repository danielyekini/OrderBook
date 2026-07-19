# OrderBook Trading Suite

A compact C++ order-book / matching engine playground. Designed to demonstrate an exchange-style matching flow, order handling, and an in-memory order book for experiments and learning.

## Features
- Simple limit order book and matching engine
- Example exchange client and request types
- Small, single-directory C++ project for quick builds

## Quick build
On systems with `g++` (MinGW / MSYS2 / WSL / Linux/macOS):

```bash
g++ -std=c++17 -O2 main.cpp Exchange.cpp MatchingEngine.cpp OrderBook.cpp ExchangeClient.cpp -o orderbook
```

On Windows with MSVC (Developer Command Prompt):

```powershell
cl /EHsc /std:c++17 main.cpp Exchange.cpp MatchingEngine.cpp OrderBook.cpp ExchangeClient.cpp /Fe:orderbook.exe
```

## Run
- After building with `g++`:

```bash
./orderbook
```

- On Windows (MSVC build):

```powershell
.\orderbook.exe
```

## Project structure
- `main.cpp` — simple runner / entry point
- `Exchange.cpp` / `exchange.hpp` — exchange-level orchestration
- `ExchangeClient.cpp` — example client code
- `MatchingEngine.cpp` / `matching.hpp` — matching logic
- `OrderBook.cpp` / `order_book.hpp` — order book implementation
- `order_request.hpp` — order request types
- `exchange_models.hpp` — shared data models

## Notes
- No external dependencies required — single-step compile shown above.
- If you prefer a CMake workflow, I can add a minimal `CMakeLists.txt`.

## Contributing
- Open issues or send PRs for fixes, tests, or feature improvements.

## License
This repository does not include an explicit license. Add a `LICENSE` file if you want to set terms.
