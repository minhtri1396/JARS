# JARS
Manager money by dividing it into 6 jars

## Chức năng:
- Nhập vào số tiền cần chia, ví dụ: 1.000.000
- Tính toán và chia số tiền truyền vào ra thành 6 phần tiền theo quy tắc JARS

## Main flow:
1. Nhập vào editbox(*) Money số tiền cần chia,
2. Click button Start để hiển thị kết quả.
Ví dụ: nhập 100000 vào editbox rối click button Start thì chương trình chia ra thành 6 phần tiền:
- Necessary: 55,000 VND
- Investment: 10,000 VND
- Education: 10,000 VND
- Long term: 10,000 VND
- Enjoying: 10,000 VND
- Giving: 5,000 VND

## Additional flow:
- Bỏ trống editbox và nhấn button Start: chương trình hiển thị MessageBox báo lỗi "Amount of money can not be blank."
- Nhập dấu '.' không hợp lệ thì thông báo: "You wrote invalid dots." và kèm theo các ví dụ dấu '.' hợp lệ và không hợp lệ.
- Nhập ký tự không hợp lệ, là ký tự khác 0 -> 9, khác dấu '.' và khác khoảng trắng thì thông báo:
	"You wrote invalid characters." và kèm theo thông báo các ký tự nào là hợp lệ.

## Chú thích:
* (*) giá trị nhập vào textbox có thể nhập chuỗi có chứa ký tự:
	+ 0 -> 9
	+ Khoảng trắng, vd: 100 000. Nếu chỉ nhập khoẳng trắng vào textbox thì xem như đó là số 0
	+ Dấu '.' để ngăn cách phần thập phân hay chia ra từng phần đơn vị, chục, trăm, nghìn, ...
		VD: 100.001 thì chương trình xem đây là số thực có phần thập phân là .001
		    100.000.000 thì chương trình xem đây là số nguyên có giá trị là 100 000 000 (một trăm triệu)
		    100.000 thì chương trình xem đây là số nguyên có giá trị là 100 (một trăm)

* (**) giá trị kết quả trả về có thể có chứa ký tự:
	+ Dấu ',' để thể hiện sự chia ra từng phần đơn vị, chục, trăm, nghìn, ...
		VD: 100,000 thì chương trình xem đây là số nguyên có giá trị là 100 000 (một trăm nghìn)
	+ Dấu '.' để ngăn cách phần thập phân.
		VD: 100.001 thì chương trình xem đây là số thực có phần thập phân là .001
