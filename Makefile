all:
	gcc -o main main.c scheduler.c process.c CPU.c

clean:
	rm main
