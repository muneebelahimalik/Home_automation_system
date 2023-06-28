#include "cMain.h"
#include<Windows.h>
#include<string>

using namespace std;

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, LoadOn1)
EVT_BUTTON(10002, LoadOn2)
EVT_BUTTON(10003, LoadOn3)
EVT_BUTTON(10004, LoadOff1)
EVT_BUTTON(10005, LoadOff2)
EVT_BUTTON(10006, LoadOff3)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Home Automation using PC",wxDefaultPosition,wxSize(800,400))
{
	l1On = new wxButton(this, 10001, "ON", wxPoint(250, 50), wxSize(150, 50));

	l2On = new wxButton(this, 10002, "ON", wxPoint(250, 150), wxSize(150, 50));

	l3On = new wxButton(this, 10003, "ON", wxPoint(250, 250), wxSize(150, 50));

	l1Off = new wxButton(this, 10004, "OFF", wxPoint(550, 50), wxSize(150, 50));

	l2Off = new wxButton(this, 10005, "OFF", wxPoint(550, 150), wxSize(150, 50));

	l3Off = new wxButton(this, 10006, "OFF", wxPoint(550, 250), wxSize(150, 50));

	

	light = new wxStaticText(this, wxID_ANY, "Lights", wxPoint(100, 55));

	wxFont t_Font = light->GetFont();
	t_Font.SetPointSize(14);
	light->SetFont(t_Font);
	
	fan = new wxStaticText(this, wxID_ANY, "Fans", wxPoint(100, 155));

	t_Font = fan->GetFont();
	t_Font.SetPointSize(14);
	fan->SetFont(t_Font);

	other = new wxStaticText(this, wxID_ANY, "Other", wxPoint(100, 255));

	t_Font = other->GetFont();
	t_Font.SetPointSize(14);
	other->SetFont(t_Font);
}

cMain::~cMain()
{
}

void cMain::LoadOn1(wxCommandEvent& evt)
{
	serialComm("1");
}
void cMain::LoadOn2(wxCommandEvent& evt)
{
	serialComm("3");
}
void cMain::LoadOn3(wxCommandEvent& evt)
{
	serialComm("5");
}
void cMain::LoadOff1(wxCommandEvent& evt)
{
	serialComm("2");
}
void cMain::LoadOff2(wxCommandEvent& evt)
{
	serialComm("4");
}
void cMain::LoadOff3(wxCommandEvent& evt)
{
	serialComm("6");
}

void cMain::serialComm(LPCVOID input)
{
	string comNum = "COM1";
	// Open serial port
	HANDLE serialHandle;

	serialHandle = CreateFileA(comNum.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);

	GetCommState(serialHandle, &serialParams);
	serialParams.BaudRate = 9600;
	serialParams.ByteSize = 1;
	serialParams.StopBits = TWOSTOPBITS;
	serialParams.Parity = NOPARITY;
	SetCommState(serialHandle, &serialParams);

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;

	SetCommTimeouts(serialHandle, &timeout);

	WriteFile(serialHandle, input, 1, nullptr, nullptr);

	CloseHandle(serialHandle);


}