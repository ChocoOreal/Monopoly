
Đối với các ô bàn cờ thì sẽ có:
Cũng như trên, mỗi dòng là một thông tin, và một file sẽ chứa nhiều thông tin.

```
ID @ Loại ô @ Tên @ Miêu tả @ Giá mua @ Giá thuê gốc @ Hệ số thuê @ Giá mua nhà @ Giá cầm cố
```

Danh sách các ô nằm trong cùng một file dữ liệu. Mỗi dòng là thông tin một ô.Các ô có cùng loại đặt cạnh nhau để thuận tiện cho việc khởi tạo. Thêm tham số trả về trong các constructor của các ô loại Cell để gán con trỏ ô vào đúng vị trí tương ứng trong _listCell của Game

Hàm toString() của Cell trả về vector string chứa các thông tin như sau

```
ID | Loại ô | Tên | Miêu tả | Giá mua | Giá thuê gốc | Hệ số thuê | Giá mua nhà | Giá cầm cố | Chủ sở hữu | Số lượng nhà hiện tại | Giá thuê hiện tại | Tình trạng cầm cố

```
Hàm toString() của Player trả về vector string chứa các thông tin như sau

```
ID | Nickname | Vị trí | Tên ảnh token | Số tiền | Ở tù