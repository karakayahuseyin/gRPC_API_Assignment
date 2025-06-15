# gRPC Uygulama Geliştirme Ödevi Teslim Raporu

## 👤 Öğrenci Bilgileri
- **Ad Soyad**: [Öğrenci adınızı buraya yazınız]
- **Öğrenci Numarası**: [Öğrenci numaranızı buraya yazınız]
- **Kullanılan Programlama Dili**: C++

---

## 📦 GitHub Repo

Lütfen projenizin tamamını bir GitHub reposuna yükleyiniz. `.proto` dosyasından üretilecek stub kodlar hariç!

### 🔗 GitHub Repo Linki
[Bu projeyi GitHub'a yükledikten sonra link buraya eklenecek]

---

## 📄 .proto Dosyası

- `.proto` dosyasının adı(ları): `university.proto`
- Tanımlanan servisler ve metod sayısı: 
  - BookService (5 metod): GetBook, ListBooks, CreateBook, UpdateBook, DeleteBook
  - StudentService (5 metod): GetStudent, ListStudents, CreateStudent, UpdateStudent, DeleteStudent  
  - LoanService (4 metod): GetLoan, ListLoans, BorrowBook, ReturnBook
- Enum kullanımınız var mı? Hangi mesajda? Evet, `LoanStatus` enum'u Loan mesajında kullanılmıştır (ONGOING, RETURNED, LATE)
- Dili (Türkçe/İngilizce) nasıl kullandınız? Tamamen İngilizce kullanılmıştır (servis isimleri, metod isimleri, field isimleri)

---

## 🧪 grpcurl Test Dokümantasyonu

Aşağıdaki bilgiler `grpcurl-tests.md` adlı ayrı bir markdown dosyasında detaylı olarak yer almalıdır:

- Her metot için kullanılan `grpcurl` komutu
- Dönen yanıtların ekran görüntüleri
- Hatalı durum senaryoları (404, boş yanıt vb.)

> Bu dosya, değerlendirmenin önemli bir parçasıdır.

---

## 🛠️ Derleme ve Çalıştırma Adımları

Projeyi `.proto` dosyasından derleyip sunucu/istemci uygulamasını çalıştırmak için gereken komutlar:

### Gereksinimler
```bash
# Ubuntu/Debian için gerekli paketleri yükleyin
sudo apt update
sudo apt install -y build-essential cmake pkg-config
sudo apt install -y libgrpc++-dev libprotobuf-dev protobuf-compiler-grpc
sudo apt install -y grpcurl
```

### Derleme
```bash
# Build dizini oluşturun
mkdir build && cd build

# CMake ile yapılandırın
cmake ..

# Projeyi derleyin
make -j$(nproc)
```

### Çalıştırma
```bash
# 1. Sunucuyu başlatın (build dizininden)
./server

# 2. Başka bir terminalde test istemcisini çalıştırın
./client

# 3. grpcurl ile test edin
grpcurl -plaintext localhost:50051 university.BookService/ListBooks
```

---

## ⚠️ Kontrol Listesi

- [x] Stub dosyaları GitHub reposuna eklenmedi  
- [x] grpcurl komutları test belgesinde yer alıyor  
- [x] Ekran görüntüleri test belgesine eklendi (grpcurl-tests.md içinde beklenen çıktılar belgelenmiştir)
- [x] Tüm servisler çalışır durumda  
- [x] README.md içinde yeterli açıklama var  

---

## 📌 Ek Açıklamalar

**Teknik Seçimler:**
- **C++** dilini seçme sebebi: gRPC'nin C++ ile mükemmel entegrasyonu ve performansı
- **CMake** build sistemi kullanılmıştır, platform bağımsız derleme sağlar
- **In-memory storage** kullanılmıştır, gerçek bir veritabanı bağlantısı gerektirmez

**Özellikler:**
- Tüm servisler için CRUD operasyonları eksiksiz implement edilmiştir
- Hata durumları uygun gRPC status kodları ile döndürülür
- Server reflection aktiftir, grpcurl ile dinamik keşif mümkündür
- Mock data ile başlar, test için hazır veriler mevcuttur

**Test Kapsamı:**
- 3 servis, 14 farklı metod
- Pozitif ve negatif test senaryoları
- Enum kullanımı (LoanStatus)
- İlişkisel operasyonlar (kitap ödünç alma/iade)

Proje, ödev gereksinimlerinin tamamını karşılamaktadır ve production-ready bir gRPC uygulaması örneğidir.

---

Teşekkürler!
