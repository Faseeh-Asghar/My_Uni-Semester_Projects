# Smart Campus Access and Analytics System

This project is a C++ console application for a smart campus scenario. It combines:

- Role-based access control (RBAC) with time-based rules
- Access logging and analytics
- Graph algorithms for campus navigation and structure analysis

It was built as a Discrete Structures semester project and demonstrates practical use of graph theory, rule evaluation, and file-based data management.

## What This Project Is About

The system models a campus with users, doors, and policies.

- A user tries to access a door at a specific hour.
- The policy engine checks matching rules by role, door type, access level, and time period.
- The system grants or denies access and logs the result.
- In parallel, the campus is represented as a weighted graph, enabling shortest path, MST, BFS/DFS traversal, and Euler/Hamilton checks.

In short: this is an **access control simulator + graph analytics toolkit** for a campus environment.

## Learning Goals (Discrete Structures Concepts)

This project demonstrates:

- Graph representation with adjacency lists
- Weighted shortest path (Dijkstra)
- Minimum spanning tree (Kruskal)
- Graph traversals (BFS, DFS)
- Eulerian path existence conditions
- Hamiltonian path search (backtracking)
- Rule-based decision systems with priority/conflict resolution

## Core Modules

- `User` (`User.h`, `User.cpp`): stores user identity, role, and credentials
- `Door` (`Door.h`, `Door.cpp`): stores door location, type, and required access level
- `AccessRule` (`AccessRule.h`, `AccessRule.cpp`): policy rule model
- `PolicyEngine` (`PolicyEngine.h`, `PolicyEngine.cpp`): evaluates rules and returns grant/deny decisions
- `AccessLog` (`AccessLog.h`, `AccessLog.cpp`): records each access attempt and provides filters/statistics
- `CampusGraph` (`CampusGraph.h`, `CampusGraph.cpp`): graph algorithms for campus map analysis
- `FileManager` (`FileManager.h`, `FileManager.cpp`): loads/saves users and doors from text files
- `CampusSystem` (`CampusSystem.h`, `CampusSystem.cpp`): orchestrates all components
- `main.cpp`: menu-driven user interface

## Project Structure

Important files:

- `main.cpp`
- `CampusSystem.*`
- `CampusGraph.*`
- `PolicyEngine.*`
- `AccessRule.*`
- `AccessLog.*`
- `FileManager.*`
- `User.*`
- `Door.*`
- Data files: `users.txt`, `doors.txt`, `access_rules.txt`, `accesslog.txt`

## Data Files and Formats

### `users.txt`
Pipe-separated format:

```text
ID|Name|Role|Password
25F-1234|Ali Hamza|student|3456234789
```

### `doors.txt`
Pipe-separated format:

```text
DoorID|Location|AccessLevel|Type
D001|CS Building Room 101|2|classroom
```

### `access_rules.txt`
Pipe-separated format:

```text
RuleID|Name|Description|TargetRole|TargetDoorType|MinAccessLevel|TimePeriod|StartHour|EndHour|DenyFlag|Priority
R001|Guard Access|...|guard||-1|0|0|23|0|100
```

### `accesslog.txt`
Stores logged access attempts (generated/updated by the system).

## Menu Features

The console menu includes:

1. Test Access (evaluate grant/deny for user + door + hour)
2. View Users
3. View Doors
4. View Logs (recent/failed/success filters)
5. View Campus Map
6. Find Shortest Path (Dijkstra)
7. Compute MST (Kruskal)
8. BFS/DFS Traversal
9. Check Euler Path
10. Check Hamilton Path
11. Show Access Statistics
12. Run Demo Scenarios

## How Access Decisions Work

When an access request is tested, the policy engine:

1. Finds all rules matching current context (role, door type, level, time).
2. Selects the highest-priority applicable rule.
3. Resolves ties so DENY can override ALLOW at equal priority.
4. Returns final decision with reason and applied rule.
5. Saves the attempt to access log.

## Build and Run

## Option A: Visual Studio (Recommended)

1. Open `Discrete final smester project.slnx` in Visual Studio.
2. Select `Debug` and `x64` (or your preferred configuration).
3. Build and run.

## Option B: g++ (if all sources are compiled together)

Example command:

```bash
g++ -std=c++17 -O2 *.cpp -o campus_system
./campus_system
```

Note: Ensure `users.txt`, `doors.txt`, and `access_rules.txt` are in the same working directory as the executable.

## Example Demo Scenarios

The built-in demo runs sample checks such as:

- Student accessing classroom during allowed hours (usually granted)
- Student accessing lab at night (typically denied)
- Teacher accessing lab (usually granted)
- Guard accessing high-security door (typically granted)

## Current Limitations

- Campus graph is loaded by default code (not currently read from `campus_map.txt`).
- Password field exists in user data, but authentication is not a full login flow.
- Hamiltonian path check is backtracking-based and can become expensive on very large graphs.

## Future Improvements

- Load graph edges dynamically from file
- Add full authentication and hashed passwords
- Add admin menu to create/edit users, doors, and rules
- Export reports for denied access patterns
- Improve Hamiltonian analysis heuristics for larger graphs

## Authors / Course Context

Semester project for Discrete Structures, focused on applying theoretical graph and logic concepts to a realistic campus security use case.
