# Zombie Survival Game - C++

## Giới thiệu

Game sinh tồn tiêu diệt zombie được viết bằng C++, chạy trên terminal. Người chơi phải sống sót qua 30 ngày, mỗi ngày sẽ có một đàn zombie tấn công. Người chơi có thể lên level, học skill mới và dùng đồ để trụ lại đến cuối game.

Project này sử dụng các cấu trúc dữ liệu tự cài đặt (không dùng STL) như LinkedList, Queue, PriorityQueue, HashTable, cùng với các giải thuật sắp xếp và tìm kiếm trong lib/.

## Cấu trúc thư mục

```
StudentID1_StudentID2/
├── lib/
│   ├── Algorithm.hpp       (sắp xếp: bubble, selection, insertion, heap, quick, merge + tìm kiếm: linear, binary)
│   ├── HashTable.hpp       (hash table dùng mảng BST)
│   ├── LinkedList.hpp      (danh sách liên kết đơn)
│   ├── PriorityQueue.hpp   (hàng đợi ưu tiên dùng heap)
│   └── Queue.hpp           (hàng đợi vòng)
├── app/
│   ├── main.cpp            (hàm main)
│   ├── Game.h / Game.cpp   (logic chính của game)
│   ├── Player.h            (thông tin và skill người chơi)
│   └── Zombie.h            (thông tin zombie, hàm tạo zombie theo ngày)
├── Makefile
├── run.bat                 (file chạy nhanh trên Windows - double click hoặc chạy trong terminal)
├── demo.txt                (link video demo)
└── README.md
```

---

## Hướng dẫn cài đặt và chạy (Windows)

 — Chạy game

**Cách 1: 
- Mở thư mục project, double-click file **`run.bat`**
- File này sẽ tự biên dịch và chạy game luôn

**Cách 2: 
- Mở Command Prompt hoặc PowerShell, cd vào thư mục project:
  ```
  cd đường_dẫn_tới_thư_mục
  ```
- Chạy bằng Makefile:
  ```
  mingw32-make
  game.exe
  ```
- Hoặc biên dịch thủ công không cần Makefile:
  ```
  g++ -std=c++17 -Ilib -Iapp app/Game.cpp app/main.cpp -o game.exe
  game.exe
  ```

---

## Cách chơi

1. Chạy chương trình, nhập tên nhân vật
2. Mỗi ngày sẽ có nhiều zombie xuất hiện theo hàng, đánh lần lượt từng con
3. Mỗi lượt chọn skill bằng cách nhập số tương ứng rồi Enter
4. Có 3 skill mặc định từ đầu: đánh thường, phòng thủ, dùng thuốc
5. Lên level sẽ mở thêm skill mới (tối đa level 6)
6. Sống sót qua đủ 30 ngày là thắng

## Lưu ý

- Game chạy trên terminal nên cần cửa sổ đủ rộng để hiển thị đẹp
- Nếu chạy `run.bat` mà cửa sổ terminal đóng ngay thì click chuột phải vào file → **"Run as administrator"**
