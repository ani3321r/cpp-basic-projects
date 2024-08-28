//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	RemainderTimer->Enabled = false;
}
const int MillisecondsPerDay=86400000;
//---------------------------------------------------------------------------
void __fastcall TForm1::setRemainderBtnClick(TObject *Sender)
{
	TDate remainderDate = RemainderDate->Date;
	TTime remainderTime = RemainderTime->Time;

	TDateTime remainderDateTime = remainderDate + remainderTime;

	TDateTime remainingTime = remainderDateTime - Now();

	double remainingTimeInMilliseconds =
					static_cast<double>(remainingTime)*MillisecondsPerDay;

	RemainderTimer->Interval = remainingTimeInMilliseconds;
	RemainderTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RemainderTimerTimer(TObject *Sender)
{
	RemainderTimer->Enabled = false;
	ShowMessage(RemainderMessage->Text);
}
//---------------------------------------------------------------------------
