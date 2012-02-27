#include "StdAfx.h"
#include "ConsoleWriter.h"

ConsoleWriter::ConsoleWriter(void)
{
}

ConsoleWriter::~ConsoleWriter(void)
{
}

//przygotowuje archiwum do zapisu
bool ConsoleWriter::Prepare(void* params)
{
	printf("ConsoleWriter::Prepare\n");
	return true;
}
//ustawia UID w³aœcieciela
void ConsoleWriter::setOwnerUID(char* UID)
{
	printf("ConsoleWriter::setOwnerUID(%s)\n", UID);
}
// ustawia czas odebrania aktualnej wiadomosci
void ConsoleWriter::setMsgTime(cTime64 time)
{
	printf("ConsoleWriter::setMsgTime(%s)\n", time.strftime("%c").c_str());
}
// nadawca aktualnej wiadomosci
void ConsoleWriter::setMsgSenderUID(char* UID)
{
	printf("ConsoleWriter::setMsgSenderUID(%s)\n", UID);
}
// odbiorca aktualnej wiadomosci
void ConsoleWriter::setMsgReceiverUID(char* UID)
{
	printf("ConsoleWriter::setMsgRecieverUID(%s)\n", UID);
}
// tekst aktualnie prztwarzanej wiadomosci
void ConsoleWriter::setMsgText(char* text)
{
	printf("ConsoleWriter::setMsgText(%s)\n", text);
}
// true jeœli wiadomoœæ wys³ana, false jeœli odebrana
void ConsoleWriter::setMsgWasSent(bool was)
{
	printf("ConsoleWriter::setMsgWasSent(%d)\n", was);
}
//dodaje aktualn¹ wiadomoœæ
//zwraca true jeœli wszystko posz³o dobrze
bool ConsoleWriter::addMsg(void)
{
	printf("ConsoleWriter::addMsg(void)\n");
	return true;
}
