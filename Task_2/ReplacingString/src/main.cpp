#include <iostream>
#include "replace.h"

void task2() {
	char pszResult[] = "aa aa aaa"; //"ABABCDCDCD-ABABCD__CDABAB"
	char pcszSubstr[] = "aa"; //"ABCD"
	char pcszStr2[] = "123"; //"0AB"

	std::cout << "input: " << pszResult << std::endl;
	std::cout << "which str to replace: " << pcszSubstr << std::endl;
	std::cout << "which str to replace it with: " << pcszStr2 << std::endl;
	std::cout << "--------------------------" << std::endl;

	char* result = strreplace(pszResult, pcszSubstr, pcszStr2);

	if (result != NULL) {
		std::cout << "output: " << result << std::endl;
		free(result);
	}
	else {
		std::cout << "the output array is missing" << std::endl;
	}
}

int main() {

	task2();

	return 0;
}
