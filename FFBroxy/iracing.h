#include "irsdk_defines.h"

// Prototypes:
	void initIRacing();
	float getFFBIRacing();
	void initData(const irsdk_header *header, char* &data, int &nData);

// Macros:
	#define TIMEOUT 32