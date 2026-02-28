Architecture

Cache22 follows a layered architecture:

Client
   ↓
Network Layer (TCP + fork)
   ↓
Command Handling
   ↓
Storage Engine
   ↓
Tree Structure


Tree Structure

Each node contains:

Key

Pointers: north, east, west

Value (leaf)

Traversal is performed using linear search.
