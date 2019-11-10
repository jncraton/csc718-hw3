bins=p1 p2 p3 p4

all: $(bins)

%: %.c
	gcc $< -o $@

clean:
	rm -f $(bins)