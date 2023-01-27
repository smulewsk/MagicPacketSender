#include "WOLClient.h"

using namespace WOL;

void WOLClient::WakeMe(String^ hwAddr) 
{
    const auto BUFFER_LENGTH(102);

    IPHostEntry^ localIpAddressList = Dns::GetHostEntry(Dns::GetHostName());

    // Send broadcast packet on all network interfaces
    for (int i = 0; i < localIpAddressList->AddressList->Length; i++)
    {
        // Filter out IPv6 addresses
        if (localIpAddressList->AddressList[i]->AddressFamily == AddressFamily::InterNetwork)
        {
            long long ipAddr = localIpAddressList->AddressList[i]->Address;
            //
            long long ipAddrBroadcast = (ipAddr & 0x00FFFFFF) | 0xFF000000;
            //
            this->Connect(gcnew IPAddress(ipAddrBroadcast), 0x2fff);
            this->SetClientToBrodcastMode();

            //buffer to be send
            array <unsigned char>^ buffer = gcnew array<unsigned char>(BUFFER_LENGTH);

            this->PrepareMagicPacket(buffer, hwAddr);

            //now send wake up packet
            this->Send(buffer, BUFFER_LENGTH);
        }

    }
}

void WOLClient::SetClientToBrodcastMode()
{
    if (this->Active)
        this->Client->SetSocketOption(SocketOptionLevel::Socket,
            SocketOptionName::Broadcast, 0);
}

void WOLClient::PrepareMagicPacket(array <unsigned char>^ buffer, String^ hwAddr)
{
    auto counter(0);
    
    // Magic Packet buffer = 6*0xFF + 16*MAC address

    for (int i = 0; i < 6; i++)
        buffer[counter++] = 0xFF;

    for (int i = 0; i < 16; i++)
    {
        int j = 0;
        for (int z = 0; z < 6; z++)
        {
            if (hwAddr[j] == ':') {
                j++;
            }
            buffer[counter++] =
                Byte::Parse(hwAddr->Substring(j, 2),
                    NumberStyles::HexNumber);
            j += 2;
        }
    }
}