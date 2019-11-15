bins=p1 p2 p3 p4

all: $(bins)

%: %.c seq/%
	@gcc -O3 $< -fopenmp -o $@
	@./$@ | head -n -1 | diff test/$@ - || echo "Results do not match exactly"
	@seq/$@ | tail -n 1
	@./$@ | tail -n 1

seq/%: seq/%.c
	gcc -O3 $< -fopenmp -o $@

clean:
	rm -f $(bins)