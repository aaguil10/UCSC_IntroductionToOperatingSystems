
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct{
    char* filename;
    char* tags[20];
    int dir;
    char* parent;
}file;


void load_files(){
	int buff_size = 90000;
  	char buffer[buff_size];

	int file_handle = open("origin", O_RDONLY);
	ssize_t l = read(file_handle, buffer, buff_size);

	//create and initilize file array.
 	file file_array[100];
 	for(int i = 0; i < 100; i++){
 		file_array[i].filename = NULL;
 		for (int j = 0; j < 20; ++j){
 			file_array[i].tags[i] = NULL;
 		}
 		file_array[i].dir = 0;
 		file_array[i].parent = NULL;
 	}

 	int file_count  = 0;

	while(l > 0){
		//parse file
		int file_index = 0;
		while(buffer[file_index] != '\0') { 
			char curr  = buffer[file_index];
		    char line_buffer[900]; 
		    int counter = 0;
		    //add line to line buffer
			while(curr != '\n'){ 
			  	curr = buffer[file_index];
			  	line_buffer[counter++] = curr;
				file_index++;
			}

			int line_index = 0;
			char curr2  = line_buffer[line_index];
		    char sixtyfour_buff[100]; 
		    int counter2 = 0;
		    //add 64 bit names to 64 buffer
			while(curr2 != ' '){ 
			  	curr2 = line_buffer[line_index];
			  	sixtyfour_buff[counter2++] = curr2;
				line_index++;
			}

			file_array[file_count].filename = sixtyfour_buff;
		  	printf("sixtyfour_buff: %s\n", file_array[file_count].filename);

			curr2  = line_buffer[line_index];
		    char tag_buff[100]; 
		    int counter3 = 0;
		    int tag_count = 0;
		    //read comma seprated tags
		    while(curr2 != '\0'){
		    	//put each tag in file struct
				while(curr2 != ','){ 
			  		curr2 = line_buffer[line_index];
			  		tag_buff[counter3++] = curr2;
			  		//printf("-%c", tag_buff[counter2 - 1] );
					line_index++;
					
				}
				//printf("\n");
				file_array[file_count].tags[tag_count++] = tag_buff;
				for(int i = 0; i < counter2;i++){
					tag_buff[i] = '\0';
				}
				counter3 = 0;
				curr2 = line_buffer[line_index++];
			}

			for(int i = 0; i < tag_count;i++){
				printf("	tag: %s\n", file_array[file_count].tags[i] );
			}

			//Reset line buffer
		  	for(int i = 0; i < file_index;i++){
				line_buffer[i] = '\0';
			}
		  	file_index++;
		  	file_count++;
	  	}
	  	l = read(file_handle, buffer, buff_size);
	}
	if(l < 0){
	  perror("Error: ");
	}
	close(file_handle);
 }

int main(){
    load_files();  
	return 0;
}