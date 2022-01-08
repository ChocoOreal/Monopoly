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

# Plan 4: 27/12/2021
Mục tiêu: hoàn chỉnh bộ cơ sở dữ liệu của trò chơi (dữ liệu thẻ, ô bàn cờ); hoàn chỉnh file config

## Hợp nhất GUI và mã nguồn Logic: 28/12/2021 -> hết ngày 29/12/2021
Không pull/push gì thêm, không cần phải chỉnh sửa gì trong mã nguồn vào giai đoạn này

## File Config (Postponed)
* Chỉnh số nhà tối đa trong trò chơi được xây
* Chỉnh số khách sạn tối đa trong trò chơi được xây
* Người chơi có phải chỉ được xây nhà vào lượt của mình và tại ô mình đang đứng hay không

## Hàm lấy dữ liệu xuất ra GUI
* `getData() -> vector <string> {Loại, Tên, Giá mua ô bàn cờ đó, Giá thuê gốc (chưa có công trình ở trên), }`
* Dữ liệu người chơI: getDate() -> vector <string> {Nickname, ID_hình ảnh token, Số thứ tự lượt đi, Tiền mặt hiện có, Có đang trong tù không, Có giữ thẻ ra tù không}

# Deadline: 14/1/2022

# Plan 5: 

* Theo dõi định dạng các file dữ liệu trong file Document/metadata format.md
* Chỉnh sửa trong folder Logic_sourcecode cần copy lại qua Comporated_sourcecode trước khi đẩy lên

* Tạo file chứa dữ liệu Cell (Như) và chỉnh constructor của Cell trả về ID của nó
* Khởi tạo danh sách các Cell (đọc từ file dữ liệu trên) và danh sách Player cho lớp Game (Khâm)
* Gọi hàm notifyChange trong các lớp Cell và Player khi thuộc tính của chúng thay đổi
* Những phần còn lại (Hoàng)








