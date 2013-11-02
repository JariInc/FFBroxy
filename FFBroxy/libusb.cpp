#include "stdafx.h"
#include "libusb.h"

usb_dev_handle *dev = NULL;

usb_dev_handle *open_dev(void)
{
	struct usb_bus *bus;
	struct usb_device *dev;

	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == MY_VID
				&& dev->descriptor.idProduct == MY_PID)
			{
				return usb_open(dev);
			}
		}
	}
	return NULL;
}

int initlibusb() {
	usb_init(); /* initialize the library */
	usb_find_busses(); /* find all busses */
	usb_find_devices(); /* find all connected devices */

	if (!(dev = open_dev()))
		return 0;
	else
		return 1;
}

void closelibusb() {
	if (dev != NULL)
		usb_close(dev);
}

int sendPacket(int request, int value) {
	char tmp[1];
	int ret;
	if (dev != NULL)
		ret = usb_control_msg(dev, USB_TYPE_VENDOR,
			request,
			value,
			MY_INTF,
			tmp, 0, 1000);
	else
		ret = -1;
	return ret;
}