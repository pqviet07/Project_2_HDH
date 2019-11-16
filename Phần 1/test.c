#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_LENGTH 256           ///< The buffer length (crude but fine)
static char receive[BUFFER_LENGTH]; ///< The receive buffer from the LKM



/*
Để test CDV ta sử dụng 2 hàm sau đây
1.
	fd = open("/dev/myrandom", O_RDONLY); 
	Mở file ở chế độ (mode) chỉ đọc

2.
	ret = read(fd, receive, BUFFER_LENGTH);
	Đọc số ngẫu nhiên mà Module đã tạo ra
	Định dạng của module trả ra là một chuỗi ký tự

*/

int main()
{
    int ret, fd;
  
    printf("Bat dau mo file...\n");
    fd = open("/dev/myrandom", O_RDONLY); 
	
    if (fd < 0)//Kiểm tra mở file thành công không
    {
		
        perror("Mo file that bai...");
        return errno;
    }
	
	printf("Mo file thanh cong...\n");
    printf("Doc file...\n");
    ret = read(fd, receive, BUFFER_LENGTH); 
    if (ret < 0) //Kiểm tra đọc file thành công không
    {
        perror("Doc file that bai...");
        return errno;
    }
    printf("So ngau nhien nhan duoc la: [%s]\n", receive);
	
	
    printf("Ket thuc.\n");
    return 0;
}

