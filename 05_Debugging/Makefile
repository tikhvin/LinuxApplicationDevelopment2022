GENERATES = range *.log
CFLAGS = -O0 -g -Wall

test: range
	gdb -x script_1.txt ./$< | grep "@@@" > script_1.log
	gdb -x script_2.txt ./$< | grep "@@@" > script_2.log
	cmp script_1.log reference_1.txt
	cmp script_2.log reference_2.txt

clean:
	rm -f $(GENERATES)
