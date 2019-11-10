all: linpack_bench

linpack_bench: linpack_bench.cpp
	g++ -pg $< -o $@

clean:
	rm -f linpack_bench