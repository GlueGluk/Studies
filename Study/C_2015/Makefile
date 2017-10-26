CC=gcc

.PHONY: all test

all: wordsplit linesort countd

test: dict_std.txt dict.txt

util.o: util.c util.h
	$(CC) -c util.c -o util.o
wordsplit :wordsplit.c util.o
	$(CC) wordsplit.c util.o -o wordsplit
countd: countd.c util.h
	$(CC) countd.c util.o -o countd
data: books
#	wget -i book_urls1 --wait=5 
	cat *txt >data
dict_std.txt: data
	cat data |tr '[:punct:]' '\n' |tr '[:space:]' '\n' |tr -s '\n' | sort | tr A-Z a-z | uniq -c >dict_std.txt
dict.txt: wordsplit linesort countd data
	cat data |./wordsplit -l|./countd >dict.txt
sorted_dict.txt: data
	 cat data |tr '[:punct:]' '\n' |tr '[:space:]' '\n' |tr -s '\n'| sort | tr A-Z a-z | uniq -c |sort -k1 -nr >sorted_dict.txt

