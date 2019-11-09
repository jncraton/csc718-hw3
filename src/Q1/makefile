EXECS=sieve1 sieve2 sieve3 sieve4 sieve5 sieve6
MPICC?=mpicc

all: ${EXECS} transfer

sieve1: sieve1.c
	@echo Building sieve1.c
	@${MPICC} -o sieve1 sieve1.c -lm
	@echo Completed

sieve2: sieve2.c
	@echo Building sieve2.c
	@${MPICC} -o sieve2 sieve2.c -lm
	@echo Completed

sieve3: sieve3.c
	@echo Building sieve3.c
	@${MPICC} -o sieve3 sieve3.c -lm
	@echo Completed

sieve4: sieve4.c
	@echo Building sieve4.c
	@${MPICC} -o sieve4 sieve4.c -lm
	@echo Completed

sieve5: sieve5.c
	@echo Building sieve5.c
	@${MPICC} -o sieve5 sieve5.c -lm
	@echo Completed

sieve6: sieve6.c
	@echo Building sieve6.c
	@${MPICC} -o sieve6 sieve6.c -lm
	@echo Completed

transfer:
	@echo Transferring files to Washington, Lincoln, and Roosevelt
	@scp -rp $(CURDIR)/* washington:$(CURDIR) > /dev/null
	@scp -rp $(CURDIR)/* lincoln:$(CURDIR) > /dev/null
	@scp -rp $(CURDIR)/* roosevelt:$(CURDIR) > /dev/null
	@echo Tranfer Complete

clean:
	@echo Removing ${EXECS}
	@rm ${EXECS}
