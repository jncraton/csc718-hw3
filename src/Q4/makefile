bins=p1 p2 p3 p4

all: $(bins)

%: %.c
	gcc $< -fopenmp -o $@
	./$@ | diff test/$@ -

clean:
	rm -f $(bins)