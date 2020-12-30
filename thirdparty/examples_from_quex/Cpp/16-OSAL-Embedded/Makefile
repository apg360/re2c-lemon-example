all: lexer

FLAGS := -ggdb \
         -I. -I./osal/build/inc -I./osal/src/os/inc \
         -Wall -Werror \
         -Wno-int-to-pointer-cast 

# OPT_FLAGS  := -ffunction-sections -fdata-sections -nodefaultlibs -nostdli

CPP := g++ -c $(FLAGS)                          # $(OPT_FLAGS)
CC  := gcc -c $(FLAGS) -Wno-pointer-to-int-cast # $(OPT_FLAGS)
LD  := g++ -ggdb                                    

# Lexer _______________________________________________________________________
#
tiny/tiny.cpp: tiny.qx
	quex -i tiny.qx -o tiny --tiny-stdlib

lexer: main.o tasks.o auxiliary.o tiny.o libOsalTiny.a
	$(LD) $^ -lpthread -lrt -ldl -o $@ 

%.o: %.cpp tiny/tiny.cpp osal
	$(CPP) $< -o $@ 

%.o: tiny/%.cpp       osal 
	$(CPP) $< -o $@ 

# OSAL ________________________________________________________________________
#
osal:
	7z x ../../C/16-OSAL-Embedded/osal-mini.7z -o./

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
