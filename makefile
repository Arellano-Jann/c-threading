CFLAGS = -pthread

loopedSummation: loopedSummation.c
	gcc -o $@ $^
	./loopedSummation tenValues.txt

threadedSummation: threadedSummation.c
	gcc $(CFLAGS) -o $@ $^
	./threadedSummation 2 tenValues.txt 0

all:
	make loopedSummation
	make threadedSummation
	./loopedSummation tenValues.txt
	./loopedSummation tenValues.txt

	./threadedSummation 2 tenValues.txt 0
	./threadedSummation 2 tenValues.txt 0
	./threadedSummation 4 tenValues.txt 0
	./threadedSummation 4 tenValues.txt 0
	./threadedSummation 8 tenValues.txt 0
	./threadedSummation 8 tenValues.txt 0

	./threadedSummation 2 tenValues.txt 1
	./threadedSummation 2 tenValues.txt 1
	./threadedSummation 4 tenValues.txt 1
	./threadedSummation 4 tenValues.txt 1
	./threadedSummation 8 tenValues.txt 1
	./threadedSummation 8 tenValues.txt 1

	./loopedSummation oneThousandValues.txt
	./loopedSummation oneThousandValues.txt

	./threadedSummation 2 oneThousandValues.txt 0
	./threadedSummation 2 oneThousandValues.txt 0
	./threadedSummation 4 oneThousandValues.txt 0
	./threadedSummation 4 oneThousandValues.txt 0
	./threadedSummation 8 oneThousandValues.txt 0
	./threadedSummation 8 oneThousandValues.txt 0

	./threadedSummation 2 oneThousandValues.txt 1
	./threadedSummation 2 oneThousandValues.txt 1
	./threadedSummation 4 oneThousandValues.txt 1
	./threadedSummation 4 oneThousandValues.txt 1
	./threadedSummation 8 oneThousandValues.txt 1
	./threadedSummation 8 oneThousandValues.txt 1

clean:
	rm -f loopedSummation threadedSummation