# Makefile for bitwise-tutor
# Created by: gopeterjun@naver.com
# Created on: Mon 09 Jun 2025
# Last Updated: Tue 10 Jun 2025
CC = gcc
CFLAGS = -g -fsanitize=address -Wall -O3 -std=c23
BINDIR = bin
SRCREGEX = *.c
VALFLAGS = --tool=memcheck --leak-check=full
# meaning of CFLAGS options
# -g emit debugging info
# -Wall emit all warnings
# -O3 optimization level 3
# -std=c23 use C23
# -fsanitize=address Use AddressSanitizer (part of GCC since 4.8)
.PHONY: all check-syntax clean cleanall mem test

all: $(BINDIR) bitwise_operators bwt debug_binary


$(BINDIR):
	mkdir -p $(BINDIR)

%: %.c | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $<

check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(SRCREGEX) || true

mem:
	@for file in $(BINDIR)/*; do \
		echo "Running valgrind on $$file..."; \
		valgrind $(VALFLAGS) ./"$$file" || true; \
	done

# run splint linter
test: all
	@for file in $(SRCREGEX); do \
		echo "Running splint on $$file..."; \
		splint "$$file" || true; \
	done

clean: all
	rm -f *.o

cleanall:
	rm -rf $(BINDIR)
