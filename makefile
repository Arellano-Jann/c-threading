CFLAGS = -pthread

loopedSummation: loopedSummation.c
	gcc -o $@ $^

threadedSummation: threadedSummation.c
	gcc $(CFLAGS) -o $@ $^