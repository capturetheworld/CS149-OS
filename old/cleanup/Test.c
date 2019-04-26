void foo(char a, char *b) {
	a = 'x'; *b = a; a = 'y'
}

char x = 'q';
foo(x, &x);

//X contins x






