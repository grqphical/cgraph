test:
	@gcc -o tests -std=c99 cgraph_tests.c
	@./tests
