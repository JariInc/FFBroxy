#ifndef __LIBUSB_H__
#define __LIBUSB_H__

// Includes:
	#include <lusb0_usb.h>

// Prototypes:
	usb_dev_handle *initUSB();
	void closeUSB(usb_dev_handle *dev);
	int sendUSBPacket(usb_dev_handle *dev, int request, int value);

// Macros:
	// Device vendor and product id.
	#define MY_VID 0x03EB
	#define MY_PID 0x2043

	// Device configuration and interface id.
	#define MY_CONFIG 1
	#define MY_INTF 0

	// Device endpoint(s)
	#define EP_IN 0x81
	#define EP_OUT 0x01

#endif