# Default Lapacke: Openblas at CESGA
LDLIBS=-lopenblas

# Other systems (my Debian boxes, for example)
#LDLIBS=-llapacke

# Intel MKL at CESGA
# Module needed: imkl
# => module load openblas
# LDLIBS for intel compiler: icx (module needed: intel)
# Just invoke make like this: make CC=icx
#LDLIBS=-qmkl=sequential -lmkl_intel_lp64

CC = gcc
CFLAGS = -Wall -g -fopenmp

SRCS = dgesv.c main.c timer.c

OBJS = $(SRCS:.c=.o)



dgesv: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS) -fopenmp

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -fopenmp

clean:
	$(RM) dgesv $(OBJS) *~
