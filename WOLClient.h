#pragma once

namespace WOL
{
	using namespace System;
	using namespace System::Net;
	using namespace System::Globalization;
	using namespace System::Net::Sockets;
	using namespace System::Net;
	public ref class WOLClient : public UdpClient
	{
	public:
		WOLClient() {};
		void WakeMe(String^ hwAddr);
	private:
		void PrepareMagicPacket(array <unsigned char>^ buffer, String^ hwAddr);
		void SetClientToBrodcastMode();

	};
}


