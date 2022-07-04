FLEX=flex
BISON=bison
CC=gcc
LIBS=-I.

PROGRAMA = sintatico
LEXICO = lexico.l
SINTATICO = sintatico.y

$(PROGRAMA): $(LEXICO)
	$(FLEX) $(LEXICO)
	$(BISON) -d $(SINTATICO)
	$(CC) *.c $(LIBS) -o $(PROGRAMA)

clean:
	rm -f lex.yy.c
	rm -f sintatico
	rm -f sintatico.tab.c
	rm -f sintatico.tab.h