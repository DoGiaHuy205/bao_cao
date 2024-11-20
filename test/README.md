# D23_DoGiaHuy

## A. NỘI DUNG ĐÃ TÌM HIỂU VÀ ĐƯỢC HỌC

### Tìm hiểu về MQTT:

- Định nghĩa:

	+ Là một giao thức truyền tin đơn giản
	
	+ Cho phép các thiết bị IoT có thể phát hoặc nhận bản tin
	
		+ Được thiết kế cho các thiết bị IoT đơn giản
		
		+ Băng thông (khả năng chuyển, nhận tín hiệu trong một khoảng thời gian) thấp
		
		+ Giao thức rất thích hợp cho các ứng dụng IoT
		
	+ Cho phép người sử dụng có thể gửi các lệnh điều khiển cũng nhận các bản tin từ các thiết bị IoT
	
- Cách sử dụng chính:

	+ Phát lệnh điều khiển để điều khiển thiết bị IoT
	
	+ Đọc dữ liệu từ thiết bị 
	
- Những khái niệm cơ bản:

	+ Publish/Subscribe: Trong MQTT, một thiết bị IoT có thể phát dữ liệu qua một chủ đề hoặc có thể được đăng ký một chủ đề  để nhận những bản tin về chủ đề đó
	
	+ Messages: là bản tin trao đổi giữa các thiết bị, bản tin có thể là lệnh điều khiển hoặc dữ liệu
	
	+ Topics:
	
		+ Là chủ đề mỗi một thiết bị IoT đăng ký để nhận được các bản tin đến hoặc chủ đề mà các thiết bị IoT muốn gửi các bản tin đi
		
		+ Chủ đề được biểu diễn dưới dạng chuỗi ký tự và được tách nhau bởi một dấu gạch chéo (/), mỗi một dấu gạch chéo biểu thị một mức chủ
		
	+ Broker:
	
		+ Nhận tất cả các bản tin
		
		+ Lọc các bản tin dựa theo chủ 
		
		+ Gửi bản tin này đến thiết bị IoT đã đăng ký chủ đề tương ứng trước đó

- Demo về MQTT:

- Em đang tìm hiểu và chạy thử code examples theo link: https://khuenguyencreator.com/lap-trinh-esp32-mqtt-bat-tat-den-voi-hivemq-broker/#google_vignette
	
- Tìm hiểu về Hivemq broker:

	+ Hivemq Broker là nền tảng truyền nhận dữ liệu bằng giao thức MQTT
	
	+ Hivemq Broker chia thành 2 loại:

		+ Public broker: Sử dụng cổng 1883, không có bảo mật, thường dùng để test ứng dụng hoặc các sản phẩm đơn giản
		
		+ Private broker: Sử dụng cổng 8883 và bảo mật SSL/TLS. Thường sử dụng trong các sản phẩm thương mại

- Chạy thử code examples:

	+ Bước 1: Cài đặt thư viện pubsubclient
	
		+ Đã cài đặt được thư viện pubsubclient (nhưng mà lúc đấy e đọc trên web là "Mở terminal gõ lệnh pio lib install “knolleary/PubSubClient” thì em nghĩ là terminal trong app Arduino nên em không hiểu và nhờ anh Vũ cài hộ thư viện mà anh Vũ đã cài thư viện từ trên mạng và em vẫn chưa rõ lắm :))"
		
		+ Em cũng đã cài đặt các thông số của MQTT như Server broker và port của mình trên hivemq
		
	+ Bước 2: Kết nối với broker
	
		+ Web có nói "mỗi một thiết bị phải có 1 client ID riêng, nếu 2 thiết bị cùng client ID kết nối vào Broker. Nó sẽ đẩy thiết bị cũ ra hoặc không thể connect được. Trong bài này, mình sẽ cho Client ID 1 dãy số random khi kết nối vào." nên em vẫn để như code họ
	
	+ Bước 3: Kết nối phần cứng
	
		+ Đã mắc được mạch như trong video

	+(Tới đây thì buổi đầu em chưa nạp được code, sau đó về nhà thì đã nap được code tuy nhiên là vẫn chưa connect được ạ)
	
	+ Bước 4: Publish dữ liệu lên MQTT
	
	+ Bước 5: Subcrible dữ liêu từ MQTT


## B. CÔNG VIỆC TIẾP THEO

- Tiếp tục tìm hiểu về giao thức MQTT

## C. MƯỢN ĐỒ CỦA LAB

- Không