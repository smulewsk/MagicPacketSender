#include "WOLClient.h"

using namespace WOL;

void WOLClient::WakeMe(String^ hwAddr) 
{
    const auto BUFFER_LENGTH(102);
    const auto SUBMASK_FILTER(0x00FFFFFF);
    const auto BROADCAST_ADDRESS_VALUE(0xFF000000);
    const auto BROADCAST_PORT_VALUE(0x2FFF);

    IPHostEntry^ localIpAddressList = Dns::GetHostEntry(Dns::GetHostName());

    // Send broadcast packet on all network interfaces
    for (int i = 0; i < localIpAddressList->AddressList->Length; i++)
    {
        // Filter out IPv6 addresses
        if (localIpAddressList->AddressList[i]->AddressFamily == AddressFamily::InterNetwork)
        {
            long long ipAddr = localIpAddressList->AddressList[i]->Address;
            //
            long long ipAddrBroadcast = (ipAddr & SUBMASK_FILTER) | BROADCAST_ADDRESS_VALUE;
            //
            this->Connect(gcnew IPAddress(ipAddrBroadcast), BROADCAST_PORT_VALUE);
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
    const auto BUFFER_HEADING_SIZE(6);
    const auto MAC_ADDRESS_SIZE(6);
    const auto MAC_ADDRESS_REPETITIONS(16);
    const auto HEX_NUMBER_SIZE(2);

    // Magic Packet buffer = 6*0xFF + 16*MAC address

    for (int i = 0; i < BUFFER_HEADING_SIZE; i++)
        buffer[counter++] = 0xFF;

    for (int i = 0; i < MAC_ADDRESS_REPETITIONS; i++)
    {
        int j = 0;
        for (int z = 0; z < MAC_ADDRESS_SIZE; z++)
        {
            if (hwAddr[j] == ':') {
                j++;
            }
            buffer[counter++] =
                Byte::Parse(hwAddr->Substring(j, HEX_NUMBER_SIZE),
                    NumberStyles::HexNumber);
            j += HEX_NUMBER_SIZE;
        }
    }
}