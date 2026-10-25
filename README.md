# SQL Database Engine

**A custom SQL-like database engine developed in C++, featuring B+ Tree indexing, binary file storage, state-machine-based SQL parsing, and complex query evaluation using the Shunting Yard algorithm.**

## Overview

SQL Database Engine is a database management system developed from scratch in C++ that supports table creation, record insertion, and data retrieval through SQL-like commands without relying on an existing database engine.

The engine combines a custom database architecture with persistent binary file storage and a finite-state-machine parser for command interpretation. A vector of B+ Tree-backed multimaps provides efficient indexed lookups and range-based queries, while the Shunting Yard algorithm converts complex conditional expressions into postfix notation for subsequent evaluation.

## Key Features

- **SQL-Like Query Processing:** Supports table creation, record insertion, data retrieval, and conditional selection.
- **B+ Tree Indexing:** Uses custom B+ Tree-based maps and multimaps to organize field values and associated record references.
- **Persistent Binary Storage:** Stores table records in binary files for retrieval across program executions.
- **State-Machine-Based SQL Parser:** Tokenizes and parses commands using a finite-state machine.
- **Complex Query Evaluation:** Uses the Shunting Yard algorithm to process relational and logical expressions, including nested conditions.
- **Custom Data Structures:** Implements B+ Trees, maps, multimaps, stacks, queues, and linked-list utilities.
- **Error Handling:** Validates commands and reports invalid SQL syntax or table-related errors.
- **Interactive Console Interface:** Allows users to execute supported database commands and access usage instructions.

---

## Supported SQL Commands

The database engine supports table creation, record insertion, data retrieval, and conditional queries using SQL-like syntax.

| Command | Example | Description |
|---------|---------|-------------|
| `MAKE TABLE` | `make table student fields fname, lname, major, age` | Creates a table with specified fields |
| `INSERT INTO` | `insert into student values Jane, Doe, CS, 24` | Inserts a new record |
| `SELECT *` | `select * from student` | Retrieves all records and columns |
| `SELECT` | `select age, lname from student` | Retrieves specified columns |
| `SELECT WHERE` | `select * from student where age > 21` | Filters records using relational conditions |
| `SELECT WHERE` | `select * from student where (age > 20 and major = CS) or (age < 25 and major = Math)` | Filters records using compound logical and relational conditions |
| `GET FIELDS` | `get fields from student` | Displays a table's field names |

The engine also includes an interactive Help Desk, accessible by entering `?`, which provides command syntax, usage examples, and guidance on supported SQL operations.

## Showcase 
https://github.com/user-attachments/assets/8f2fcecc-c925-45d7-b983-759f36b3ed48

## Error-Checking Showcase
https://github.com/user-attachments/assets/38f8194d-862e-4927-8853-85971e665e71

## Help Desk Showcase
Picture of Help Desk (which you can get by entering '?')
![Alt text](image-2.png)
A Guide to all the Commands (which you can get by entering 'A')
![Alt text](image-3.png) 

## System Architecture

The database engine is organized into five primary components responsible for command processing, parsing, indexing, persistent storage, and query evaluation.

### 1. <ins>SQL Command Processing</ins>

The `SQL` class serves as the primary interface between user commands and database operations.

It receives SQL-like statements, invokes the parser, and dispatches valid commands to the appropriate `Table` operations.

This separates command interpretation and execution coordination from the underlying data storage and indexing logic.

### 2. <ins>Finite-State-Machine Parsing</ins>

The `Parser` class uses a finite-state machine to recognize supported SQL-like command structures.

Input statements are tokenized and processed through a state-transition table to identify command keywords, table names, field names, values, and conditional expressions.

The resulting parse tree organizes these components for execution by the database engine.

### 3. <ins>B+ Tree Indexing</ins>

Each table maintains a vector of B+ Tree-backed multimaps, with each multimap indexing a separate column.

Field values (CS, Math, etc.) are associated with lists of record numbers, allowing multiple records to share the same indexed value.

For example, a `major` column might be indexed as follows:

```text
Major Index (B+ Tree-backed multimap)

"CS"    -> [0, 2, 4]
"Math"  -> [1, 5]
"Physics" -> [3]
```
<sup>record numbers 0, 2, 4 share the same indexed value "CS"</sup>

A vector of B+ Tree-backed multimaps was chosen to organize column indexes in a contiguous, dynamically sized structure, allowing each column's index to be accessed directly by its position. A separate field-name map associates field names with vector indices, enabling efficient retrieval of the appropriate multimap during query execution. B+ Trees maintain sorted keys for efficient equality lookups and range-based queries, while multimaps support duplicate field values by mapping each key to multiple record numbers. This design simplifies index management and allows indexes to be updated systematically during record insertion.

### 4. <ins>Persistent Binary File Storage</ins>

Table records are stored in binary files using the `FileRecord` class.

When a record is inserted, the engine writes its contents to persistent storage and updates each column's multimap with the corresponding record number.

When an existing table is loaded, the engine reads its stored records and reconstructs the in-memory indexes.

This design separates persistent record storage from indexed data retrieval.

### 5. <ins>Conditional Query Evaluation</ins>

The engine processes conditional expressions using the Shunting Yard algorithm and stack-based postfix evaluation.

The Shunting Yard algorithm converts infix expressions into Reverse Polish Notation (RPN), accounting for operator precedence and parentheses.

During evaluation:

1. Relational operators (`=`, `<`, `>`, `<=`, `>=`) retrieve matching record numbers from the appropriate column indexes.
2. The `and` operator computes the intersection of matching record sets.
3. The `or` operator combines matching record sets through union.
4. The resulting record numbers identify the rows to retrieve from binary storage.

This allows the engine to evaluate compound conditions while keeping parsing, indexing, and record retrieval as separate operations.

---

## Core Components

The engine is implemented using reusable C++ classes and custom data structures.

| Component | Responsibility |
|-----------|----------------|
| `SQL` | Processes commands and coordinates database operations |
| `Parser` | Interprets SQL-like statements using a finite-state machine |
| `Table` | Manages table records, column indexes, insertion, and selection |
| `BPlusTree` | Implements the underlying ordered tree structure |
| `Map` | Maps individual keys to associated values |
| `MMap` | Maps field values to lists of corresponding record numbers |
| `ShuntingYard` | Converts conditional expressions from infix to postfix notation |
| `FileRecord` | Handles binary record storage and retrieval |
| `Stack` / `Queue` | Support expression conversion and evaluation |
| `Interaction` | Provides the command-line interface and interactive Help Desk |

---

## Development Challenges

One architectural challenge was deciding whether command validation should be handled by the Interaction class or the SQL class. Initially, I considered validating commands in Interaction before passing them to SQL, but this approach would require parsing each command twice: once for validation and again for execution.

I ultimately centralized command validation within the SQL class, eliminating redundant parsing and allowing the command-line interface to focus on user interaction. This design improved separation of concerns and ensured that the database engine could independently validate incoming commands.

---

## Testing

The project includes test programs for validating SQL command processing, data structure behavior, and database operations.

Key test scenarios include:

- Table creation and record insertion
- Selection of all records or specific columns
- Equality and range-based comparisons
- Compound `and` / `or` expressions
- Parenthesized conditional expressions
- Command parsing and invalid-input handling
- Record retrieval and indexed query execution

---

## Project Information

**Developer:** Queency Tan  
**Language:** C++  
**Interface:** Command-line application  
**Project Type:** Database Management System
