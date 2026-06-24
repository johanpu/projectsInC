#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	bool hasUpper;
	bool hasLower;
	bool hasSpecial;
	bool hasDigit;
	bool hasLength;
	bool hasSpaces;
} PasswordCheck;

#define MAX_PASSWORD_LENGTH 100

int isValidPassword(const char *str);
bool isspecial(char c);

int main(void) {
	char password[MAX_PASSWORD_LENGTH];

	printf("Enter password: ");

	/*
		fgets scans entire input instead of until space (which is what scanf does).
		strcspn is an index counter until it hits specified character, aka "\n".
		Then, it's just password[given index] = '/0'. Ensures fgets does not cause invalid passwords as it inserts \n
		by itself.
	*/
	if (fgets(password, sizeof(password), stdin)) {
		password[strcspn(password, "\n")] = '\0';
	}

	if (isValidPassword(password)) {
		printf("Password is valid.\n");
	}
	else {
		printf("Password is invalid.\n");
	}
}

bool isspecial(char c) {
	if (c == '%' || c == '$' || c == '&' || c == '*') {
		return true;
	}
	else {
		return false;
	}
}

int isValidPassword(const char *str) {
	PasswordCheck check = {
		.hasUpper = false,
		.hasLower = false,
		.hasSpecial = false,
		.hasDigit = false,
		.hasLength = false,
		.hasSpaces = false // must be true to be valid.
	};

	for (int i = 0; str[i] != '\0'; i++) {
		if (isupper(str[i])) {
			check.hasUpper = true;
		}

		if (islower(str[i])) {
			check.hasLower = true;
		}

		if (isspecial(str[i])) {
			check.hasSpecial = true;
		}

		if (isspace(str[i])) {
			check.hasSpaces = true;
		}

		if (isdigit(str[i])) {
			check.hasDigit = true;
		}
	}

	if (strlen(str) >= 8) {
		check.hasLength = true;
	}

	bool isValid = (
		check.hasUpper &&
		check.hasLower &&
		check.hasDigit &&
		check.hasSpecial &&
		!check.hasSpaces &&
		check.hasLength
	);

	return isValid;
}