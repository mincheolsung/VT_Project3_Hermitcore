CC=/opt/hermit/bin/x86_64-hermit-gcc
SRC=prog.c
PROG=prog
CFLAGS=
LDFLAGS= -pthread
PROXY=/opt/hermit/bin/proxy
MEM=4G
CPUS=8
VERBOSE=0

all: $(PROG)
	$(CC) $(CFLAGS) $(SRC) -o $(PROG) $(LDFLAGS)

test: all
	HERMIT_MEM=$(MEM) HERMIT_CPUS=${CPUS} HERMIT_VERBOSE=${VERBOSE} HERMIT_ISLE=uhyve HERMIT_KVM=0 $(PROXY) $(PROG)
