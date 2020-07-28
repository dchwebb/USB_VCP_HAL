#include "debug.h"
#include "stm32f4xx.h"
#include <string>
#include <sstream>
#include <iomanip>

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
	uartSendStr("Event,Interrupt,Int Data,Endpoint,mRequest,Request,Value,Index,Length,PacketSize,XferBuff0,XferBuff1\n");

	for (int i = 0; i < usbEventNo; ++i) {

		uartSendStr(IntToString(i) + ","
				+ HexToString(usbDebug[i].Interrupt, false) + ","
				+ HexToString(usbDebug[i].IntData, false) + ","
				+ IntToString(usbDebug[i].endpoint) + ","
				+ HexByte(usbDebug[i].Request.bmRequest) + ", "
				+ HexByte(usbDebug[i].Request.bRequest) + ", "
				+ HexByte(usbDebug[i].Request.wValue) + ", "
				+ HexByte(usbDebug[i].Request.wIndex) + ", "
				+ HexByte(usbDebug[i].Request.wLength) + ", "
				+ HexByte(usbDebug[i].PacketSize) + ", "
				+ HexToString(usbDebug[i].xferBuff0, false) + ", "
				+ HexToString(usbDebug[i].xferBuff1, false) + "\n");
	}



//	for (int i = 0; i < usbEventNo; ++i) {
//		uartSendStr(IntToString(i) + "," +
//				HexToString(usbDebug[i].Interrupt, false) + "," +
//				HexByte(usbDebug[i].Request.bmRequest) + ", " +
//				HexByte(usbDebug[i].Request.bRequest) + ", " +
//				HexByte(usbDebug[i].Request.wValue) + ", " +
//				HexByte(usbDebug[i].Request.wIndex) + ", " +
//				HexByte(usbDebug[i].Request.wLength) +
//				"\n");
//	}
}
}
