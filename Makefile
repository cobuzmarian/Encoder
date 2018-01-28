build:
	gcc -Wall encoder.c -o encoder

run:
	gcc -Wall encoder.c -o encoder
	./encoder

clean:
	rm -f encoder
