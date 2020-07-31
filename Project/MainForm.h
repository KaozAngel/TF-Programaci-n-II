#pragma once
#include"Controller.h"
#include"NamesForm.h"
namespace Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		Controlador*controlador;
		Graphics^g;
		BufferedGraphicsContext^context;
		BufferedGraphics^buffer;
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  tmrGame;
	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->tmrGame = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// tmrGame
			// 
			this->tmrGame->Enabled = true;
			this->tmrGame->Tick += gcnew System::EventHandler(this, &MainForm::tmrGame_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::MainForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress);
			this->ResumeLayout(false);

		}
#pragma endregion
		void GoFullscreen(bool fullscreen)
		{
			if (fullscreen)
			{
				this->WindowState = FormWindowState::Normal;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				this->Bounds = Screen::PrimaryScreen->Bounds;
			}
			else
			{
				this->WindowState = FormWindowState::Maximized;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
			}
		}

	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		GoFullscreen(true);
		g = this->CreateGraphics();
		controlador = new Controlador(5, g);
		context = BufferedGraphicsManager::Current;
		buffer = context->Allocate(g, this->ClientRectangle);
		
	}
			

	private: System::Void MainForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		
		buffer->Graphics->Clear(Color::White);
		controlador->DibujarPantalla(buffer->Graphics);
		buffer->Render();
		
	}
	private: System::Void MainForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		
		
	}
	private: System::Void tmrGame_Tick(System::Object^  sender, System::EventArgs^  e) {
		buffer->Graphics->Clear(Color::White);
		controlador->DibujarPantalla(buffer->Graphics);
		buffer->Render();
	}
private: System::Void MainForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	int tecla = controlador->ProcesarTecla(e->KeyValue);
	if (tecla==0)
	{
		this->Close();
	}
	else if(tecla==2)
	{
		NamesForm^ nf = gcnew NamesForm(controlador);
		nf->ShowDialog();
	}
}
};
}
