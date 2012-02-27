Jedno "ale", Tlen afair jest napisany w BCB, który podczas zapisywania
do pliku zaokr¹gla struktury œmieciami do Mod 4 rozmiaru. St¹d w tym co
napiszê bêd¹ char[] nic nie znacz¹ce.
No wiêc najpierw sms'y i wiadomoœci - tam odczyt jest banalny. Dostajesz
offset i d³ugoœæ co przeczytaæ [chocia¿ mo¿na te¿ do \0]

Struktura dla SMS:

char[12] - #gsm
char[4] - smieci
date - [standardowy double]
char[4] - nic
int - offset
int - dlugosc
char[4] - nic

Wiadomoœci:

char[26] - ID [w Tlen'ie maksymalna d³ugoœæ loginu to 25 + miejsce \0]
char[6] - nic
date
fromme - bool kto wys³a³ wiadomoœæ
char[3] - nic
int - offset
int - dlugosc
char[4] - nic

login jest bez @tlen.pl
Dlatego by³ problem z pluginem jabber'a - nie móg³ korzystaæ z archiwum
bo gdzie zapamiêtaæ server.


W pliku indexowym rozmów jest:

char[26] - ID
char[6] - nic
date
char[4] - nic
int - offset
int - index, ka¿da rozmowa ma swój numer [nie pamiêtam czy od 0 czy od 1
zaczyna liczyæ, ale to nie ma znaczenia]
Przez to ¿e Tlen zapisuje na bie¿¹co ka¿d¹ wypowiedŸ ka¿dy msg w
rozmowie te¿ ma swój nag³ówek, taki:

date
fromme - bool/char
deleted - bool/char, jeœli != 0 wtedy wiadomoœæ ma byæ pominiêta przy
czytaniu
char[2] - nic
int - length [tej pojedynczej wiadomoœci]
int - index [rozmowy do której nale¿y]
char[4] - nic

to jest struktura która jest przed ka¿d¹ wypowiedzi¹.

Struktura w indexie rozmów - 56 bajtów, ka¿da wiadomoœæ w rozmowie - 24,
wiadomoœci pojedyncze - 56, sms - 40.

co do smsów - w³aœnie sprawdzi³em, s¹ w archiwum, natomiast PowerArchiwe
pokazuje je wszystkie jako wys³ane - oryginalne archiwum rozró¿nia
wys³¹ne i odebrane
Widocznie wykorzystali któryœ z nieu¿ywanych bajtów, bêdziesz musia³ to
ju¿ rozgryŸæ sam.

W .idx wiadomoœci [pojedynczych] i sms'ów masz wszystkie oñ informacje.
Pliki .dat to tylko treœci + /0

Natomiast .idx rozmów zawiera ogólne informacje o rozmowie - datê, z
kim, ile wypowiedzi, offset pierwszej wiadomoœci, etc. Dlatego Tlen
kiedy otwiera archiwum nie dotyka na pocz¹tek .dat tylko wyœwietla listê
na podstawie samej zawartoœci .idx