all: calc_elidian.l calc_elidian.y
	flex -i calc_elidian.l
	bison calc_elidian.y
	gcc calc_elidian.tab.c -o calc_elidian -lm
	cls
	./calc_elidian