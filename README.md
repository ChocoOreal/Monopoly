# Github đồ án TH OOP của 20CTT1TN3
"Thầy rất là mong chờ vào cái sản phẩm này của các em" - GV. Trần Anh Duy 2021.
## Giảng viên hướng dẫn:
- GV. Trần Anh Duy

Của nhóm 4, bao gồm các thành viên:
- Nguyễn Thế Hoàng - 20120090
- Phạm Thị Quỳnh Như - 20120153
- Nhan Gia Khâm - 20120504

Để có thể xem UML thì download về và nhấn vào [đây](https://app.diagrams.net) để mở UML đó lên và xem.



# Plan 1:
Mục tiêu: Hoàn thiện giao diện bàn cờ (hiển thị bàn cờ, xúc xắc, quân cờ di chuyển) và demo một số chức năng của các lớp dưới đây (xuất thông tin của các đối tượng sau khi thực thi phương thức của nó ra cửa sổ console là điều kiệu cần đạt được tối thiểu, nếu có thể sẽ xuất thông tin ra GUI)

Thế Hoàng: 
- Phần GUI (như trên) (Done)
- Class Game 

Khâm:
- Lớp Player (Done)
- Lớp Dice (Done)

Quỳnh Như:
- Lớp Cell (có thêm một số class khác như là NormalLand và Card).


# Plan 2: 6 / 12 / 2021
Cần phải hoàn thành ToString để ít nhất là xuất ra được thông cho người chơi.
Tối thiểu là nên xuất ra được thông tin người chơi trên UI.

Thế Hoàng:
- sửa lại cấu trúc command và UI

Quỳnh Như
- chỉnh lại liên hệ của Cell và cái Factory và cái NormalLand, có thể nên thêm một cái class bất động sản (RealEstate).

Khâm:
- code class Game và ~~Board~~. Để ý song song với cái bên UI để có thể kết nối lại hai phần với nhau.

# Plan 3: 20 / 12 / 2021
Mục tiêu: Hoàn thành phần xử lí Logic, mã nguồn. Hoàn tất việc thử nghiệm ở lớp giao diện người dùng.
Lưu ý là nhớ thay đổi thông tin cho các card Luck và Chances.

## Quy ước
* Biên dịch dưới chuẩn **C++ 17**

* Các phương thức trong lớp Cell chỉ nên trả về void, các **kết quả** trả về thông qua **truyền tham chiếu** để không phải mất công nghĩ kiểu trả về cho từng hành động

* Đối với các tham số truyền vào, chỉ nên **dùng truyền tham chiếu** với các kiểu của **thư viện** hoặc kiểu cần khởi tạo **"nặng"**, không cần truyền tham chiếu các biến có kiểu built-in (như int, double,...)

* Nên dùng các kiểu số nguyên **có dấu** (int,...) và kiểu số thực **double**

* Nên chuyển qua sử dụng các con trỏ "**an toàn**" của thư viện. Không nên trỏ cùng một đối tượng bởi nhiều con trỏ khác nhau trừ khi nó được quản lý bởi các lớp hay là một thuộc tính của lớp tham chiếu tới đối tượng khác.

* **Mô tả** bằng comment các phương thức trong Interface IGame cụ thể để có thể implement trong lớp Class

* Trong các file header (.h), chỉ include những gì cần phải có để file header đó **hoạt động**. Nếu trong file header chỉ có dùng kiểu con trỏ tới một class, mà chưa dùng phương thức của class đó, **không include file header của class** đó mà chỉ cần dùng forward declaration tên của class để tránh cyclic dependency.

* Nên test kĩ đảm bảo chương trình có thể **compile và chạy được** trước khi đẩy mã nguồn lên github.

## File Cell.h (Như)
Định nghĩa các ô đặc biệt còn lại (Go, GoToJail,...)
Hoàn thiện lớp Card
Hoàn thiện các hàm activateCell của các lớp ô bàn cờ

## File Comand.h (Hoàng)
Hoàn thiện các lớp Command đã xây dựng
Thêm UpdateCommand (Cập nhật thông tin của GUI)
Thêm NotifyCommand (Xuất thông tin và các lựa chọn (nếu có) để người dùng biết và lựa chọn)

## File Game.h (Khâm)
Quan sát Interface Game (IGame) và thực thi các phương thức đó. Bên Cell cần gì thì thêm phương thức đó

## File Player.h (Khâm)
...

## Các lớp của giao diện người dùng (Hoàng)
Thử nghiệm việc hiển thị thông tin theo filter của game, hoàn tất phân lớp các Class để mã nguồn gọn hơn
