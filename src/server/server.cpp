#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "university.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace university;

// Mock data storage
class MockDatabase {
private:
    std::map<std::string, Book> books_;
    std::map<std::string, Student> students_;
    std::map<std::string, Loan> loans_;
    int counter_;

public:
    MockDatabase() : counter_(1) {
        // Initialize with some mock data
        initializeMockData();
    }

    void initializeMockData() {
        // Mock Books
        Book book1;
        book1.set_id("book-001");
        book1.set_title("Clean Code");
        book1.set_author("Robert C. Martin");
        book1.set_isbn("978-0132350884");
        book1.set_publisher("Prentice Hall");
        book1.set_page_count(464);
        book1.set_stock(5);
        books_[book1.id()] = book1;

        Book book2;
        book2.set_id("book-002");
        book2.set_title("Design Patterns");
        book2.set_author("Gang of Four");
        book2.set_isbn("978-0201633610");
        book2.set_publisher("Addison-Wesley");
        book2.set_page_count(395);
        book2.set_stock(3);
        books_[book2.id()] = book2;

        // Mock Students
        Student student1;
        student1.set_id("student-001");
        student1.set_name("Ali Veli");
        student1.set_student_number("20190001");
        student1.set_email("ali.veli@university.edu");
        student1.set_is_active(true);
        students_[student1.id()] = student1;

        Student student2;
        student2.set_id("student-002");
        student2.set_name("Ayşe Yılmaz");
        student2.set_student_number("20190002");
        student2.set_email("ayse.yilmaz@university.edu");
        student2.set_is_active(true);
        students_[student2.id()] = student2;

        // Mock Loans
        Loan loan1;
        loan1.set_id("loan-001");
        loan1.set_student_id("student-001");
        loan1.set_book_id("book-001");
        loan1.set_loan_date("2024-01-15");
        loan1.set_return_date("");
        loan1.set_status(LoanStatus::ONGOING);
        loans_[loan1.id()] = loan1;
    }

    std::string generateId(const std::string& prefix) {
        return prefix + "-" + std::to_string(counter_++);
    }

    // Book operations
    std::map<std::string, Book>& getBooks() { return books_; }
    std::map<std::string, Student>& getStudents() { return students_; }
    std::map<std::string, Loan>& getLoans() { return loans_; }
};

// Book Service Implementation
class BookServiceImpl final : public BookService::Service {
private:
    MockDatabase& db_;

public:
    BookServiceImpl(MockDatabase& db) : db_(db) {}

    Status GetBook(ServerContext* context, const GetBookRequest* request,
                   GetBookResponse* response) override {
        auto& books = db_.getBooks();
        auto it = books.find(request->id());
        if (it != books.end()) {
            *response->mutable_book() = it->second;
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Book not found");
    }

    Status ListBooks(ServerContext* context, const ListBooksRequest* request,
                     ListBooksResponse* response) override {
        auto& books = db_.getBooks();
        for (const auto& pair : books) {
            *response->add_books() = pair.second;
        }
        return Status::OK;
    }

    Status CreateBook(ServerContext* context, const CreateBookRequest* request,
                      CreateBookResponse* response) override {
        Book book = request->book();
        if (book.id().empty()) {
            book.set_id(db_.generateId("book"));
        }
        
        auto& books = db_.getBooks();
        books[book.id()] = book;
        *response->mutable_book() = book;
        return Status::OK;
    }

    Status UpdateBook(ServerContext* context, const UpdateBookRequest* request,
                      UpdateBookResponse* response) override {
        auto& books = db_.getBooks();
        auto it = books.find(request->book().id());
        if (it != books.end()) {
            books[request->book().id()] = request->book();
            *response->mutable_book() = request->book();
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Book not found");
    }

    Status DeleteBook(ServerContext* context, const DeleteBookRequest* request,
                      DeleteBookResponse* response) override {
        auto& books = db_.getBooks();
        auto it = books.find(request->id());
        if (it != books.end()) {
            books.erase(it);
            response->set_success(true);
            response->set_message("Book deleted successfully");
            return Status::OK;
        }
        response->set_success(false);
        response->set_message("Book not found");
        return Status(grpc::StatusCode::NOT_FOUND, "Book not found");
    }
};

// Student Service Implementation
class StudentServiceImpl final : public StudentService::Service {
private:
    MockDatabase& db_;

public:
    StudentServiceImpl(MockDatabase& db) : db_(db) {}

    Status GetStudent(ServerContext* context, const GetStudentRequest* request,
                      GetStudentResponse* response) override {
        auto& students = db_.getStudents();
        auto it = students.find(request->id());
        if (it != students.end()) {
            *response->mutable_student() = it->second;
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Student not found");
    }

    Status ListStudents(ServerContext* context, const ListStudentsRequest* request,
                        ListStudentsResponse* response) override {
        auto& students = db_.getStudents();
        for (const auto& pair : students) {
            *response->add_students() = pair.second;
        }
        return Status::OK;
    }

    Status CreateStudent(ServerContext* context, const CreateStudentRequest* request,
                         CreateStudentResponse* response) override {
        Student student = request->student();
        if (student.id().empty()) {
            student.set_id(db_.generateId("student"));
        }
        
        auto& students = db_.getStudents();
        students[student.id()] = student;
        *response->mutable_student() = student;
        return Status::OK;
    }

    Status UpdateStudent(ServerContext* context, const UpdateStudentRequest* request,
                         UpdateStudentResponse* response) override {
        auto& students = db_.getStudents();
        auto it = students.find(request->student().id());
        if (it != students.end()) {
            students[request->student().id()] = request->student();
            *response->mutable_student() = request->student();
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Student not found");
    }

    Status DeleteStudent(ServerContext* context, const DeleteStudentRequest* request,
                         DeleteStudentResponse* response) override {
        auto& students = db_.getStudents();
        auto it = students.find(request->id());
        if (it != students.end()) {
            students.erase(it);
            response->set_success(true);
            response->set_message("Student deleted successfully");
            return Status::OK;
        }
        response->set_success(false);
        response->set_message("Student not found");
        return Status(grpc::StatusCode::NOT_FOUND, "Student not found");
    }
};

// Loan Service Implementation
class LoanServiceImpl final : public LoanService::Service {
private:
    MockDatabase& db_;

public:
    LoanServiceImpl(MockDatabase& db) : db_(db) {}

    Status GetLoan(ServerContext* context, const GetLoanRequest* request,
                   GetLoanResponse* response) override {
        auto& loans = db_.getLoans();
        auto it = loans.find(request->id());
        if (it != loans.end()) {
            *response->mutable_loan() = it->second;
            return Status::OK;
        }
        return Status(grpc::StatusCode::NOT_FOUND, "Loan not found");
    }

    Status ListLoans(ServerContext* context, const ListLoansRequest* request,
                     ListLoansResponse* response) override {
        auto& loans = db_.getLoans();
        for (const auto& pair : loans) {
            if (request->student_id().empty() || 
                pair.second.student_id() == request->student_id()) {
                *response->add_loans() = pair.second;
            }
        }
        return Status::OK;
    }

    Status BorrowBook(ServerContext* context, const BorrowBookRequest* request,
                      BorrowBookResponse* response) override {
        auto& books = db_.getBooks();
        auto& students = db_.getStudents();
        auto& loans = db_.getLoans();

        // Check if book and student exist
        if (books.find(request->book_id()) == books.end()) {
            return Status(grpc::StatusCode::NOT_FOUND, "Book not found");
        }
        if (students.find(request->student_id()) == students.end()) {
            return Status(grpc::StatusCode::NOT_FOUND, "Student not found");
        }

        // Check book stock
        auto& book = books[request->book_id()];
        if (book.stock() <= 0) {
            return Status(grpc::StatusCode::FAILED_PRECONDITION, "Book out of stock");
        }

        // Create loan
        Loan loan;
        loan.set_id(db_.generateId("loan"));
        loan.set_student_id(request->student_id());
        loan.set_book_id(request->book_id());
        loan.set_loan_date("2024-06-15"); // Current date
        loan.set_return_date("");
        loan.set_status(LoanStatus::ONGOING);

        // Update book stock
        book.set_stock(book.stock() - 1);

        loans[loan.id()] = loan;
        *response->mutable_loan() = loan;
        return Status::OK;
    }

    Status ReturnBook(ServerContext* context, const ReturnBookRequest* request,
                      ReturnBookResponse* response) override {
        auto& loans = db_.getLoans();
        auto& books = db_.getBooks();

        auto it = loans.find(request->loan_id());
        if (it == loans.end()) {
            return Status(grpc::StatusCode::NOT_FOUND, "Loan not found");
        }

        auto& loan = it->second;
        if (loan.status() != LoanStatus::ONGOING) {
            return Status(grpc::StatusCode::FAILED_PRECONDITION, "Book already returned");
        }

        // Update loan
        loan.set_return_date("2024-06-15"); // Current date
        loan.set_status(LoanStatus::RETURNED);

        // Update book stock
        auto& book = books[loan.book_id()];
        book.set_stock(book.stock() + 1);

        *response->mutable_loan() = loan;
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    
    MockDatabase db;
    BookServiceImpl book_service(db);
    StudentServiceImpl student_service(db);
    LoanServiceImpl loan_service(db);

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&book_service);
    builder.RegisterService(&student_service);
    builder.RegisterService(&loan_service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "University Library gRPC Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
