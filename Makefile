CC=g++
CFLAGS = -c  -std=c++11 

laa : 
	$(CC) $(CFLAGS) main.cpp Grid.cpp hash_table.cpp read_file.cpp object_list.cpp linked_list_of_curves.cpp Functions.cpp 
	

	$(CC) -o lsh main.o  Grid.o hash_table.o read_file.o object_list.o linked_list_of_curves.o Functions.o 
 
clean:
	rm  -rf *o Compile 



	  
	
