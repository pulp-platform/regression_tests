############## Default compiler and possible option sets
CC        = gcc

OPT       = -O2

CFLAGS   = 
LDFLAGS  = -lgcc -lc -lm

ifdef N
  CFLAGS += -DN=$(N)
endif


############## Actual build process
app:
	$(CC) -o app $(CFLAGS) *.c  $(LDFLAGS)


############## Support routines
.PHONY : clean disassemble

all: app

clean:
	rm -f *.o app


run:
	./app
