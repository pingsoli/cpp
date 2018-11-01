#include <stdio.h>

void c();

void b(const char *a) {
	static const char *p = 0;

	if (!p) {
		p = a;
		c();
	} else {
		if (a==p) {
			printf("problem!\n");
		}
	}
}

void c() {
	const char a[] = { 0xd, 0xe, 0xa, 0xd, 0xb, 0xe, 0xe, 0xf };

	b(a);
}

int main() {
	c();
}
