#pragma once
namespace stcharcade {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de FrmMenu
	/// </summary>
	public ref class FrmMenu : public System::Windows::Forms::Form
	{
		public:
			FrmMenu(void)
			{
				InitializeComponent();

				/* Inicializamos las variables gráficas
				 * que nos permitirá crear gráficos donde
				 * le asignemos.
				*/
				gMenu = PnlMenu->CreateGraphics();

				/* Creamos un espacio que nos proporciona métodos para poder
				 * configurar nuestro bufer gráfico. Con el método allocate creo
				 * un contenedor bufer de gráficos con las dimensiones de nuestros paneles
				*/
				bfSpace = BufferedGraphicsManager::Current;
				bfMenu = bfSpace->Allocate(gMenu, PnlMenu->ClientRectangle);

				/* Inicializamos los mapas de bits con las rutas de la imagen */
				bmpMenu = gcnew Bitmap("resources/images/fondo.jpg");
				bmpTitulo = gcnew Bitmap("resources/images/titulo.png");
				bmpCopyright = gcnew Bitmap("resources/images/copyright.png");

				/* Inicializamos los string para definir las rutas por defecto */
				pathSprite_Jugar = "resources/images/jugaron.png";
				pathSprite_Instrucciones = "resources/images/instruccionesoff.png";
				pathSprite_Creditos = "resources/images/creditosoff.png";
			}

		protected:
			/// <summary>
			/// Limpiar los recursos que se estén usando.
			/// </summary>
			~FrmMenu()
			{
				if (components)
				{
					delete components;
				}
			}

		private: System::Windows::Forms::Panel^ PnlMenu;
		private: System::Windows::Forms::Timer^ Loop;
		private: System::ComponentModel::IContainer^ components;
		private:
			Graphics^ gMenu;
			BufferedGraphicsContext^ bfSpace;
			BufferedGraphics^ bfMenu;
			
			Bitmap^ bmpTitulo;
			Bitmap^ bmpMenu;
			Bitmap^ bmpCopyright;
			Bitmap^ bmpBtnSalir;

			String^ pathSprite_Jugar;
			String^ pathSprite_Instrucciones;
			String^ pathSprite_Creditos;
			
			int indexButtons = 1;
			bool viewScreenPlayGame = false;
			bool viewScreenInstructions = false;
			bool viewScreenCredits = false;

			int posXTitulo = -725;
			int posYTitulo = -50;
			bool playAnimation_Title = true;
			bool playAnimationVertical_Title = false;
			bool playAnimationHorizontal_Title = true;

			int posYCredits_G = -250;
			int posYCredits_J = -230;
			int posYCredits_D = 680;

			bool Animacion_Titulo() {
				bfMenu->Graphics->DrawImage(bmpTitulo, posXTitulo, posYTitulo, 900, 500);
				
				if (posXTitulo == 185) {
					playAnimationHorizontal_Title = false;
					playAnimation_Title = playAnimationHorizontal_Title;
				}

				if (posYTitulo == -420) {
					playAnimationVertical_Title = false;
					playAnimation_Title = playAnimationVertical_Title;
				}

				if (playAnimationHorizontal_Title)
					posXTitulo += 10;

				if (playAnimationVertical_Title)
					posYTitulo -= 40;
				
				return playAnimation_Title;
			}

			void Cargar_Botones() {
				Bitmap^ bmpBtnJugar = gcnew Bitmap(pathSprite_Jugar);
				Bitmap^ bmpBtnInstrucciones = gcnew Bitmap(pathSprite_Instrucciones);
				Bitmap^ bmpBtnCreditos = gcnew Bitmap(pathSprite_Creditos);

				bfMenu->Graphics->DrawImage(bmpBtnJugar, 530, 405, 190, 65);
				bfMenu->Graphics->DrawImage(bmpBtnInstrucciones, 417, 485, 410, 65);
				bfMenu->Graphics->DrawImage(bmpBtnCreditos, 484, 562, 280, 60);

				delete bmpBtnJugar;
				delete bmpBtnInstrucciones;
				delete bmpBtnCreditos;
			}
			
			void Transicion_Pantallas(){
				playAnimationVertical_Title = true;
				if (indexButtons == 1) viewScreenPlayGame = true;
				if (indexButtons == 2) viewScreenInstructions = true;
				if (indexButtons == 3) viewScreenCredits = true;
			}

			void Load_ScreenPlayGame() {

			}

			void Load_ScreenInstructions() {

			}

			void Load_ScreenCredits() {
				Bitmap^ bmpProfileGianpaul = gcnew Bitmap("resources/images/gbernal.png");
				Bitmap^ bmpProfileDaniella = gcnew Bitmap("resources/images/daniella.png");
				Bitmap^ bmpProfileJoaquin = gcnew Bitmap("resources/images/joaquin.png");
				Bitmap^ bmpNameGianpaul = gcnew Bitmap("resources/images/gianpaulbernal.png");
				Bitmap^ bmpNameDaniella = gcnew Bitmap("resources/images/daniellavargas.png");
				Bitmap^ bmpNameJoaquin = gcnew Bitmap("resources/images/joaquinruiz.png");

				bfMenu->Graphics->DrawImage(bmpProfileGianpaul, 150, posYCredits_G, 250, 250);

				bfMenu->Graphics->DrawImage(bmpProfileDaniella, 510, posYCredits_D, 230, 230);
				
				bfMenu->Graphics->DrawImage(bmpProfileJoaquin, 880, posYCredits_J, 230, 230);

				/* G y J = 55 y 75, 370 */
				//if ()

				if (posYCredits_G <= 55) posYCredits_G += 15;
				else bfMenu->Graphics->DrawImage(bmpNameGianpaul, 132, 330, 275, 20);

				if (posYCredits_J <= 75) posYCredits_J += 15;
				else bfMenu->Graphics->DrawImage(bmpNameJoaquin, 875, 330, 245, 20);

				if (posYCredits_D >= 370) posYCredits_D -= 15;
				else bfMenu->Graphics->DrawImage(bmpNameDaniella, 505, 610, 275, 20);

				delete bmpProfileGianpaul;
				delete bmpProfileDaniella;
				delete bmpProfileJoaquin;
				delete bmpNameGianpaul;
				delete bmpNameDaniella;
				delete bmpNameJoaquin;
			}

			void Reiniciar_Menu() {
				indexButtons = 1;

				posXTitulo = -725;
				posYTitulo = -50;

				viewScreenPlayGame = false;
				viewScreenInstructions = false;
				viewScreenCredits = false;

				playAnimationVertical_Title = false;
				playAnimationHorizontal_Title = true;
				playAnimation_Title = true;

				posYCredits_G = -250;
				posYCredits_J = -230;
				posYCredits_D = 680;
			}

			void Habilitar_BtnJugar() {
				pathSprite_Jugar = "resources/images/jugaron.png";
				pathSprite_Instrucciones = "resources/images/instruccionesoff.png";
				pathSprite_Creditos = "resources/images/creditosoff.png";
			}

			void Habilitar_BtnInstrucciones() {
				pathSprite_Jugar = "resources/images/jugaroff.png";
				pathSprite_Instrucciones = "resources/images/instruccioneson.png";
				pathSprite_Creditos = "resources/images/creditosoff.png";
			}

			void Habilitar_BtnCreditos() {
				pathSprite_Jugar = "resources/images/jugaroff.png";
				pathSprite_Instrucciones = "resources/images/instruccionesoff.png";
				pathSprite_Creditos = "resources/images/creditoson.png";
			}

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
				this->PnlMenu = (gcnew System::Windows::Forms::Panel());
				this->Loop = (gcnew System::Windows::Forms::Timer(this->components));
				this->SuspendLayout();
				// 
				// PnlMenu
				// 
				this->PnlMenu->BackColor = System::Drawing::Color::Transparent;
				this->PnlMenu->Location = System::Drawing::Point(0, 0);
				this->PnlMenu->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				this->PnlMenu->Name = L"PnlMenu";
				this->PnlMenu->Size = System::Drawing::Size(1920, 1049);
				this->PnlMenu->TabIndex = 0;
				this->PnlMenu->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FrmMenu::PnlMenu_Paint);
				// 
				// Loop
				// 
				this->Loop->Enabled = true;
				this->Loop->Interval = 33;
				this->Loop->Tick += gcnew System::EventHandler(this, &FrmMenu::Loop_Tick);
				// 
				// FrmMenu
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(1920, 1049);
				this->Controls->Add(this->PnlMenu);
				this->Name = L"FrmMenu";
				this->Text = L"FrmMenu";
				this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FrmMenu::FrmMenu_KeyDown);
				this->ResumeLayout(false);

			}
			#pragma endregion

			#pragma region Events
			private: System::Void Loop_Tick(System::Object^ sender, System::EventArgs^ e) {
				bfMenu->Graphics->Clear(Color::White);
				bfMenu->Graphics->DrawImage(bmpMenu, 0, 0, 1281, 683);

				if (!Animacion_Titulo() && 
					!viewScreenPlayGame &&
					!viewScreenInstructions &&
					!viewScreenCredits) {
					Cargar_Botones();
					bfMenu->Graphics->DrawImage(bmpCopyright, 7, 660, 380, 15);
				}

				/* Visualización de distintas pantallas en el menú */
				if (viewScreenPlayGame) Load_ScreenPlayGame();
				if (viewScreenInstructions) Load_ScreenInstructions();
				if (viewScreenCredits) Load_ScreenCredits();

				bfMenu->Render(gMenu);
			}

			private: System::Void FrmMenu_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
				if (e->KeyCode == Keys::Space) 
					posXTitulo = 185;

				if (posXTitulo != 185) return;

				if (e->KeyCode == Keys::Up && indexButtons > 1) 
					indexButtons--;
				
				if (e->KeyCode == Keys::Down && indexButtons < 3) 
					indexButtons++;

				switch (indexButtons) {
					case 1: Habilitar_BtnJugar(); break;
					case 2: Habilitar_BtnInstrucciones(); break;
					case 3: Habilitar_BtnCreditos(); break;
				}

				if (e->KeyCode == Keys::Enter) Transicion_Pantallas();

				if (e->KeyCode == Keys::Escape && 
					(viewScreenPlayGame || viewScreenInstructions || viewScreenCredits))
					Reiniciar_Menu();

				bfMenu->Render(gMenu);
			}
			#pragma endregion
	private: System::Void PnlMenu_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
};
}
