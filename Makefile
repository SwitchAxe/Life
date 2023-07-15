##
# life: a simple C cli implementation of Conway's game of life
#
# @file
# @version 0.1

life: main.c
	$(CC) main.c -o life

clean:
	rm life
# end
