FILES = preprocess.cpp defns.h
FILES2 = encode.cpp defns.h
FILES3 = decode.cpp defns.h
OBJS = preprocess.o
OBJS2 = encode.o
OBJS3 = decode.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

clean: $(OBJS) $(OBJS2) $(OBJS3) encode decode preprocess
	rm *.o

decode: $(OBJS3) encode preprocess
	$(CC) $(LFLAGS) $(OBJS3) -o decode

encode: $(OBJS2) preprocess
	$(CC) $(LFLAGS) $(OBJS2) -o encode

preprocess: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o preprocess

encode.o: $(FILES2)
	$(CC) $(CFLAGS) $(FILES2)

decode.o: $(FILES3)
	$(CC) $(CFLAGS) $(FILES3)

preprocess.o: $(FILES)
	$(CC) $(CFLAGS) $(FILES)


