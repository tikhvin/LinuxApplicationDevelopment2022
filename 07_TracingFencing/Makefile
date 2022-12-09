GENERATES = move fake_remove.so *.txt
CFLAGS = -Wall

all: move fake_remove.so tests

move: move.c
	cc $^ -o $@

fake_remove.so: fake_remove.c
	cc -shared $^ -o $@

test_1: move
	./$@.sh in.txt out.txt

test_2: move
	./$@.sh in.txt out.txt

test_3: move
	./$@.sh in.txt out.txt

test_4: move fake_remove.so
	./$@.sh in_PROTECT.txt out.txt

tests: test_1 test_2 test_3 test_4

clean:
	rm -f $(GENERATES)