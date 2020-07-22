#pragma once

#include "usbd_def.h"


#define USB_DEBUG_COUNT 300
struct usbDebugItem {
	uint32_t Interrupt;
	uint32_t IntData;
	struct usb_setup_req Request;
	uint8_t endpoint;
	uint16_t PacketSize;
	uint32_t xferBuff0;
	uint32_t xferBuff1;
};

extern struct usbDebugItem usbDebug[USB_DEBUG_COUNT];
extern uint16_t usbEventNo;
extern uint32_t usbEvents[USB_DEBUG_COUNT];
