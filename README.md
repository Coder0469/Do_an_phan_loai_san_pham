# ĐỒ ÁN CÁC THIẾT BỊ MẠCH ĐIỆN TỬ
## Đề tài: Băng chuyền phân loại sản phẩm theo 3 màu sắc đỏ, lục, lam

<img src="https://github.com/user-attachments/assets/dcf69dca-6f92-4df0-8f7d-e5a6c3e65f3b" width="300">

## **LINH KIỆN SỬ DỤNG**
- Bộ xử lý chính: **STM32F407VET6**
- Cảm biến **LCS3200** để đọc giá trị màu
- 2x Servo **SG90** làm cần gạt phân loại
- Màn hình **LCD1602** để hiển thị số lượng vật mỗi màu
- 2x Buck **LM2596** điều chỉnh điện áp từ adapter sang các linh kiện

## **CÁCH THỨC HOẠT ĐỘNG**
1. Khi đặt vật lên băng chuyền, nó sẽ đưa vật đến cảm biến LCS3200 để xác định màu của vật
2. Thông tin về màu của vật và thời gian tồn tại của nó sẽ được đưa vào hàng đợi (Queue)
3. Biến lưu số lượng vật có màu đó được tăng lên
4. MCU sẽ dựa trên thông tin của vật đứng đầu hàng (Front) và điều khiển cần gạt tương ứng, phân loại vật về đúng vị trí của nó
5. Sau khi vật đã được phân loại, thông tin về màu của nó trong Queue sẽ bị xóa (Pop)

## **VIDEO SẢN PHẨM**
[![Xem Video Demo](https://img.youtube.com/vi/6F3wyrPdCC0/0.jpg)](https://www.youtube.com/shorts/6F3wyrPdCC0)
