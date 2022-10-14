GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so *.txt README
TRASH = *.o

CFLAGS = -Wall -fPIC

all: prog prog-a prog-so README

prog: const.o fun.o prog.o

prog.o fun.o: outlib.h

prog-a: prog.o liboutput_static.a

prog-so: prog.o liboutput.so

prog-a prog-so:
	cc -L. $< -$(subst lib,l,$(basename $(word 2, $^))) -o $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

test: prog prog-a prog-so
	for program in $^ ; do \
		> $@-$$program.txt ; \
		if [ $$program != "prog-so" ] ; then \
			./$$program >> $@-$$program.txt 2> /dev/null ; \
			./$$program one >> $@-$$program.txt ; \
			./$$program one two three >> $@-$$program.txt ; \
		else \
			LD_LIBRARY_PATH=$(shell pwd) ./$$program >> $@-$$program.txt 2> /dev/null ; \
			LD_LIBRARY_PATH=$(shell pwd) ./$$program one >> $@-$$program.txt ; \
			LD_LIBRARY_PATH=$(shell pwd) ./$$program one two three >> $@-$$program.txt ; \
		fi ; \
	done
	cmp $@-$(word 1, $^).txt $@-$(word 2, $^).txt
	cmp $@-$(word 2, $^).txt $@-$(word 3, $^).txt
	
README: prog prog-a prog-so
	>z $@
	for program in $^ ; do \
		if [ $$program != "prog-so" ] ; then \
			./$$program 2>> $@ ; \
		else \
			LD_LIBRARY_PATH=$(shell pwd) ./$$program 2>> $@ ; \
		fi ; \
	done

clean:
	rm -f $(GENERATES) $(TRASH)
