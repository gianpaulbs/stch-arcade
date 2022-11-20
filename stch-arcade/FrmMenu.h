#pragma once
#include "FrmBackground.h"

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
				bmpMenu = gcnew Bitmap("resources/images/fondo3.png");
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

			String^ pathSprite_Jugar;
			String^ pathSprite_Instrucciones;
			String^ pathSprite_Creditos;

			int posXTitulo = -725;
			int posYTitulo = -50;
			bool playAnimation_Title = true;
			bool playAnimationVertical_Title = false;
			bool playAnimationHorizontal_Title = true;

			int indexButtons_Menu = 1;
			bool viewScreenMenu = true;
			bool viewScreenInstructions = false;
			bool viewScreenCredits = false;

			int posYCredits_G = -250;
			int posYCredits_J = -230;
			int posYCredits_D = 680;

			int posXInstr_W = -210;
			int posXInstr_Q = -85;
			int posXInstr_E = -180;

			int ventaja;
			int dificultad;
			int indexButtons_Play = 1;
			bool viewScreenPlayGame = false;
			bool viewChooseVentaja = true;
			bool viewChooseDifficulty = false;

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

			void Liberar_Memoria() {
				//delete bmpTitulo;
				//delete bmpMenu;
				delete bmpCopyright;
			}

			void Animation_Cursor() {
				Bitmap^ bmpCursor = gcnew Bitmap("resources/images/cursor.png");
				Bitmap^ bmpDesc_V1 = gcnew Bitmap("resources/images/descventa1.png");
				Bitmap^ bmpDesc_V2 = gcnew Bitmap("resources/images/descventa2.png");
				Bitmap^ bmpDesc_L1 = gcnew Bitmap("resources/images/desclevel1.png");
				Bitmap^ bmpDesc_L2 = gcnew Bitmap("resources/images/desclevel2.png");

				switch (indexButtons_Play) {
				case 1:
					bfMenu->Graphics->DrawImage(bmpCursor, 255, 330, 90, 90);

					if (viewChooseVentaja)
						bfMenu->Graphics->DrawImage(bmpDesc_V1, 360, 480, 540, 40);

					if (viewChooseDifficulty)
						bfMenu->Graphics->DrawImage(bmpDesc_L1, 230, 480, 750, 40);

					break;
				case 2:
					bfMenu->Graphics->DrawImage(bmpCursor, 885, 330, 90, 90);

					if (viewChooseVentaja)
						bfMenu->Graphics->DrawImage(bmpDesc_V2, 360, 480, 540, 40);

					if (viewChooseDifficulty)
						bfMenu->Graphics->DrawImage(bmpDesc_L2, 230, 480, 750, 40);
					break;
				}

				delete bmpCursor;
				delete bmpDesc_V1;
				delete bmpDesc_V2;
				delete bmpDesc_L1;
				delete bmpDesc_L2;
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
				viewScreenMenu = false;
				if (indexButtons_Menu == 1) viewScreenPlayGame = true;
				if (indexButtons_Menu == 2) viewScreenInstructions = true;
				if (indexButtons_Menu == 3) viewScreenCredits = true;
			}

			void ScreenChooseVentaja() {
				Bitmap^ bmpVentajas = gcnew Bitmap("resources/images/ventajas.png");
				Bitmap^ bmpCubeta = gcnew Bitmap("resources/images/cubeta.png");
				Bitmap^ bmpMedicina = gcnew Bitmap("resources/images/medicina.png");
				Bitmap^ bmpx3_C = gcnew Bitmap("resources/images/x3.png");
				Bitmap^ bmpx3_M = gcnew Bitmap("resources/images/x3.png");

				bfMenu->Graphics->DrawImage(bmpVentajas, 480, 50, 300, 60);
				bfMenu->Graphics->DrawImage(bmpCubeta, 210, 250, 120, 130);
				bfMenu->Graphics->DrawImage(bmpx3_C, 350, 300, 80, 60);
				bfMenu->Graphics->DrawImage(bmpMedicina, 840, 250, 120, 130);
				bfMenu->Graphics->DrawImage(bmpx3_M, 980, 300, 80, 60);

				delete bmpVentajas;
				delete bmpCubeta;
				delete bmpMedicina;
				delete bmpx3_C;
				delete bmpx3_M;
			}

			void ScreenChooseDifficulty() {
				Bitmap^ bmpDificultad = gcnew Bitmap("resources/images/dificultad.png");
				Bitmap^ bmpBueno = gcnew Bitmap("resources/images/picardia.png");
				Bitmap^ bmpMalo = gcnew Bitmap("resources/images/llorando.png");

				bfMenu->Graphics->DrawImage(bmpDificultad, 480, 50, 300, 60);
				bfMenu->Graphics->DrawImage(bmpBueno, 180, 220, 230, 170);
				bfMenu->Graphics->DrawImage(bmpMalo, 830, 220, 170, 170);

				delete bmpDificultad;
				delete bmpBueno;
				delete bmpMalo;
			}

			void Load_ScreenPlayGame() {
				if (viewChooseVentaja) ScreenChooseVentaja();
				if (viewChooseDifficulty) ScreenChooseDifficulty();

				Animation_Cursor();
			}

			void Load_ScreenInstructions() {
				Bitmap^ bmpWASD = gcnew Bitmap("resources/images/wasd.png");
				Bitmap^ bmpQ = gcnew Bitmap("resources/images/q.png");
				Bitmap^ bmpEnter = gcnew Bitmap("resources/images/enter2.png");
				Bitmap^ bmpDescriptionWASD = gcnew Bitmap("resources/images/descriptionwasd.png");
				Bitmap^ bmpDescriptionQ = gcnew Bitmap("resources/images/descriptionq.png");
				Bitmap^ bmpDescriptionEnter = gcnew Bitmap("resources/images/descriptionenter.png");

				bfMenu->Graphics->DrawImage(bmpWASD, posXInstr_W, 85, 210, 150);
				bfMenu->Graphics->DrawImage(bmpQ, posXInstr_Q, 310, 80, 80);
				bfMenu->Graphics->DrawImage(bmpEnter, posXInstr_E, 475, 175, 85);

				if (posXInstr_W <= 120) posXInstr_W += 20;
				else bfMenu->Graphics->DrawImage(bmpDescriptionWASD, 445, 145, 680, 30);

				if (posXInstr_Q <= 185) posXInstr_Q += 20;
				else bfMenu->Graphics->DrawImage(bmpDescriptionQ, 445, 330, 440, 30);

				if (posXInstr_E <= 140) posXInstr_E += 20;
				else bfMenu->Graphics->DrawImage(bmpDescriptionEnter, 445, 500, 420, 30);

				delete bmpWASD;
				delete bmpQ;
				delete bmpEnter;
				delete bmpDescriptionWASD;
				delete bmpDescriptionQ;
				delete bmpDescriptionEnter;
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
				indexButtons_Play = 1;
				indexButtons_Menu = 1;

				posXTitulo = -725;
				posYTitulo = -50;

				viewScreenMenu = true;
				viewScreenPlayGame = false;
				viewScreenInstructions = false;
				viewScreenCredits = false;

				viewChooseVentaja = true;
				viewChooseDifficulty = false;

				playAnimationVertical_Title = false;
				playAnimationHorizontal_Title = true;
				playAnimation_Title = true;

				posYCredits_G = -250;
				posYCredits_J = -230;
				posYCredits_D = 680;

				posXInstr_W = -210;
				posXInstr_Q = -85;
				posXInstr_E = -180;

				ventaja = 1;
				dificultad = 1;
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
				if (viewScreenPlayGame)
					Load_ScreenPlayGame();
				
				if (viewScreenInstructions) 
					Load_ScreenInstructions();
				
				if (viewScreenCredits) 
					Load_ScreenCredits();

				bfMenu->Render(gMenu);
			}

			private: System::Void FrmMenu_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
				if (viewScreenMenu) {
					if (e->KeyCode == Keys::Space)
						posXTitulo = 185;

					if (posXTitulo != 185) return;

					if (e->KeyCode == Keys::Up && indexButtons_Menu > 1)
						indexButtons_Menu--;

					if (e->KeyCode == Keys::Down && indexButtons_Menu < 3)
						indexButtons_Menu++;

					switch (indexButtons_Menu) {
						case 1: Habilitar_BtnJugar(); break;
						case 2: Habilitar_BtnInstrucciones(); break;
						case 3: Habilitar_BtnCreditos(); break;
					}

					if (e->KeyCode == Keys::Enter) {
						Transicion_Pantallas();
						return;
					}

					if (e->KeyCode == Keys::Escape)
						Application::Exit();
				}

				if (viewScreenPlayGame) {
					if (e->KeyCode == Keys::Left && indexButtons_Play > 1)
						indexButtons_Play--;

					if (e->KeyCode == Keys::Right && indexButtons_Play < 2)
						indexButtons_Play++;

					if (e->KeyCode == Keys::Enter && viewChooseVentaja) {
						ventaja = indexButtons_Play;
						indexButtons_Play = 1;
						viewChooseVentaja = false;
						viewChooseDifficulty = true;
						return;
					}

					if (e->KeyCode == Keys::Enter && viewChooseDifficulty) {
						dificultad = indexButtons_Play;
						
						Loop->Enabled = false;
						FrmMenu::Visible = false;

						FrmBackground^ frmBackground = gcnew FrmBackground(ventaja, dificultad);
						frmBackground->ShowDialog();

						Reiniciar_Menu();
						Loop->Enabled = true;
						FrmMenu::Visible = true;
					}
				}
				
				if (e->KeyCode == Keys::Escape &&
					(viewScreenPlayGame || viewScreenInstructions || viewScreenCredits))
					Reiniciar_Menu();

				bfMenu->Render(gMenu);
			}
			#pragma endregion
	};
}
