
//Program takes  a filename as argument. Program opens file. Gets file length using lseek(). Then divides the length into 10 equal parts. Opens a file 'copy' for writing. Program accesses 10 chunks in the input file, in random order and writes them to the 'copy' file (in the same random order) using lseek().  In the end the original and new file should be same.

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
void userp2(char *filename) {	
	char buffer[1024];
	int filedescriptor = open(filename, O_RDONLY);
	lseek(filedescriptor, (size_t)0, SEEK_CUR);
    	size_t size = lseek(filedescriptor, (size_t)0, SEEK_END);
	printf("size = %d" ,(int) size);
	int filedescriptor2  = open("copyfile.txt", O_WRONLY | O_CREAT);
	int no = size / 10;
	int m = size - no * 9 ; 
	for(int i = 0; i < 6; i++) {
		lseek(filedescriptor, (size_t)(i * no), SEEK_SET) ;
		lseek(filedescriptor2, (size_t)(i * no), SEEK_SET);
 		if(i == 9){
				read(filedescriptor, buffer, m);
				write(filedescriptor2, buffer, m);
		}	 
		else{
				read(filedescriptor, buffer, no);
				write(filedescriptor2, buffer, no);
	 	}
	}
	for(int i = 9; i > 5; i--) {
		lseek(filedescriptor, (size_t)(i * no), SEEK_SET) ;
		lseek(filedescriptor2, (size_t)(i * no), SEEK_SET);
 		if(i == 9){
				read(filedescriptor, buffer, m);
				write(filedescriptor2, buffer, m);
		}	 
		else{
				read(filedescriptor, buffer, no);
				write(filedescriptor2, buffer, no);
	 	}
	}
	close(filedescriptor);
	close(filedescriptor2);
		
} 
int main() {
	
	userp2("sample.txt");
	return 0;
} 
