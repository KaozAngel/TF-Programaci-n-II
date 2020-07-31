#pragma once

#include"Controller.h"

namespace Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NamesForm
	/// </summary>
	public ref class NamesForm : public System::Windows::Forms::Form
	{
	private:
		Controlador*controlador;
		cli::array<TextBox^>^names;
		cli::array<Label^>^labels ;
	public:
		NamesForm(Controlador*c) 
		{
			InitializeComponent();
			this->controlador = c;
		}
		NamesForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NamesForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:






	private: System::Windows::Forms::Button^  btnAceptar;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnAceptar = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnAceptar
			// 
			this->btnAceptar->Location = System::Drawing::Point(159, 277);
			this->btnAceptar->Name = L"btnAceptar";
			this->btnAceptar->Size = System::Drawing::Size(75, 23);
			this->btnAceptar->TabIndex = 7;
			this->btnAceptar->Text = L"Aceptar";
			this->btnAceptar->UseVisualStyleBackColor = true;
			this->btnAceptar->Click += gcnew System::EventHandler(this, &NamesForm::btnAceptar_Click);
			// 
			// NamesForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(352, 342);
			this->Controls->Add(this->btnAceptar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"NamesForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"NamesForm";
			this->Load += gcnew System::EventHandler(this, &NamesForm::NamesForm_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &NamesForm::NamesForm_KeyPress);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void NamesForm_Load(System::Object^  sender, System::EventArgs^  e) {

		int num = controlador->getNumJugadores();

		names= gcnew cli::array<TextBox^>(num);
		labels= gcnew cli::array<Label^>(num);


		for (int i = 0; i < num; i++)
		{
			names[i] = gcnew TextBox();
			labels[i] = gcnew Label();
		}

		int x = this->ClientRectangle.Width / 2;
		int y = this->ClientRectangle.Height / 2;

		for (int i = 0; i < num; i++) 
		{
			names[i]->Width = 100;
			names[i]->Height = 20;
			labels[i]->Width = 100;
			labels[i]->Height = 15;
			int px = names[i]->Size.Width / 2;
			int py = names[i]->Size.Height;
			names[i]->Location = Point(x - px, y - num * py+(40*i));
			labels[i]->Location = Point(x-px, y -(num * py)-20+(40*i));
			names[i]->Name = "txtJugador" + (i+1);
			labels[i]->Text = "Jugador " + (i + 1);
			this->Controls->Add(names[i]);
			this->Controls->Add(labels[i]);
		}	
		int bx = names[names->Length - 1]->Location.X;
		int by= names[names->Length - 1]->Location.Y;
		btnAceptar->Location = Point(bx,by+20);
	}
	private: System::Void btnAceptar_Click(System::Object^  sender, System::EventArgs^  e) {
		int num = controlador->getNumJugadores();
		cli::array<String^>^stringNames = gcnew cli::array<String^>(num);
		bool good = true;
		for (int i = 0; i < num; i++) 
		{
			String ^s = names[i]->Text;
			if (String::IsNullOrEmpty(s)) 
			{
				MessageBox::Show("Ingrese todos los datos");
				good = false;
				break;
			}
			stringNames[i] = s;
		}
		if (good) 
		{
			controlador->getTablero()->setNames(stringNames);
			this->Close();
		}
		
	}
private: System::Void NamesForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == char(Keys::Escape)) 
	{
		this->Close();
	}
}
};
}
