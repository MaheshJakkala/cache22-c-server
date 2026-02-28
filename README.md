🚀 Cache22 – In-Memory Hierarchical Key-Value Server in C

Cache22 is a lightweight TCP-based in-memory key-value server implemented entirely in C. It supports hierarchical data organization using a custom tree structure and handles multiple client connections using process-based concurrency.

🧠 Core Features

Custom tree-based hierarchical storage

In-memory key-value structure

TCP socket-based client-server architecture

Fork-based concurrent client handling

Manual memory management

Modular system design

🏗 Architecture Overview

The system is divided into three main components:

1. Core (Tree Engine)

Implements:

Node creation

Leaf management

Linear lookup

Tree traversal

Location:

src/core/
2. Storage Layer

Handles:

High-level command interpretation

Tree operations

Data mutation logic

Location:

src/storage/
3. Network Layer

Responsible for:

TCP socket initialization

Accepting client connections

Fork-based process handling

Client request parsing

Location:

src/network/
🔁 Concurrency Model

Each client connection is handled using:

fork()

This isolates client sessions at the OS level and prevents memory corruption between clients.

🧪 Build Instructions
make
./cache22
🛠 Technologies Used

C (C11)

POSIX sockets

Unix process management

Manual memory management

GCC

⚙️ Design Decisions

In-memory storage for fast access

Linear lookup for simplicity

Fork-based isolation for concurrency

Hierarchical node navigation (north/east/west pointers)

🚧 Limitations

No persistence (data lost on restart)

Linear lookup (O(n))

No transaction support

No indexing structure

🔮 Future Improvements

Persistent storage (file-backed)

Hash-based indexing

Thread-based concurrency

Memory pooling

Benchmark suite
