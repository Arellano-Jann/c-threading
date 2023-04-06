CFLAGS = -pthread

loopedSummation: loopedSummation.c
	gcc -o $@ $^

threadedSummation: threadedSummation.c
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f loopedSummation threadedSummation