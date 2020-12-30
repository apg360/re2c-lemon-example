all: lexer

FLAGS := -ggdb \
         -I. -I./osal/build/inc -I./osal/src/os/inc \
         -Wall -Werror \
         -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast 

# OPT_FLAGS  := -ffunction-sections -fdata-sections -nodefaultlibs -nostdli

CC := gcc -c $(FLAGS) # $(OPT_FLAGS)
LD := gcc -ggdb

# Lexer _______________________________________________________________________
#
tiny/tiny.c: tiny.qx
	quex -i tiny.qx -o tiny --tiny-stdlib --language C 

lexer: main.o tasks.o auxiliary.o tiny.o libOsalTiny.a
	$(LD) $^ -lpthread -lrt -ldl -o $@ 

%.o: %.c tiny/tiny.c osal
	$(CC) $< -o $@ 

%.o: tiny/%.c        osal 
	$(CC) $< -o $@ 

# OSAL ________________________________________________________________________
#
osal:
	7z x osal-mini.7z 

OSAL_OBJS := osfileapi.o osfilesys.o osapi.o osloader.o osnetwork.o \
             ostimer.o bsp_voltab.o bsp_start.o

osal/src/os/posix/osfileapi.c:          osal
osal/src/os/posix/osfilesys.c:          osal
osal/src/os/posix/osapi.c:              osal
osal/src/os/posix/osloader.c:           osal
osal/src/os/posix/osnetwork.c:          osal
osal/src/os/posix/ostimer.c:            osal
osal/src/bsp/pc-linux/src/bsp_start.c:  osal
osal/src/bsp/pc-linux/src/bsp_voltab.c: osal

%.o: osal/src/os/posix/%.c 
	$(CC) -c $(FLAGS) $< -o $@

%.o: osal/src/bsp/pc-linux/src/%.c 
	$(CC) -c $(FLAGS) $< -o $@

libOsalTiny.a: osal $(OSAL_OBJS)
	ar rcs $@ $(OSAL_OBJS)

#______________________________________________________________________________
clean:
	rm -rf lexer tiny/ build *.o *.a osal
