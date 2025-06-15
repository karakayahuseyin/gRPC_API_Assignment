# grpcurl Test Documentation

This document contains detailed testing procedures and results for all gRPC services using `grpcurl`.

## Prerequisites

1. Server must be running on `localhost:50051`
2. grpcurl must be installed
3. Server has reflection enabled

## Book Service Tests

### 1. List All Books

**Command:**
```bash
grpcurl -plaintext localhost:50051 university.BookService/ListBooks
```

**Expected Response:**
```json
{
  "books": [
    {
      "id": "book-001",
      "title": "Clean Code",
      "author": "Robert C. Martin",
      "isbn": "978-0132350884",
      "publisher": "Prentice Hall",
      "pageCount": 464,
      "stock": 5
    },
    {
      "id": "book-002", 
      "title": "Design Patterns",
      "author": "Gang of Four",
      "isbn": "978-0201633610",
      "publisher": "Addison-Wesley",
      "pageCount": 395,
      "stock": 3
    }
  ]
}
```

### 2. Get Specific Book

**Command:**
```bash
grpcurl -plaintext -d '{"id": "book-001"}' localhost:50051 university.BookService/GetBook
```

**Expected Response:**
```json
{
  "book": {
    "id": "book-001",
    "title": "Clean Code", 
    "author": "Robert C. Martin",
    "isbn": "978-0132350884",
    "publisher": "Prentice Hall",
    "pageCount": 464,
    "stock": 5
  }
}
```

### 3. Get Non-existent Book (Error Case)

**Command:**
```bash
grpcurl -plaintext -d '{"id": "book-999"}' localhost:50051 university.BookService/GetBook
```

**Expected Response:**
```
ERROR:
  Code: NotFound
  Message: Book not found
```

### 4. Create New Book

**Command:**
```bash
grpcurl -plaintext -d '{
  "book": {
    "title": "The Pragmatic Programmer",
    "author": "David Thomas, Andrew Hunt", 
    "isbn": "978-0201616224",
    "publisher": "Addison-Wesley",
    "pageCount": 352,
    "stock": 10
  }
}' localhost:50051 university.BookService/CreateBook
```

**Expected Response:**
```json
{
  "book": {
    "id": "book-3",
    "title": "The Pragmatic Programmer",
    "author": "David Thomas, Andrew Hunt",
    "isbn": "978-0201616224", 
    "publisher": "Addison-Wesley",
    "pageCount": 352,
    "stock": 10
  }
}
```

### 5. Update Book

**Command:**
```bash
grpcurl -plaintext -d '{
  "book": {
    "id": "book-001",
    "title": "Clean Code - Updated",
    "author": "Robert C. Martin",
    "isbn": "978-0132350884",
    "publisher": "Prentice Hall",
    "pageCount": 464,
    "stock": 8
  }
}' localhost:50051 university.BookService/UpdateBook
```

**Expected Response:**
```json
{
  "book": {
    "id": "book-001",
    "title": "Clean Code - Updated",
    "author": "Robert C. Martin", 
    "isbn": "978-0132350884",
    "publisher": "Prentice Hall",
    "pageCount": 464,
    "stock": 8
  }
}
```

### 6. Delete Book

**Command:**
```bash
grpcurl -plaintext -d '{"id": "book-002"}' localhost:50051 university.BookService/DeleteBook
```

**Expected Response:**
```json
{
  "success": true,
  "message": "Book deleted successfully"
}
```

## Student Service Tests

### 1. List All Students

**Command:**
```bash
grpcurl -plaintext localhost:50051 university.StudentService/ListStudents
```

**Expected Response:**
```json
{
  "students": [
    {
      "id": "student-001",
      "name": "Ali Veli",
      "studentNumber": "20190001", 
      "email": "ali.veli@university.edu",
      "isActive": true
    },
    {
      "id": "student-002",
      "name": "Ayşe Yılmaz",
      "studentNumber": "20190002",
      "email": "ayse.yilmaz@university.edu", 
      "isActive": true
    }
  ]
}
```

### 2. Get Specific Student

**Command:**
```bash
grpcurl -plaintext -d '{"id": "student-001"}' localhost:50051 university.StudentService/GetStudent
```

**Expected Response:**
```json
{
  "student": {
    "id": "student-001",
    "name": "Ali Veli",
    "studentNumber": "20190001",
    "email": "ali.veli@university.edu",
    "isActive": true
  }
}
```

### 3. Create New Student

**Command:**
```bash
grpcurl -plaintext -d '{
  "student": {
    "name": "Mehmet Demir",
    "studentNumber": "20210003",
    "email": "mehmet.demir@university.edu",
    "isActive": true
  }
}' localhost:50051 university.StudentService/CreateStudent
```

**Expected Response:**
```json
{
  "student": {
    "id": "student-3",
    "name": "Mehmet Demir", 
    "studentNumber": "20210003",
    "email": "mehmet.demir@university.edu",
    "isActive": true
  }
}
```

### 4. Update Student

**Command:**
```bash
grpcurl -plaintext -d '{
  "student": {
    "id": "student-001",
    "name": "Ali Veli Updated",
    "studentNumber": "20190001",
    "email": "ali.veli.new@university.edu",
    "isActive": true
  }
}' localhost:50051 university.StudentService/UpdateStudent
```

**Expected Response:**
```json
{
  "student": {
    "id": "student-001",
    "name": "Ali Veli Updated",
    "studentNumber": "20190001", 
    "email": "ali.veli.new@university.edu",
    "isActive": true
  }
}
```

### 5. Delete Student

**Command:**
```bash
grpcurl -plaintext -d '{"id": "student-002"}' localhost:50051 university.StudentService/DeleteStudent
```

**Expected Response:**
```json
{
  "success": true,
  "message": "Student deleted successfully"
}
```

## Loan Service Tests

### 1. List All Loans

**Command:**
```bash
grpcurl -plaintext localhost:50051 university.LoanService/ListLoans
```

**Expected Response:**
```json
{
  "loans": [
    {
      "id": "loan-001",
      "studentId": "student-001", 
      "bookId": "book-001",
      "loanDate": "2024-01-15",
      "returnDate": "",
      "status": "ONGOING"
    }
  ]
}
```

### 2. Get Specific Loan

**Command:**
```bash
grpcurl -plaintext -d '{"id": "loan-001"}' localhost:50051 university.LoanService/GetLoan
```

**Expected Response:**
```json
{
  "loan": {
    "id": "loan-001",
    "studentId": "student-001",
    "bookId": "book-001", 
    "loanDate": "2024-01-15",
    "returnDate": "",
    "status": "ONGOING"
  }
}
```

### 3. Borrow Book

**Command:**
```bash
grpcurl -plaintext -d '{
  "studentId": "student-002",
  "bookId": "book-002"
}' localhost:50051 university.LoanService/BorrowBook
```

**Expected Response:**
```json
{
  "loan": {
    "id": "loan-2",
    "studentId": "student-002",
    "bookId": "book-002",
    "loanDate": "2024-06-15",
    "returnDate": "",
    "status": "ONGOING"
  }
}
```

### 4. Borrow Non-existent Book (Error Case)

**Command:**
```bash
grpcurl -plaintext -d '{
  "studentId": "student-001", 
  "bookId": "book-999"
}' localhost:50051 university.LoanService/BorrowBook
```

**Expected Response:**
```
ERROR:
  Code: NotFound
  Message: Book not found
```

### 5. Return Book

**Command:**
```bash
grpcurl -plaintext -d '{"loanId": "loan-001"}' localhost:50051 university.LoanService/ReturnBook
```

**Expected Response:**
```json
{
  "loan": {
    "id": "loan-001",
    "studentId": "student-001",
    "bookId": "book-001",
    "loanDate": "2024-01-15", 
    "returnDate": "2024-06-15",
    "status": "RETURNED"
  }
}
```

### 6. Return Already Returned Book (Error Case)

**Command:**
```bash
grpcurl -plaintext -d '{"loanId": "loan-001"}' localhost:50051 university.LoanService/ReturnBook
```

**Expected Response:**
```
ERROR:
  Code: FailedPrecondition
  Message: Book already returned
```

### 7. List Loans with Student Filter

**Command:**
```bash
grpcurl -plaintext -d '{"studentId": "student-001"}' localhost:50051 university.LoanService/ListLoans
```

**Expected Response:**
```json
{
  "loans": [
    {
      "id": "loan-001",
      "studentId": "student-001",
      "bookId": "book-001", 
      "loanDate": "2024-01-15",
      "returnDate": "2024-06-15",
      "status": "RETURNED"
    }
  ]
}
```

## Service Discovery

### List Available Services

**Command:**
```bash
grpcurl -plaintext localhost:50051 list
```

**Expected Response:**
```
grpc.health.v1.Health
grpc.reflection.v1alpha.ServerReflection
university.BookService
university.LoanService
university.StudentService
```

### List Methods for Specific Service

**Command:**
```bash
grpcurl -plaintext localhost:50051 list university.BookService
```

**Expected Response:**
```
university.BookService.CreateBook
university.BookService.DeleteBook  
university.BookService.GetBook
university.BookService.ListBooks
university.BookService.UpdateBook
```
