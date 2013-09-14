all:
	cd src; make

clean:
	cd src; make clean
	rm -f lib/libCUtil.a
