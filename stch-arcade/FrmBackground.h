#pragma once
#include "Controlador.h"

namespace stcharcade {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Background
	/// </summary>
	public ref class FrmBackground : public System::Windows::Forms::Form
	{
		public:
			FrmBackground(void)
			{
				InitializeComponent();

				/* Inicializamos las variables gráficas
				 * que nos permitirá crear gráficos donde
				 * le asignemos.
				*/
				gInfo = PnlInfo->CreateGraphics();
				gGame = PnlGame->CreateGraphics();

				/* Creamos un espacio que nos proporciona métodos para poder
				 * configurar nuestro bufer gráfico. Con el método allocate creo
				 * un contenedor bufer de gráficos con las dimensiones de nuestros paneles
				*/
				bfSpace = BufferedGraphicsManager::Current;
				bfInfo = bfSpace->Allocate(gInfo, PnlInfo->ClientRectangle);
				bfGame = bfSpace->Allocate(gGame, PnlGame->ClientRectangle);

				/* Inicializamos los mapas de bits con las rutas de la imagen */
				bmpInfo = gcnew Bitmap("resources/images/tablero.png");
				bmpMap = gcnew Bitmap("resources/images/background.png");

				/* Cargamos el controlador del juego */
				controlador = gcnew ControladorJuego();
			}

		protected:
			/// <summary>
			/// Limpiar los recursos que se estén usando.
			/// </summary>
			~FrmBackground()
			{
				if (components)
				{
					delete components;
				}
			}

		private: System::Windows::Forms::Panel^ PnlInfo;
		private: System::Windows::Forms::Panel^ PnlGame;
		private: System::Windows::Forms::Timer^ Loop;
		private: System::ComponentModel::IContainer^ components;
		private:
			Graphics^ gInfo;
			Graphics^ gGame;
			BufferedGraphicsContext^ bfSpace;
			BufferedGraphics^ bfInfo;
			BufferedGraphics^ bfGame;

			Bitmap^ bmpInfo;
			Bitmap^ bmpMap;

			ControladorJuego^ controlador;

		protected:
		protected:

		private:
			/// <summary>
			/// Variable del diseñador necesaria.
			/// </summary>


			#pragma region Windows Form Designer generated code
			/// <summary>
			/// Método necesario para admitir el Diseñador. No se puede modificar
			/// el contenido de este método con el editor de código.
			/// </summary>
			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				this->PnlInfo = (gcnew System::Windows::Forms::Panel());
				this->PnlGame = (gcnew System::Windows::Forms::Panel());
				this->Loop = (gcnew System::Windows::Forms::Timer(this->components));
				this->SuspendLayout();
				// 
				// PnlInfo
				// 
				this->PnlInfo->Location = System::Drawing::Point(0, 0);
				this->PnlInfo->Name = L"PnlInfo";
				this->PnlInfo->Size = System::Drawing::Size(1280, 125);
				this->PnlInfo->TabIndex = 0;
				// 
				// PnlGame
				// 
				this->PnlGame->Location = System::Drawing::Point(0, 125);
				this->PnlGame->Name = L"PnlGame";
				this->PnlGame->Size = System::Drawing::Size(1280, 595);
				this->PnlGame->TabIndex = 1;
				// 
				// Loop
				// 
				this->Loop->Enabled = true;
				this->Loop->Interval = 33;
				this->Loop->Tick += gcnew System::EventHandler(this, &FrmBackground::Loop_Tick);
				// 
				// FrmBackground
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(1280, 720);
				this->Controls->Add(this->PnlGame);
				this->Controls->Add(this->PnlInfo);
				this->Name = L"FrmBackground";
				this->Text = L"Background";
				this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FrmBackground::FrmBackground_KeyDown);
				this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FrmBackground::FrmBackground_KeyUp);
				this->ResumeLayout(false);

			}
			#pragma endregion

			#pragma region Events
			private: System::Void Loop_Tick(System::Object^ sender, System::EventArgs^ e) {
				bfInfo->Graphics->Clear(Color::White);
				bfInfo->Graphics->DrawImage(bmpInfo, 0, 0, 1281, 125);
				
				bfGame->Graphics->Clear(Color::White);
				bfGame->Graphics->DrawImage(bmpMap, 0, 0, 1281, 595);

				controlador->Mostrar(bfGame->Graphics);
				bfInfo->Render(gInfo);
				bfGame->Render(gGame);

				if (!controlador->Mover(gGame)) {
					this->Loop->Enabled = false;

					if (controlador->GetResultado()) 
						MessageBox::Show("GANASTE");
					else 
						MessageBox::Show("PERDISTE");

					this->Close();
				}
			}

			private: System::Void FrmBackground_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
				controlador->MovimientoJugador(true, e->KeyCode);

				if (e->KeyCode == Keys::Enter) {
					controlador->Habilitar_Aliados();
				}
			}

			private: System::Void FrmBackground_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
				controlador->MovimientoJugador(false, e->KeyCode);
			}
			#pragma endregion
	};
}
