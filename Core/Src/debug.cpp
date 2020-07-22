#include "usbd_def.h"
#include "stm32f4xx.h"
#include <string>
#include <sstream>
#include <iomanip>

extern uint32_t usbEvents[300];
extern struct usb_setup_req usbReqs[300];
extern uint16_t usbEventNo;

void uartSendStr(const std::string& s) {
	for (char c : s) {
		while ((USART3->SR & USART_SR_TXE) == 0);
		USART3->DR = c;
	}

}

std::string IntToString(const int32_t& v) {
	std::stringstream ss;
	ss << v;
	return ss.str();
}


std::string HexToString(const uint32_t& v, const bool& spaces) {
	std::stringstream ss;
	ss << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << v;
	if (spaces) {
		//std::string s = ss.str();
		return ss.str().insert(2, " ").insert(5, " ").insert(8, " ");
	}
	return ss.str();
}


std::string HexByte(const uint16_t& v) {
	std::stringstream ss;
	ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << v;
	return ss.str();
}

extern "C" {
void dumpArray() {
	for (int i = 0; i < usbEventNo; ++i) {
		uartSendStr(IntToString(i) + "," + HexToString(usbEvents[i], false) + "," + HexByte(usbReqs[i].bmRequest) + ", " + HexByte(usbReqs[i].bRequest) + ", " + HexByte(usbReqs[i].wValue) + ", " + HexByte(usbReqs[i].wIndex) + ", " + HexByte(usbReqs[i].wLength) + "\n");
	}
}
}
