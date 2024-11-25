clean: main.c clean_data.c clean_data.h output_data.c output_data.h read_data.c read_data.h
	gcc -o clean clean_data.c output_data.c read_data.c main.c