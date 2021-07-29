#include "replace.h"

char* strreplace(char* pszResult, const char* pcszSubstr, const char* pcszStr2) {

	if (pszResult == NULL || pcszSubstr == NULL || pcszStr2 == NULL || strlen(pcszSubstr) == 0) {
		return NULL;
	}

	int length = std::strlen(pszResult);
	int substrLength = std::strlen(pcszSubstr);
	int substrLength2 = std::strlen(pcszStr2);

	int maxLength = length * substrLength2 + 1;
	int finalIndex = 0;
	int newLength = 0;

	char* pStart = pszResult;
	char* result = (char*)malloc(maxLength * sizeof(char));
	result[0] = '\0';

	char* pTemp = std::strstr(pszResult, pcszSubstr);
	while (pTemp) {
		strncat(result, pStart, pTemp - pStart);
		strcat(result, pcszStr2);

		newLength += (pTemp - pStart) + substrLength2;
		pStart = pTemp + substrLength;
		pTemp = std::strstr(pStart, pcszSubstr);
	}
	strcat(result, pStart);
	newLength += strlen(pStart) + 1;

	if (_msize(result) > newLength) {
		char* tmpResult = (char*)malloc(newLength * sizeof(char));
		tmpResult[0] = '\0';
		strcat(tmpResult, result);

		free(result);
		result = tmpResult;
	}

	return result;
}