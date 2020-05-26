
//Program takes arguments: filename, offset, len, string.   Progrma opens 'filename' file, does lseek(offset), reads data of length 'len' and //verifies that data read is same as 'string' 
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>


void userp1(char* filename, off_t offset, int len, char* string) {
	
	int filedescriptor = open(filename, O_RDONLY);
	int stringlen = 0;
	int i;
	for(; string[stringlen] != '\0'; ++stringlen);
	lseek(filedescriptor, offset, SEEK_CUR);
	char buffer[len + 1];
	read(filedescriptor, buffer, len);
	if(len == stringlen) {
			
		for( i = 0; i < stringlen; i++) {
			
			if(buffer[i] != string[i]) 
				break;
		}
		if (i == stringlen) {
			printf("Both the strings are successfully matched");
		}
		else {
			printf("The strings are not matched and are different"); 
		}
	}
	else {
		printf("Strings not matching"); 
	}
	
	close(filedescriptor);
}
int main() {
	
	char r[] = "\ntor";
	userp1("sample.txt", 9, 3,r);
	
} 


