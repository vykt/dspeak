.RECIPEPREFIX=>

all:
> ${CC} -O2 -fno-unwind-tables -o dspeak main.c

clean:
> -rm dspeak
