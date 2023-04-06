CFLAGS = -pthread

loopedSummation: loopedSummation.c
	gcc -o $@ $^
	./loopedSummation tenValues.txt

threadedSummation: threadedSummation.c
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f loopedSummation threadedSummation