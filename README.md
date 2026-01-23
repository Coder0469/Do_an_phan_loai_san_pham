# ĐỒ ÁN CÁC THIẾT BỊ MẠCH ĐIỆN TỬ
## Đề tài: Băng chuyền phân loại sản phẩm theo 3 màu sắc đỏ, lục, lam

<img src="https://github.com/user-attachments/assets/dcf69dca-6f92-4df0-8f7d-e5a6c3e65f3b" width="300">
<img src="https://github.com/user-attachments/assets/895f41e2-e9a5-49ae-bd1a-e0956cb812f1" width="400">

## **LINH KIỆN SỬ DỤNG**
- Bộ xử lý chính: **STM32F407VET6**
- Cảm biến **LCS3200** để đọc giá trị màu
- 2x Servo **SG90** làm cần gạt phân loại
- Màn hình **LCD1602** để hiển thị số lượng vật mỗi màu
- 2x Buck **LM2596** điều chỉnh điện áp từ adapter sang các linh kiện

## **CÁCH THỨC HOẠT ĐỘNG**
1. Khi đặt vật lên băng chuyền, nó sẽ đưa vật đến cảm biến LCS3200 để xác định màu của vật
2. Thông tin về màu của vật và thời gian đi từ cảm biến đến cần gạt sẽ được đưa vào hàng đợi (Queue)
3. Biến lưu số lượng vật có màu đó được tăng lên
4. MCU sẽ dựa trên thông tin của vật đứng đầu hàng (Front) và điều khiển cần gạt tương ứng, phân loại vật về đúng vị trí của nó
5. Sau khi vật đã được phân loại, thông tin về màu của nó trong Queue sẽ bị xóa (Pop)

## **VIDEO SẢN PHẨM**
[![Xem Video Demo](https://img.youtube.com/vi/6F3wyrPdCC0/0.jpg)](https://www.youtube.com/shorts/6F3wyrPdCC0)


English version
# Project: Object classifier based on colors (Red, Green, Blue) using STM32

## **COMPONENTS**
- Main microcontrooler: **STM32F407VET6**
- Color sensor: **LCS3200**
- 2x **SG90** Servos acting as sorting arms
- **LCD1602 Display** to show the quantity of items per color
- 2x **LM2596** Buck converters to regulate voltage from the adapter to the components

Here is the translation of the operating logic into English.

## **HOW DOES IT WORK**
1. When an object is placed on the conveyor belt, it is transported to the LCS3200 sensor to detect its color.
2. The object's color information and the travel time from the sensor to the sorting arm are added (Pushed) into a Queue.
3. The variable counting the quantity of items for that specific color is incremented.
4. The MCU reads the data at the Front of the Queue and controls the corresponding servo arm to sort the object into its correct position.
5. After the object has been sorted, its data is removed (Popped) from the Queue.
