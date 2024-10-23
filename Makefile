CC=gcc
IDIR=src/include
DEPS=$(IDIR)/stb_image.h
LIBS=-lm

.PHONY: build run

build:
	$(CC) -o image-to-ascii src/main.c $(DEPS) $(LIBS)

run: build
	./image-to-ascii image.jpg

