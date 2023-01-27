#include "AppSettings.h"

using namespace Settings;

AppSettings::AppSettings(String^ configFileName) : XmlDocument()
{
	mConfigFileName = gcnew String(configFileName);

	if (!System::IO::File::Exists(configFileName))
	{
		gcnew XmlDocument();
		//
		this->AppendChild(this->CreateXmlDeclaration("1.0", "utf-8", "yes"));
		this->AppendChild(this->CreateElement("appSettings"));
		//
		this->Save(configFileName);
	}
	else
	{
		this->Load(configFileName);
	}

}

void AppSettings::GetParameterList(String^ parameterName, List<String^> ^macAddressStringList) {
	
	XmlNodeList^ macAddressNodeList = this->GetElementsByTagName(parameterName);
	if (macAddressNodeList->Count > 0) {
		for (auto i = 0; i<macAddressNodeList->Count; i++)
		{
			macAddressStringList->Add(macAddressNodeList->Item(i)->LastChild->Value);
		}
	}
}

void AppSettings::SaveParameter(String^ parameterName, String^ macAdress)
{
	XmlNodeList^ macAddressNodeList = this->GetElementsByTagName(parameterName);
	
	// Avoid to duplicate MAC addresses in the settings
	if (macAddressNodeList->Count > 0) {
		for (auto i = 0; i<macAddressNodeList->Count; i++)
		{
			if(macAddressNodeList->Item(i)->LastChild->Value == macAdress)
				return;
		}
	}

	XmlElement^ newMacAddressNode = this->CreateElement(parameterName);
	XmlText^ macAddressText = this->CreateTextNode(macAdress);
	newMacAddressNode->AppendChild(macAddressText);
	//
	XmlNodeList^ appSettingsNode = this->GetElementsByTagName("appSettings");
	appSettingsNode->Item(0)->AppendChild(newMacAddressNode);
	this->Save(mConfigFileName);
}