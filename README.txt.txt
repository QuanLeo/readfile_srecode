	Yêu cầu của đề bài là đọc file dang Srecord (SREC)
	viết chương trình parse file srecord :
		+ Kiểm tra file, in ra thông báo lỗi nếu có
		+ Nếu không có bất kỳ lỗi nào thì xuất ra dữ liệu đã được parse, bao gồm: địa chỉ, dữ liệu. Dữ liệu xuất ra ghi vào một file khác.
		+ Hai file ví dụ ở trong attachment.

	Ý tưởng của tôi :
		+ Đoc từng dòng trong file srecord
		+ Xử lí từng dòng một :
			- kiểm tra xem các kí tự có thuôc bảng mã ASCII không
			- Kiểm tra checksum của dòng
			- Kiểm tra dataline count của dòng
			- Kiem tra byte count cua dòng s5
			- Tao 1 ham process tìm các lỗi
			- Nếu không có lỗi data được xử lí và in vào trong file mới 

