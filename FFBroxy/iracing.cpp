#include "stdafx.h"
#include "iracing.h"

// Globals:
char *g_data = NULL;
int g_nData = 0;
time_t g_ttime;
FILE *g_file = NULL;


irsdk_header g_diskHeader;
irsdk_diskSubHeader g_diskSubHeader;
int g_diskSubHeaderOffset = 0;
int g_diskLastLap = -1;

void initIRacing() {
	if (irsdk_waitForDataReady(TIMEOUT, g_data))
	{
		const irsdk_header *pHeader = irsdk_getHeader();
		if (pHeader)
		{
			initData(pHeader, g_data, g_nData);
		}
	}
}

void closeiracing() {
	irsdk_shutdown();
}

void initData(const irsdk_header *header, char* &data, int &nData)
{
	if (data) delete[] data;
	nData = header->bufLen;
	data = new char[nData];
}

float getFFBIRacing() {
	if (irsdk_waitForDataReady(TIMEOUT, g_data))
	{
		const irsdk_header *pHeader = irsdk_getHeader();
		if (pHeader)
		{
			// if header changes size, assume a new connection
			if (!g_data || g_nData != pHeader->bufLen)
			{
				// realocate our g_data buffer to fit, and lookup some data offsets
				initData(pHeader, g_data, g_nData);
			}
			else if (g_data)
			{
				int g_SteeringWheelPctTorque = -1;

				g_SteeringWheelPctTorque = irsdk_varNameToOffset("SteeringWheelTorque"); // SteeringWheelPctTorque
				float SteeringWheelPctTorque = *((float *)(g_data + g_SteeringWheelPctTorque));
				return SteeringWheelPctTorque;
			}
		}
	}

	// otherwise return safe value
	return 0.0f;

}