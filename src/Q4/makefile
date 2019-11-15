bins=p1 p2 p3 p4 seq/p2

all: $(bins)

%: %.c
	gcc -O3 $< -fopenmp -o $@
	./$@ | diff test/$@ -
	time ./$@ > /dev/null

clean:
	rm -f $(bins)