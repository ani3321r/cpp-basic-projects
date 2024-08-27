//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "tic_tac_toe.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner), xScore(0), oScore(0), currPlayerSym('x')
{
    currPlayerSymLabel->Text = currPlayerSym;
    xScoreLabel->Text = "X: " + IntToStr(xScore);
    oScoreLabel->Text = "O: " + IntToStr(oScore);

    // Assign the ButtonClick handler to all buttons
    Button1->OnClick = ButtonClick;
    Button2->OnClick = ButtonClick;
    Button3->OnClick = ButtonClick;
    Button4->OnClick = ButtonClick;
    Button5->OnClick = ButtonClick;
    Button6->OnClick = ButtonClick;
    Button7->OnClick = ButtonClick;
    Button8->OnClick = ButtonClick;
	Button9->OnClick = ButtonClick;

    playAgainButton->OnClick = playAgainButtonClick;
}


void TForm1::UpdateScores() {
    if (currPlayerSym == 'x') {
        xScore++;
    } else {
        oScore++;
    }
	xScoreLabel->Text = "X: " + IntToStr(xScore);
    oScoreLabel->Text = "O: " + IntToStr(oScore);
}

void __fastcall TForm1::playAgainButtonClick(TObject *Sender)
{
    ResetGame();
}

bool TForm1::CheckIsWinner() {
    if (!Button1->Text.IsEmpty() && Button1->Text == Button2->Text && Button1->Text == Button3->Text)
        return true;
    if (!Button4->Text.IsEmpty() && Button4->Text == Button5->Text && Button4->Text == Button6->Text)
        return true;
    if (!Button7->Text.IsEmpty() && Button7->Text == Button8->Text && Button7->Text == Button9->Text)
        return true;
    if (!Button1->Text.IsEmpty() && Button1->Text == Button4->Text && Button1->Text == Button7->Text)
        return true;
    if (!Button2->Text.IsEmpty() && Button2->Text == Button5->Text && Button2->Text == Button8->Text)
        return true;
    if (!Button3->Text.IsEmpty() && Button3->Text == Button6->Text && Button3->Text == Button9->Text)
        return true;
    if (!Button1->Text.IsEmpty() && Button1->Text == Button5->Text && Button1->Text == Button9->Text)
        return true;
    if (!Button3->Text.IsEmpty() && Button3->Text == Button5->Text && Button3->Text == Button7->Text)
        return true;

    return false;
}

void TForm1::DisableButtons() {
    Button1->Enabled = false;
    Button2->Enabled = false;
    Button3->Enabled = false;
    Button4->Enabled = false;
    Button5->Enabled = false;
    Button6->Enabled = false;
    Button7->Enabled = false;
    Button8->Enabled = false;
    Button9->Enabled = false;
}


void TForm1::ResetGame() {
    Button1->Text = "";
    Button2->Text = "";
    Button3->Text = "";
    Button4->Text = "";
    Button5->Text = "";
    Button6->Text = "";
    Button7->Text = "";
    Button8->Text = "";
    Button9->Text = "";

    Button1->Enabled = true;
    Button2->Enabled = true;
    Button3->Enabled = true;
    Button4->Enabled = true;
    Button5->Enabled = true;
    Button6->Enabled = true;
    Button7->Enabled = true;
    Button8->Enabled = true;
    Button9->Enabled = true;

    currPlayerSym = 'x';  // Reset to 'x'
    currPlayerSymLabel->Text = currPlayerSym;

    winLabel->Text = "";
}

void TForm1::ButtonClick(TObject *Sender)
{
    TButton* clickedButton = dynamic_cast<TButton*>(Sender);
    if (clickedButton->Text.IsEmpty()) {
        clickedButton->Text = currPlayerSym;

        if(CheckIsWinner()){
            winLabel->Text = "Player " + String(currPlayerSym) + " wins!";
            UpdateScores();
            DisableButtons();
            return;
        }

        currPlayerSym = (currPlayerSym == 'x') ? 'o' : 'x';  // Toggle player
        currPlayerSymLabel->Text = currPlayerSym;
    }
}

//---------------------------------------------------------------------------
