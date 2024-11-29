
# Wireless Power Trees

## Overview
This project implements a system for managing wireless power customer data using advanced binary tree structures, including Binary Search Trees (BST), AVL Trees, and Splay Trees. The system enables efficient insertion, removal, and search operations, supporting different tree types based on user needs.

## Features

### Core Functionality
1. **Customer Management**:
   - Insert customer data (ID, latitude, longitude) into the selected tree structure.
   - Remove customers by ID (applicable to BST and AVL Trees).
   - Convert existing trees to AVL Tree format dynamically.

2. **Tree Structures**:
   - **Binary Search Tree (BST)**: Maintains data based on binary search property.
   - **AVL Tree**: Self-balancing binary tree ensuring height balance.
   - **Splay Tree**: Self-adjusting binary tree that performs splaying to move recently accessed elements closer to the root.

3. **Visualization**:
   - Debugging utility to print tree structures.

4. **Dynamic Operations**:
   - Rotate nodes (left or right) to maintain balance in AVL Trees.
   - Splay nodes to the root in Splay Trees.

### Testing Framework
The `Tester` class validates various functionalities, including:
- AVL Tree balancing after insertions and removals.
- BST properties after modifications.
- Splay Tree height after operations.
- Assignment operator correctness for copying trees.

## Files

### Source Files
1. **`wpower.cpp` & `wpower.h`**:
   - Implements the `WirelessPower` class and its operations for managing trees.
   - Includes helper functions for tree balancing, splaying, rotation, and traversal.

2. **`mytest.cpp`**:
   - Contains the `Tester` class to validate tree properties and operations.

### Key Classes

#### `WirelessPower` Class
- **Attributes**:
  - `Customer* m_root`: Root node of the tree.
  - `TREETYPE m_type`: Type of tree (BST, AVL, SPLAY).
- **Core Methods**:
  - `insert`: Adds a customer to the tree.
  - `remove`: Deletes a customer by ID (not applicable for Splay Trees).
  - `setType`: Converts the tree to AVL format.
  - `dumpTree`: Displays the tree structure.

#### `Customer` Class
- **Attributes**:
  - `int m_id`: Customer ID.
  - `double m_latitude`: Customer latitude.
  - `double m_longitude`: Customer longitude.
- **Core Methods**:
  - Accessor and mutator functions for ID, latitude, longitude, height, and children.
  - Overloaded insertion operator (`<<`) for displaying customer details.

#### `Tester` Class
- Provides test cases for:
  - Tree balancing after insertions and removals.
  - Correctness of splay operations.
  - Verification of AVL and BST properties.
  - Copy constructor and assignment operator functionality.

## Installation and Execution

1. Compile the program:
   ```bash
   g++ -o wireless_power mytest.cpp wpower.cpp
   ```
2. Run the program:
   ```bash
   ./wireless_power
   ```

## Example Usage

### Insert Customers
```cpp
WirelessPower tree(AVL);
tree.insert(Customer(101, 39.29, -76.61)); // Insert customer with ID 101
tree.insert(Customer(102, 34.05, -118.24));
tree.dumpTree();
```

### Remove Customers
```cpp
tree.remove(101); // Remove customer with ID 101
tree.dumpTree();
```

### Convert Tree Type
```cpp
tree.setType(AVL); // Convert existing tree to AVL format
tree.dumpTree();
```

### Test Framework
```cpp
Tester tester;
tester.testAVLTreeBalanceAfterInsertions(300);
tester.testBSTPropertyAfterInsertions(tree);
```

## Dependencies
- **Standard C++ Libraries**:
  - `<iostream>`
  - `<cmath>`
  - `<algorithm>`
  - `<vector>`
  - `<random>`

## License
This project is for educational purposes and does not include warranties or guarantees.
