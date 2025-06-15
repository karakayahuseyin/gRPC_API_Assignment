**COMMAND** cd /home/huseyin/dev/projects/grpc-assignment/build && echo "=== Running C++ Client Application ===" && ./client

**OUTPUT**
=== Running C++ Client Application ===
University Library gRPC Client
Connected to: localhost:50051

=== Books List ===
ID: book-001
Title: Clean Code
Author: Robert C. Martin
ISBN: 978-0132350884
Publisher: Prentice Hall
Pages: 464
Stock: 6
---
ID: book-002
Title: Design Patterns
Author: Gang of Four
ISBN: 978-0201633610
Publisher: Addison-Wesley
Pages: 395
Stock: 2
---
ID: book-1
Title: Effective C++
Author: Scott Meyers
ISBN: 978-0321334879
Publisher: Addison-Wesley
Pages: 320
Stock: 7
---
ID: book-2
Title: Effective C++
Author: Scott Meyers
ISBN: 978-0321334879
Publisher: Addison-Wesley
Pages: 320
Stock: 7
---

=== Book Details ===
ID: book-001
Title: Clean Code
Author: Robert C. Martin
ISBN: 978-0132350884
Publisher: Prentice Hall
Pages: 464
Stock: 6

=== Book Created ===
ID: book-5
Title: The Pragmatic Programmer

=== Students List ===
ID: student-001
Name: Ali Veli
Student Number: 20190001
Email: ali.veli@university.edu
Active: Yes
---
ID: student-002
Name: Ayşe Yılmaz
Student Number: 20190002
Email: ayse.yilmaz@university.edu
Active: Yes
---
ID: student-3
Name: Mehmet Kaya
Student Number: 20240001
Email: mehmet.kaya@university.edu
Active: Yes
---

=== Student Created ===
ID: student-6
Name: Mehmet Demir

=== Loans List ===
ID: loan-001
Student ID: student-001
Book ID: book-001
Loan Date: 2024-01-15
Return Date: 2024-06-15
Status: RETURNED
---
ID: loan-4
Student ID: student-002
Book ID: book-002
Loan Date: 2024-06-15
Return Date: 
Status: ONGOING
---

=== Book Borrowed ===
Loan ID: loan-7
Student ID: student-002
Book ID: book-002
ReturnBook failed: Book already returned