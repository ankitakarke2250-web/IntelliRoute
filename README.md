# Smart Packet Routing Using Graph Algorithms

> A Data Structures & Algorithms mini-project that models a computer network as a graph and simulates smart, adaptive packet routing using classical graph algorithms.

**Status:** 🔜 Approval Pending

---


## 📌 Overview

Modern networks route data packets across multiple nodes (routers/switches) to reach a destination efficiently. This project simulates such a network as a **weighted graph**, where:

- **Nodes** represent routers/devices
- **Edges** represent network links
- **Edge weights** represent cost metrics such as latency, bandwidth, or distance

The goal is to find the **most efficient path** for a packet to travel from a source node to a destination node, while also handling dynamic scenarios like link failures or congestion — mimicking how real-world routing protocols (e.g., OSPF, RIP) behave.

---

## 🎯 Objectives

- Model a computer network as a graph data structure
- Implement and compare multiple shortest-path/routing algorithms
- Simulate dynamic network conditions (node/link failure, congestion, weight changes)
- Visualize the network and the chosen routing path
- Analyze time complexity and performance trade-offs between algorithms

---

## 🧠 Core Concepts & Algorithms Used

| Concept | Purpose |
|---|---|
| **Graph (Adjacency List/Matrix)** | Represent the network topology |
| **Dijkstra's Algorithm** | Shortest path routing (single source) |
| **Bellman-Ford Algorithm** | Shortest path with support for negative weights / failure detection |
| **Floyd-Warshall Algorithm** | All-pairs shortest path for global routing tables |
| **BFS/DFS** | Network reachability and connectivity checks |
| **Priority Queue (Min-Heap)** | Efficient implementation of Dijkstra's algorithm |
| **A\* Search (optional/extension)** | Heuristic-based faster pathfinding |

---

## 🏗️ Project Architecture

```
smart-packet-routing/
│
├── src/
│   ├── graph.h / graph.cpp         # Graph data structure (adjacency list/matrix)
│   ├── dijkstra.h / dijkstra.cpp   # Dijkstra's algorithm implementation
│   ├── bellman_ford.h / .cpp       # Bellman-Ford implementation
│   ├── floyd_warshall.h / .cpp     # Floyd-Warshall implementation
│   ├── simulator.h / .cpp          # Network simulation logic (failures, congestion)
│   └── main.cpp                    # Entry point / menu-driven interface
│
├── data/
│   └── sample_network.txt          # Sample network topology (edge list / adjacency data)
│
├── tests/
│   └── test_routing.cpp            # Unit tests for algorithms
│
├── docs/
│   └── design_document.md          # Detailed design & complexity analysis
│
├── Makefile / CMakeLists.txt       # Build configuration
├── README.md
└── .gitignore
```

*(Use `.c`/`.h` files instead if implementing in pure C rather than C++.)*

---

## ⚙️ How It Works

1. **Network Modeling** – The network topology is loaded/created as a weighted graph.
2. **Path Computation** – On a routing request (source → destination), the selected algorithm computes the optimal path.
3. **Dynamic Simulation** – The system can simulate a link/node failure or congestion, triggering re-computation of the route.
4. **Visualization** – The network graph and computed path are printed to console (or exported to Graphviz for a rendered image).
5. **Comparison Mode** – Runs multiple algorithms on the same network to compare path cost and execution time.

---

## 🚀 Features

- ✅ Build custom or randomly generated network topologies
- ✅ Compute shortest path using multiple algorithms
- ✅ Simulate real-time link failure and automatic re-routing
- ✅ Compare algorithm performance (time complexity, path cost)
- ✅ Console-based visualization of the network graph and chosen path (adjacency list / ASCII path trace)
- 🔜 (Optional) Export graph to Graphviz (`.dot`) for a rendered image, or build a simple GUI with SFML/Qt

---

## 🛠️ Tech Stack

- **Language:** C / C++
- **Libraries:** Standard Template Library (STL) — `vector`, `priority_queue`, `queue`, `map` for graph and algorithm implementation
- **Build Tools:** GCC/G++, Make (or CMake)
- **Tools:** Git, GitHub

---

## 📥 Installation & Setup

```bash
# Clone the repository
git clone https://github.com/ankitakarke2250-web/IntelliRoute.git
cd IntelliRoute

# Compile (simple g++ example — adjust file names as your project grows)
g++ -o router src/main.cpp src/graph.cpp src/dijkstra.cpp src/bellman_ford.cpp -std=c++17

# Run the simulator
./router
```

> If you set up a `Makefile`, this simplifies to `make && ./router`.

---

## 📊 Sample Output

```
Enter source node: A
Enter destination node: E

Running Dijkstra's Algorithm...
Shortest Path: A -> C -> D -> E
Total Cost: 12

Simulating link failure: C -> D
Re-routing...
New Path: A -> C -> B -> D -> E
Total Cost: 15
```

---

## 📈 Complexity Analysis

| Algorithm | Time Complexity | Space Complexity | Use Case |
|---|---|---|---|
| Dijkstra (with Min-Heap) | O((V + E) log V) | O(V) | Single-source shortest path, non-negative weights |
| Bellman-Ford | O(V·E) | O(V) | Handles negative weights, detects cycles |
| Floyd-Warshall | O(V³) | O(V²) | All-pairs shortest path, static small networks |

---

## 🔮 Future Enhancements

- Machine learning-based traffic prediction for smarter routing
- Real-time visualization dashboard (web-based)
- Support for weighted multi-metric routing (latency + bandwidth + reliability)
- Integration with real network simulators (e.g., Mininet)

---

## 👤 Author

**Project Type:** DSA Mini Project
**Topic:** Smart Packet Routing Using Graph Algorithms
**Status:** Approval Pending

---

## 📄 License

This project is open-sourced under the [MIT License](LICENSE).