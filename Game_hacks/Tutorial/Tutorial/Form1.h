#pragma once
#include <Windows.h>
#include <ctime>
#include <string>


namespace Tutorial {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	bool AmmoStatus;
	char AmmoOpCode[]="\xFF\x06";
	char AmmoDefaultOpCode[]="\xFF\x0E";
	DWORD AmmoAddress = 0x004637E9;

	bool RecoilStatus;
	char RecoilOpCode[]="\x90\x90";
	//char RecoilDefaultOpCode[]="\xFF\x0E";
	
	std::string Nops[] =
	{
		"\x90",
		"\x90\x90",
		"\x90\x90\x90",
		"\x90\x90\x90\x90",
	};
	
	std::string RecoilDefaultOpCode[] =
	{
		"\x8B\x16",
		"\x8B\x52\x14",
		"\x50",
		"\x8D\x4C\x24\x1C",
		"\x51",
		"\x8B\xCE",
		"\xFF\xD2"
	};

	DWORD RecoilAddresses[] = {0x00463781,0x00463783,0x00463786,0x00463787,0x0046378B,0x0046378C,0x0046378E};
	int NoOfBytes[] = {2,3,1,4,1,2,2};
	
	bool AutoGunStatus;
	char AutoGunCode[]="\xEB\x09";
	char AutoGunDefaultOpCode[]="\x75\x09";
	DWORD AutoGunAddress = 0x00463716;

	bool TimeStatus;
	char TimeDefaulOpCode[] = "\x89\x0A";
	DWORD TimeAddress = 0x004637E4;
	
	int OnPressTMR = clock();
	int GameTimer = clock();

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  TitleLBL;
	private: System::Windows::Forms::Label^  DLLStatus;
	private: System::Windows::Forms::Label^  automaticLBL;
	private: System::Windows::Forms::Label^  recoilLBL;
	private: System::Windows::Forms::Label^  ammoLBL;
	private: System::Windows::Forms::Label^  autogunLBL;
	private: System::Windows::Forms::Label^  recoilStatusLBL;
	private: System::Windows::Forms::Label^  ammoStatusLBL;
	private: System::Windows::Forms::Timer^  UpdateTimer;
	private: System::Windows::Forms::Label^  CadenceLBL;
	private: System::Windows::Forms::Label^  cadenceStatusLBL;






	private: System::ComponentModel::IContainer^  components;
	
	// protected: 

	/*protected: 

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
*/

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->TitleLBL = (gcnew System::Windows::Forms::Label());
			this->DLLStatus = (gcnew System::Windows::Forms::Label());
			this->automaticLBL = (gcnew System::Windows::Forms::Label());
			this->recoilLBL = (gcnew System::Windows::Forms::Label());
			this->ammoLBL = (gcnew System::Windows::Forms::Label());
			this->autogunLBL = (gcnew System::Windows::Forms::Label());
			this->recoilStatusLBL = (gcnew System::Windows::Forms::Label());
			this->ammoStatusLBL = (gcnew System::Windows::Forms::Label());
			this->UpdateTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->CadenceLBL = (gcnew System::Windows::Forms::Label());
			this->cadenceStatusLBL = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// TitleLBL
			// 
			this->TitleLBL->AutoSize = true;
			this->TitleLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->TitleLBL->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->TitleLBL->Location = System::Drawing::Point(25, 9);
			this->TitleLBL->Name = L"TitleLBL";
			this->TitleLBL->Size = System::Drawing::Size(287, 37);
			this->TitleLBL->TabIndex = 0;
			this->TitleLBL->Text = L"AssaultCube DLL";
			// 
			// DLLStatus
			// 
			this->DLLStatus->AutoSize = true;
			this->DLLStatus->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->DLLStatus->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->DLLStatus->Location = System::Drawing::Point(28, 46);
			this->DLLStatus->Name = L"DLLStatus";
			this->DLLStatus->Size = System::Drawing::Size(250, 24);
			this->DLLStatus->TabIndex = 1;
			this->DLLStatus->Text = L"DLL Status: Injected";
			// 
			// automaticLBL
			// 
			this->automaticLBL->AutoSize = true;
			this->automaticLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->automaticLBL->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->automaticLBL->Location = System::Drawing::Point(12, 132);
			this->automaticLBL->Name = L"automaticLBL";
			this->automaticLBL->Size = System::Drawing::Size(298, 24);
			this->automaticLBL->TabIndex = 7;
			this->automaticLBL->Text = L"[F3] All guns automatic:";
			// 
			// recoilLBL
			// 
			this->recoilLBL->AutoSize = true;
			this->recoilLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->recoilLBL->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->recoilLBL->Location = System::Drawing::Point(12, 108);
			this->recoilLBL->Name = L"recoilLBL";
			this->recoilLBL->Size = System::Drawing::Size(190, 24);
			this->recoilLBL->TabIndex = 6;
			this->recoilLBL->Text = L"[F2] No recoil:";
			// 
			// ammoLBL
			// 
			this->ammoLBL->AutoSize = true;
			this->ammoLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ammoLBL->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->ammoLBL->Location = System::Drawing::Point(12, 84);
			this->ammoLBL->Name = L"ammoLBL";
			this->ammoLBL->Size = System::Drawing::Size(214, 24);
			this->ammoLBL->TabIndex = 5;
			this->ammoLBL->Text = L"[F1] Freeze ammo:";
			// 
			// autogunLBL
			// 
			this->autogunLBL->AutoSize = true;
			this->autogunLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->autogunLBL->ForeColor = System::Drawing::Color::Red;
			this->autogunLBL->Location = System::Drawing::Point(312, 132);
			this->autogunLBL->Name = L"autogunLBL";
			this->autogunLBL->Size = System::Drawing::Size(46, 24);
			this->autogunLBL->TabIndex = 10;
			this->autogunLBL->Text = L"OFF";
			// 
			// recoilStatusLBL
			// 
			this->recoilStatusLBL->AutoSize = true;
			this->recoilStatusLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->recoilStatusLBL->ForeColor = System::Drawing::Color::Red;
			this->recoilStatusLBL->Location = System::Drawing::Point(312, 108);
			this->recoilStatusLBL->Name = L"recoilStatusLBL";
			this->recoilStatusLBL->Size = System::Drawing::Size(46, 24);
			this->recoilStatusLBL->TabIndex = 9;
			this->recoilStatusLBL->Text = L"OFF";
			// 
			// ammoStatusLBL
			// 
			this->ammoStatusLBL->AutoSize = true;
			this->ammoStatusLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ammoStatusLBL->ForeColor = System::Drawing::Color::Red;
			this->ammoStatusLBL->Location = System::Drawing::Point(312, 84);
			this->ammoStatusLBL->Name = L"ammoStatusLBL";
			this->ammoStatusLBL->Size = System::Drawing::Size(46, 24);
			this->ammoStatusLBL->TabIndex = 8;
			this->ammoStatusLBL->Text = L"OFF";
			// 
			// UpdateTimer
			// 
			this->UpdateTimer->Enabled = true;
			this->UpdateTimer->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick_1);
			// 
			// CadenceLBL
			// 
			this->CadenceLBL->AutoSize = true;
			this->CadenceLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->CadenceLBL->ForeColor = System::Drawing::SystemColors::ButtonFace;
			this->CadenceLBL->Location = System::Drawing::Point(12, 156);
			this->CadenceLBL->Name = L"CadenceLBL";
			this->CadenceLBL->Size = System::Drawing::Size(274, 24);
			this->CadenceLBL->TabIndex = 11;
			this->CadenceLBL->Text = L"[F4] Increase Cadence:";
			// 
			// cadenceStatusLBL
			// 
			this->cadenceStatusLBL->AutoSize = true;
			this->cadenceStatusLBL->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cadenceStatusLBL->ForeColor = System::Drawing::Color::Red;
			this->cadenceStatusLBL->Location = System::Drawing::Point(310, 156);
			this->cadenceStatusLBL->Name = L"cadenceStatusLBL";
			this->cadenceStatusLBL->Size = System::Drawing::Size(46, 24);
			this->cadenceStatusLBL->TabIndex = 12;
			this->cadenceStatusLBL->Text = L"OFF";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(368, 279);
			this->Controls->Add(this->cadenceStatusLBL);
			this->Controls->Add(this->CadenceLBL);
			this->Controls->Add(this->autogunLBL);
			this->Controls->Add(this->recoilStatusLBL);
			this->Controls->Add(this->ammoStatusLBL);
			this->Controls->Add(this->automaticLBL);
			this->Controls->Add(this->recoilLBL);
			this->Controls->Add(this->ammoLBL);
			this->Controls->Add(this->DLLStatus);
			this->Controls->Add(this->TitleLBL);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
			 }			 	 
	private: System::Void timer1_Tick_1(System::Object^  sender, System::EventArgs^  e) 
			 {
				//MessageBoxA(NULL,"Bla","FuckU",MB_OK);
				//int a = (GetAsyncKeyState(VK_F1));
				//char b[10];
				//itoa(a,b,10);
				

				if(clock() - OnPressTMR > 400)
				{				  
				//System::String^ Loff = "Off";
				//MessageBox::Show("Bla1");
				//int a = (GetAsyncKeyState(VK_F1));
				//char b[10];
				//itoa(a,b,10);
				//MessageBoxA(NULL,b,"FuckU",MB_OK);
					
					/*-----------------------------------AMMO-----------------------------------*/
					if(GetAsyncKeyState(VK_F1))
					{
						OnPressTMR=clock();
						AmmoStatus = !AmmoStatus;
						if(AmmoStatus)
						{
						//MessageBox::Show("Bla2");
						ammoStatusLBL->Text = L"ON";
						ammoStatusLBL->ForeColor = System::Drawing::Color::Green;
						WriteToMemory(AmmoAddress, AmmoOpCode,2);
						}
						else 
						{
						ammoStatusLBL->Text = L"OFF";
						ammoStatusLBL->ForeColor = System::Drawing::Color::Red;
						WriteToMemory(AmmoAddress, AmmoDefaultOpCode,2);
						}
					}
					/*-----------------------------------RECOIL----------------------------------*/
					if(GetAsyncKeyState(VK_F2))
					{
						OnPressTMR=clock();
						RecoilStatus = !RecoilStatus;
						if(RecoilStatus)
						{
						//MessageBox::Show("Bla2");
						recoilStatusLBL->Text = L"ON";
						recoilStatusLBL->ForeColor = System::Drawing::Color::Green;

						for(int i=0; i<7;i++)
							 {
								 WriteToMemory(RecoilAddresses[i], StringToCharArr(Nops[NoOfBytes[i]-1]),NoOfBytes[i]);
							 }
						}
						else 
						{
						recoilStatusLBL->Text = L"OFF";
						recoilStatusLBL->ForeColor = System::Drawing::Color::Red;

						for(int i=0; i<7;i++)
							 {
								 WriteToMemory(RecoilAddresses[i], StringToCharArr(RecoilDefaultOpCode[i]),NoOfBytes[i]);
							 }
						}
					}
					/*-----------------------------------AUTOGUN--------------------------------*/
					if(GetAsyncKeyState(VK_F3))
					{
						OnPressTMR=clock();
						AutoGunStatus = !AutoGunStatus;
						if(AutoGunStatus)
						{
						//MessageBox::Show("Bla2");
						autogunLBL->Text = L"ON";
						autogunLBL->ForeColor = System::Drawing::Color::Green;
						WriteToMemory(AutoGunAddress, AutoGunCode,2);
						}
						else 
						{
						autogunLBL->Text = L"OFF";
						autogunLBL->ForeColor = System::Drawing::Color::Red;
						WriteToMemory(AutoGunAddress, AutoGunDefaultOpCode,2);
						}
					}
					/*-----------------------------------CADENCE----------------------------------*/
					if(GetAsyncKeyState(VK_F4))
					{
						OnPressTMR=clock();
						TimeStatus = !TimeStatus;
						if(TimeStatus)
						{
						//MessageBox::Show("Bla2");
						cadenceStatusLBL->Text = L"ON";
						cadenceStatusLBL->ForeColor = System::Drawing::Color::Green;

						WriteToMemory(TimeAddress, StringToCharArr(Nops[1]),2);
						}
						else 
						{
						cadenceStatusLBL->Text = L"OFF";
						cadenceStatusLBL->ForeColor = System::Drawing::Color::Red;

						WriteToMemory(TimeAddress, StringToCharArr(TimeDefaulOpCode),2);
						}
					}
				}
			}
			void WriteToMemory(DWORD addressToWrite, char* valueToWrite, int byteNum)
			 {
				 unsigned long oldProtection;
				 VirtualProtect((LPVOID)addressToWrite, byteNum, PAGE_EXECUTE_READWRITE,&oldProtection);
				 memcpy((LPVOID)addressToWrite,valueToWrite, byteNum);
				 VirtualProtect((LPVOID)addressToWrite, byteNum,oldProtection,NULL);
			 }
			 char *StringToCharArr(std::string strToConvert)
			 {
				 char *charRet = new char[strToConvert.length()+1];
				 std::strcpy(charRet, strToConvert.c_str());
				 return charRet;
			 }

}; 
}


