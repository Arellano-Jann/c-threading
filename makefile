CFLAGS = -pthread

loopedSummation: loopedSummation.c
	gcc -o $@ $^
	./loopedSummation tenValues.txt

threadedSummation: threadedSummation.c
	gcc $(CFLAGS) -o $@ $^
	./threadedSummation 2 tenValues.txt 0

clean:
	rm -f loopedSummation threadedSummation