bins=p1 p2 p3 p4

all: $(bins)

%: %.c
	gcc $< -fopenmp -o $@
	./$@ | diff test/$@ -
	time ./$@ > /dev/null

clean:
	rm -f $(bins)