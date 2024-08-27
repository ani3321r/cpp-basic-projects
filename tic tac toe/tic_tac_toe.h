//---------------------------------------------------------------------------

#ifndef tic_tac_toeH
#define tic_tac_toeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TLabel *currPlayerSymLabel;
	TLabel *xScoreLabel;
	TLabel *oScoreLabel;
	TLabel *winLabel;
	TButton *playAgainButton;
    void __fastcall ButtonClick(TObject *Sender);
	void __fastcall playAgainButtonClick(TObject *Sender);
private:	// User declarations
    bool CheckIsWinner();
    void DisableButtons();
    void UpdateScores();
    void ResetGame();
    int xScore;
    int oScore;
	char currPlayerSym;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
