#pragma once
#include "WOLClient.h"
#include "AppSettings.h"

#define VERSION "v1.0"
#define CONFIG_FILE "MagicPacketSender.settings"

namespace MagicPacketSender {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace WOL;
	using namespace Settings;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			wolClient = gcnew WOLClient();
			appSettings = gcnew AppSettings(CONFIG_FILE);
			macAddressList = gcnew List<String^>();
			bs = gcnew BindingSource();
			bs->DataSource = macAddressList;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnSend;
	private: System::Windows::Forms::Label^ lbMACAddress;
	private: System::Windows::Forms::TextBox^ tbMACAddress;

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Label^ lbLastUsed;
	private: System::Windows::Forms::ListBox^ lstbLastUsed;
		   WOLClient^ wolClient;
		   AppSettings^ appSettings;
		   List<String^>^ macAddressList;
		   BindingSource^ bs;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnSend = (gcnew System::Windows::Forms::Button());
			this->lbMACAddress = (gcnew System::Windows::Forms::Label());
			this->tbMACAddress = (gcnew System::Windows::Forms::TextBox());
			this->lbLastUsed = (gcnew System::Windows::Forms::Label());
			this->lstbLastUsed = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// btnSend
			// 
			this->btnSend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnSend->Location = System::Drawing::Point(80, 188);
			this->btnSend->Name = L"btnSend";
			this->btnSend->Size = System::Drawing::Size(150, 29);
			this->btnSend->TabIndex = 0;
			this->btnSend->Text = L"Send";
			this->btnSend->UseVisualStyleBackColor = true;
			this->btnSend->Click += gcnew System::EventHandler(this, &MainForm::btnSend_Click);
			// 
			// lbMACAddress
			// 
			this->lbMACAddress->AutoSize = true;
			this->lbMACAddress->Location = System::Drawing::Point(12, 9);
			this->lbMACAddress->Name = L"lbMACAddress";
			this->lbMACAddress->Size = System::Drawing::Size(71, 13);
			this->lbMACAddress->TabIndex = 1;
			this->lbMACAddress->Text = L"MAC Address";
			// 
			// tbMACAddress
			// 
			this->tbMACAddress->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tbMACAddress->Location = System::Drawing::Point(12, 25);
			this->tbMACAddress->Name = L"tbMACAddress";
			this->tbMACAddress->Size = System::Drawing::Size(285, 20);
			this->tbMACAddress->TabIndex = 2;
			// 
			// lbLastUsed
			// 
			this->lbLastUsed->AutoSize = true;
			this->lbLastUsed->Location = System::Drawing::Point(12, 58);
			this->lbLastUsed->Name = L"lbLastUsed";
			this->lbLastUsed->Size = System::Drawing::Size(55, 13);
			this->lbLastUsed->TabIndex = 3;
			this->lbLastUsed->Text = L"Last Used";
			// 
			// lstbLastUsed
			// 
			this->lstbLastUsed->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lstbLastUsed->FormattingEnabled = true;
			this->lstbLastUsed->Location = System::Drawing::Point(12, 74);
			this->lstbLastUsed->Name = L"lstbLastUsed";
			this->lstbLastUsed->Size = System::Drawing::Size(285, 108);
			this->lstbLastUsed->TabIndex = 4;
			this->lstbLastUsed->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::lstbLastUsed_SelectedIndexChanged);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(309, 228);
			this->Controls->Add(this->lstbLastUsed);
			this->Controls->Add(this->lbLastUsed);
			this->Controls->Add(this->tbMACAddress);
			this->Controls->Add(this->lbMACAddress);
			this->Controls->Add(this->btnSend);
			this->MinimumSize = System::Drawing::Size(325, 267);
			this->Name = L"MainForm";
			this->Text = L"MagicPacketSender";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
			this->Text = this->Text + " " + VERSION;
			//
			appSettings->GetParameterList("macAddress", macAddressList);
			//
			this->lstbLastUsed->DataSource = bs;
		}

		private: System::Void btnSend_Click(System::Object^ sender, System::EventArgs^ e) {
			this->wolClient->WakeMe(this->tbMACAddress->Text);
			//
			if (this->lstbLastUsed->FindString(this->tbMACAddress->Text) == ListBox::NoMatches)
			{
				this->macAddressList->Add(this->tbMACAddress->Text);
				this->lstbLastUsed->DataSource = macAddressList;
				
			}
			//
			appSettings->SaveParameter("macAddress", this->tbMACAddress->Text);
		}

		private: System::Void lstbLastUsed_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
			this->tbMACAddress->Text = this->lstbLastUsed->SelectedValue->ToString();
		}
};
}
