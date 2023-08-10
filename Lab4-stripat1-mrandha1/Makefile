TARGET = stats mainswap

all: $(TARGET)

stats: stats.c readfile.o
	gcc -Wvla -Werror -Wno-error=unused-variable -g -o stats stats.c readfile.o -lm

readfile.o: readfile.c readfile.h
	gcc -g -c readfile.c

mainswap: mainswap.c swap.s
	gcc -g -m32 -o mainswap mainswap.c swap.s

clean:
	$(RM) $(TARGET)  *.o
