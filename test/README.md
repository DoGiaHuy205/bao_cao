# Báo Cáo

# D23_DoGiaHuy

## A. CÔNG VIỆC ĐÃ LÀM:

### 1. Báo cáo chung

- Trước đấy em chưa tiếp xúc với vi sử lý thì anh Sang có cho em tìm hiểu về ngôn ngữ, các ví dụ

	+ Tìm hiểu ngôn ngữ của ESP qua: [Link](https://docs.arduino.cc/language-reference/)
	
	+ Các ví dụ của ESP qua: [Link](https://wiki-content.arduino.cc/en/Tutorial/BuiltInExamples)
	
	+ Em có ghi chép lại qua [Link](https://docs.google.com/document/d/1sSXAhn731Ds_lqACL0Tv5UjbToF_tf_ileaAPmiWsms/edit?tab=t.0#heading=h.dh0lm8h6g3js)
	
- Bên cạnh đó em cũng đang được học về ESP ở CLB
	

### 2. Báo cáo công việc đã làm của những tuần trước

#### 2.1 Báo cáo ngày 12/10/2024

- Bắt đầu tìm hiểu về arduino và esp32

	+ Tìm hiểu về pinout của arduino uno và esp32 38pin

	+ Học các hàm chức năng digital và analog qua [Link](https://docs.arduino.cc/language-reference/en/functions/digital-io/digitalread/)

	+ Tìm hiểu led, nút bấm, biến trở, cùng code qua [Link](https://nshopvn.com/blog/tai-lieu-arduino-starter-kit-2021/#den-led)

#### 2.2 Báo cáo ngày 19/10/2024

- Tiếp tục tìm hiểu về arduino và esp32

	+ Học các hàm chức năng time

	+ Tìm hiểu còi buzz thụ động, quang trở, cảm biến nghiêng, cùng code

#### 2.3 Báo cáo ngày 26/10/2024

- Tiếp tục tìm hiểu về arduino và esp32

	+ Tìm hiểu Led 7 đoạn, màn hình LCD 1602, cùng code

- Tìm hiểu cách báo cáo trên gitbup (đã báo cáo ở trên)

		
## B. BÀI TẬP

- 5Bài: Sáng dần tắt dần, giọt nước, cánh bướm, rắn săn mồi, chuyển từ 1 đến 255 sang nhị phân(sáng bằng led)

	+ Bài5. Chuyển từ 1 đến 255 sang nhị phân(sáng bằng led)
https://drive.google.com/file/d/16_ukkg7Ak7KepVbQeDGaixUwcmDgqTqV/view?usp=sharing\

```cpp
void loop(){
  for(int i=1;i<256;i++){ 
	int dp[8]={0};
	int x=i;
	for(int i=7;i>=0;i--){  // gán giá trị vào mảng dp
	  dp[i]=x%2;
	  x/=2;					// chuyển sang hệ nhị phân
	}
	for(int j=0;j<8;j++){
	  digitalWrite(led[j],dp[j]); // cho các led sáng
	  delay(1);
	}
	delay(1000);
	for(int j=0;j<8;j++){
	  digitalWrite(led[j],0);		// cho các led tắt
	  delay(1);
	}
	delay(1000);
  }
}
```
- Bài tập đọc giá trị biến trở bằng serial và đọc trạng thái nút nhấn báo qua LED

- Bài tập một vài nốt nhạc tìm hiểu các câu lệnh, bật tắt LED theo giá trị quang trở, kiểm tra cảm biến có nghiêng hay không

- Bài tập biểu diễn từ 1 đến 9 bằng led 7 đoạn, nhấn nút bấm để sáng từ 1 đến 9

## C. Khó Khăn
	- Chưa có

## D. Mượn Đồ của LAP
	- Không
