#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>

#include "university.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace university;

class UniversityLibraryClient {
public:
    UniversityLibraryClient(std::shared_ptr<Channel> channel)
        : book_stub_(BookService::NewStub(channel)),
          student_stub_(StudentService::NewStub(channel)),
          loan_stub_(LoanService::NewStub(channel)) {}

    // Book operations
    void ListBooks() {
        ListBooksRequest request;
        ListBooksResponse response;
        ClientContext context;

        Status status = book_stub_->ListBooks(&context, request, &response);

        if (status.ok()) {
            std::cout << "\n=== Books List ===" << std::endl;
            for (const auto& book : response.books()) {
                std::cout << "ID: " << book.id() << std::endl;
                std::cout << "Title: " << book.title() << std::endl;
                std::cout << "Author: " << book.author() << std::endl;
                std::cout << "ISBN: " << book.isbn() << std::endl;
                std::cout << "Publisher: " << book.publisher() << std::endl;
                std::cout << "Pages: " << book.page_count() << std::endl;
                std::cout << "Stock: " << book.stock() << std::endl;
                std::cout << "---" << std::endl;
            }
        } else {
            std::cout << "ListBooks failed: " << status.error_message() << std::endl;
        }
    }

    void GetBook(const std::string& id) {
        GetBookRequest request;
        request.set_id(id);
        GetBookResponse response;
        ClientContext context;

        Status status = book_stub_->GetBook(&context, request, &response);

        if (status.ok()) {
            const auto& book = response.book();
            std::cout << "\n=== Book Details ===" << std::endl;
            std::cout << "ID: " << book.id() << std::endl;
            std::cout << "Title: " << book.title() << std::endl;
            std::cout << "Author: " << book.author() << std::endl;
            std::cout << "ISBN: " << book.isbn() << std::endl;
            std::cout << "Publisher: " << book.publisher() << std::endl;
            std::cout << "Pages: " << book.page_count() << std::endl;
            std::cout << "Stock: " << book.stock() << std::endl;
        } else {
            std::cout << "GetBook failed: " << status.error_message() << std::endl;
        }
    }

    void CreateBook() {
        CreateBookRequest request;
        Book* book = request.mutable_book();
        
        book->set_title("The Pragmatic Programmer");
        book->set_author("David Thomas, Andrew Hunt");
        book->set_isbn("978-0201616224");
        book->set_publisher("Addison-Wesley");
        book->set_page_count(352);
        book->set_stock(10);

        CreateBookResponse response;
        ClientContext context;

        Status status = book_stub_->CreateBook(&context, request, &response);

        if (status.ok()) {
            std::cout << "\n=== Book Created ===" << std::endl;
            std::cout << "ID: " << response.book().id() << std::endl;
            std::cout << "Title: " << response.book().title() << std::endl;
        } else {
            std::cout << "CreateBook failed: " << status.error_message() << std::endl;
        }
    }

    // Student operations
    void ListStudents() {
        ListStudentsRequest request;
        ListStudentsResponse response;
        ClientContext context;

        Status status = student_stub_->ListStudents(&context, request, &response);

        if (status.ok()) {
            std::cout << "\n=== Students List ===" << std::endl;
            for (const auto& student : response.students()) {
                std::cout << "ID: " << student.id() << std::endl;
                std::cout << "Name: " << student.name() << std::endl;
                std::cout << "Student Number: " << student.student_number() << std::endl;
                std::cout << "Email: " << student.email() << std::endl;
                std::cout << "Active: " << (student.is_active() ? "Yes" : "No") << std::endl;
                std::cout << "---" << std::endl;
            }
        } else {
            std::cout << "ListStudents failed: " << status.error_message() << std::endl;
        }
    }

    void CreateStudent() {
        CreateStudentRequest request;
        Student* student = request.mutable_student();
        
        student->set_name("Mehmet Demir");
        student->set_student_number("20210003");
        student->set_email("mehmet.demir@university.edu");
        student->set_is_active(true);

        CreateStudentResponse response;
        ClientContext context;

        Status status = student_stub_->CreateStudent(&context, request, &response);

        if (status.ok()) {
            std::cout << "\n=== Student Created ===" << std::endl;
            std::cout << "ID: " << response.student().id() << std::endl;
            std::cout << "Name: " << response.student().name() << std::endl;
        } else {
            std::cout << "CreateStudent failed: " << status.error_message() << std::endl;
        }
    }

    // Loan operations
    void ListLoans() {
        ListLoansRequest request;
        ListLoansResponse response;
        ClientContext context;

        Status status = loan_stub_->ListLoans(&context, request, &response);

        if (status.ok()) {
            std::cout << "\n=== Loans List ===" << std::endl;
            for (const auto& loan : response.loans()) {
                std::cout << "ID: " << loan.id() << std::endl;
                std::cout << "Student ID: " << loan.student_id() << std::endl;
                std::cout << "Book ID: " << loan.book_id() << std::endl;
                std::cout << "Loan Date: " << loan.loan_date() << std::endl;
                std::cout << "Return Date: " << loan.return_date() << std::endl;
                std::cout << "Status: " << LoanStatus_Name(loan.status()) << std::endl;
                std::cout << "---" << std::endl;
            }
        } else {
            std::cout << "ListLoans failed: " << status.error_message() << std::endl;
        }
    }

    void BorrowBook(const std::string& student_id, const std::string& book_id) {
        BorrowBookRequest request;
        request.set_student_id(student_id);
        request.set_book_id(book_id);
        
        BorrowBookResponse response;
        ClientContext context;

        Status status = loan_stub_->BorrowBook(&context, request, &response);

        if (status.ok()) {
            std::cout << "\n=== Book Borrowed ===" << std::endl;
            std::cout << "Loan ID: " << response.loan().id() << std::endl;
            std::cout << "Student ID: " << response.loan().student_id() << std::endl;
            std::cout << "Book ID: " << response.loan().book_id() << std::endl;
        } else {
            std::cout << "BorrowBook failed: " << status.error_message() << std::endl;
        }
    }

    void ReturnBook(const std::string& loan_id) {
        ReturnBookRequest request;
        request.set_loan_id(loan_id);
        
        ReturnBookResponse response;
        ClientContext context;

        Status status = loan_stub_->ReturnBook(&context, request, &response);

        if (status.ok()) {
            std::cout << "\n=== Book Returned ===" << std::endl;
            std::cout << "Loan ID: " << response.loan().id() << std::endl;
            std::cout << "Return Date: " << response.loan().return_date() << std::endl;
            std::cout << "Status: " << LoanStatus_Name(response.loan().status()) << std::endl;
        } else {
            std::cout << "ReturnBook failed: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<BookService::Stub> book_stub_;
    std::unique_ptr<StudentService::Stub> student_stub_;
    std::unique_ptr<LoanService::Stub> loan_stub_;
};

int main(int argc, char** argv) {
    std::string target_str = "localhost:50051";
    
    UniversityLibraryClient client(
        grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

    std::cout << "University Library gRPC Client" << std::endl;
    std::cout << "Connected to: " << target_str << std::endl;

    // Test various operations
    client.ListBooks();
    client.GetBook("book-001");
    client.CreateBook();
    
    client.ListStudents();
    client.CreateStudent();
    
    client.ListLoans();
    client.BorrowBook("student-002", "book-002");
    client.ReturnBook("loan-001");

    return 0;
}
