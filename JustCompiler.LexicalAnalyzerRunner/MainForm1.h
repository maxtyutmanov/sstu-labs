#pragma once

#include "CompilerFacade.h"
#include "Utils.h"
#include <sstream>

namespace JustCompilerLexicalAnalyzerRunner {
    
    using namespace std;
    using namespace System;
    using namespace System::Runtime::InteropServices;
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

    protected: 
    private: System::Windows::Forms::MenuStrip^  menuStrip1;
    private: System::Windows::Forms::ToolStripMenuItem^  Ù‡ÈÎToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  ‚˚ıÓ‰ToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem;

    private: System::Windows::Forms::RichTextBox^  sourceTxt;
    private: System::Windows::Forms::RichTextBox^  errorsTxt;

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
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->Ù‡ÈÎToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->‚˚ıÓ‰ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->sourceTxt = (gcnew System::Windows::Forms::RichTextBox());
            this->errorsTxt = (gcnew System::Windows::Forms::RichTextBox());
            this->menuStrip1->SuspendLayout();
            this->SuspendLayout();
            // 
            // menuStrip1
            // 
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->Ù‡ÈÎToolStripMenuItem});
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Size = System::Drawing::Size(600, 24);
            this->menuStrip1->TabIndex = 1;
            this->menuStrip1->Text = L"menuStrip1";
            // 
            // Ù‡ÈÎToolStripMenuItem
            // 
            this->Ù‡ÈÎToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem, 
                this->‚˚ıÓ‰ToolStripMenuItem});
            this->Ù‡ÈÎToolStripMenuItem->Name = L"Ù‡ÈÎToolStripMenuItem";
            this->Ù‡ÈÎToolStripMenuItem->Size = System::Drawing::Size(48, 20);
            this->Ù‡ÈÎToolStripMenuItem->Text = L"‘‡ÈÎ";
            // 
            // Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem
            // 
            this->Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem->Name = L"Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem";
            this->Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
            this->Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem->Text = L"“‡ÌÒÎËÓ‚‡Ú¸";
            this->Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem_Click);
            // 
            // ‚˚ıÓ‰ToolStripMenuItem
            // 
            this->‚˚ıÓ‰ToolStripMenuItem->Name = L"‚˚ıÓ‰ToolStripMenuItem";
            this->‚˚ıÓ‰ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
            this->‚˚ıÓ‰ToolStripMenuItem->Text = L"¬˚ıÓ‰";
            // 
            // sourceTxt
            // 
            this->sourceTxt->Dock = System::Windows::Forms::DockStyle::Top;
            this->sourceTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(204)));
            this->sourceTxt->Location = System::Drawing::Point(0, 24);
            this->sourceTxt->Name = L"sourceTxt";
            this->sourceTxt->Size = System::Drawing::Size(600, 275);
            this->sourceTxt->TabIndex = 3;
            this->sourceTxt->Text = L"";
            // 
            // errorsTxt
            // 
            this->errorsTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
                | System::Windows::Forms::AnchorStyles::Left) 
                | System::Windows::Forms::AnchorStyles::Right));
            this->errorsTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(204)));
            this->errorsTxt->Location = System::Drawing::Point(0, 305);
            this->errorsTxt->Name = L"errorsTxt";
            this->errorsTxt->Size = System::Drawing::Size(600, 64);
            this->errorsTxt->TabIndex = 4;
            this->errorsTxt->Text = L"";
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(600, 374);
            this->Controls->Add(this->errorsTxt);
            this->Controls->Add(this->sourceTxt);
            this->Controls->Add(this->menuStrip1);
            this->MainMenuStrip = this->menuStrip1;
            this->Name = L"MainForm";
            this->Text = L"“‡ÌÒÎˇÚÓ";
            this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {

             }
    private: System::Void Ú‡ÌÒÎËÓ‚‡Ú¸ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                 wstring sourceStr;
                 StringToStlWString(sourceTxt->Text, sourceStr);
                 wistringstream inputStream(sourceStr);
                 wostringstream outputStream;

                 CompilerFacade::Compile(inputStream, outputStream);

                 String^ errors = StlWStringToString(outputStream.str());

                 errorsTxt->Text = errors;
             }
};
}

