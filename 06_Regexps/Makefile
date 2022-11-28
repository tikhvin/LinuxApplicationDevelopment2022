GENERATES = esub *.txt
CFLAGS = -Wall

esub: esub.c
	cc $^ -o esub

test: esub
	echo "Example 1" | sed -E 's/[0-9]/#/' > sed_result_1.txt
	./esub '[0-9]' '#' 'Example 1' > esub_result_1.txt
	cmp sed_result_1.txt esub_result_1.txt

	echo "Example 2" | sed -E 's/([a-z]?)([0-9])/\1#\2/' > sed_result_2.txt
	./esub '([a-z]?)([0-9])' '\1#\2' 'Example 2' > esub_result_2.txt
	cmp sed_result_2.txt esub_result_2.txt

	echo "Example 3" | sed -E 's/([a-z]?([0-9]))/\1#\2#\1/' > sed_result_3.txt
	./esub '([a-z]?([0-9]))' '\1#\2#\1' 'Example 3' > esub_result_3.txt
	cmp sed_result_3.txt esub_result_3.txt

clean:
	rm -f $(GENERATES)
