# University Library gRPC System

A gRPC-based university library management system developed in C++ using Protocol Buffers.

## Overview

This project implements a complete gRPC service for managing a university library system with three main entities:
- **Books**: Manage book inventory
- **Students**: Manage student records  
- **Loans**: Handle book borrowing and returning

## Features

### Book Service
- List all books
- Get book by ID
- Create new book
- Update existing book
- Delete book

### Student Service
- List all students
- Get student by ID
- Create new student
- Update existing student
- Delete student

### Loan Service
- List all loans (with optional filtering by student)
- Get loan by ID
- Borrow book (creates new loan)
- Return book (updates loan status)

## Architecture

The system uses Protocol Buffers (protobuf) for service definition and gRPC for communication:

- `university.proto`: Defines all services, messages, and data structures
- **Server**: Implements all three services with in-memory mock data
- **Client**: Demonstrates usage of all service methods
- **grpcurl**: Command-line testing of all endpoints

## Requirements

- C++17 or later
- CMake 3.15+
- gRPC and Protocol Buffers libraries
- grpcurl (for testing)

### Installing Dependencies (Ubuntu/Debian)

```bash
# Install build tools
sudo apt update
sudo apt install -y build-essential cmake pkg-config

# Install gRPC and protobuf
sudo apt install -y libgrpc++-dev libprotobuf-dev protobuf-compiler-grpc

# Install grpcurl for testing
sudo apt install -y grpcurl
```

## Building the Project

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make -j$(nproc)
```

This will generate:
- `server`: The gRPC server executable
- `client`: The test client executable
- Proto-generated files in `build/proto/` directory

## Running the System

### 1. Start the Server

```bash
# From build directory
./server
```

The server will start on `localhost:50051` and display:
```
University Library gRPC Server listening on 0.0.0.0:50051
```

### 2. Run the Test Client

In another terminal:

```bash
# From build directory  
./client
```

This will demonstrate various operations and show output like:
```
=== Books List ===
ID: book-001
Title: Clean Code
Author: Robert C. Martin
...
```

### 3. Test with grpcurl

You can also test individual methods using grpcurl:

```bash
# List all books
grpcurl -plaintext localhost:50051 university.BookService/ListBooks

# Get specific book
grpcurl -plaintext -d '{"id": "book-001"}' localhost:50051 university.BookService/GetBook

# Create new book
grpcurl -plaintext -d '{
  "book": {
    "title": "New Book",
    "author": "Author Name", 
    "isbn": "978-1234567890",
    "publisher": "Publisher",
    "page_count": 300,
    "stock": 5
  }
}' localhost:50051 university.BookService/CreateBook
```

## API Documentation

For detailed API documentation and testing examples, see [grpcurl-tests.md](grpcurl-tests.md).

