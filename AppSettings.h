#pragma once

namespace Settings
{
	using namespace System;
	using namespace System::Xml;
	using namespace System::Collections::Generic;

	public ref class AppSettings : public XmlDocument
	{

	private:
		String^ mConfigFileName;
	public:
		AppSettings(String^ configFileName);
		
		void GetParameterList(String^ parameterName, List<String^> ^macAddressStringList);
		void SaveParameter(String^ parameterName, String^ macAddress);

	};

}



