Jedno "ale", Tlen afair jest napisany w BCB, kt�ry podczas zapisywania
do pliku zaokr�gla struktury �mieciami do Mod 4 rozmiaru. St�d w tym co
napisz� b�d� char[] nic nie znacz�ce.
No wi�c najpierw sms'y i wiadomo�ci - tam odczyt jest banalny. Dostajesz
offset i d�ugo�� co przeczyta� [chocia� mo�na te� do \0]

Struktura dla SMS:

char[12] - #gsm
char[4] - smieci
date - [standardowy double]
char[4] - nic
int - offset
int - dlugosc
char[4] - nic

Wiadomo�ci:

char[26] - ID [w Tlen'ie maksymalna d�ugo�� loginu to 25 + miejsce \0]
char[6] - nic
date
fromme - bool kto wys�a� wiadomo��
char[3] - nic
int - offset
int - dlugosc
char[4] - nic

login jest bez @tlen.pl
Dlatego by� problem z pluginem jabber'a - nie m�g� korzysta� z archiwum
bo gdzie zapami�ta� server.


W pliku indexowym rozm�w jest:

char[26] - ID
char[6] - nic
date
char[4] - nic
int - offset
int - index, ka�da rozmowa ma sw�j numer [nie pami�tam czy od 0 czy od 1
zaczyna liczy�, ale to nie ma znaczenia]
Przez to �e Tlen zapisuje na bie��co ka�d� wypowied� ka�dy msg w
rozmowie te� ma sw�j nag��wek, taki:

date
fromme - bool/char
deleted - bool/char, je�li != 0 wtedy wiadomo�� ma by� pomini�ta przy
czytaniu
char[2] - nic
int - length [tej pojedynczej wiadomo�ci]
int - index [rozmowy do kt�rej nale�y]
char[4] - nic

to jest struktura kt�ra jest przed ka�d� wypowiedzi�.

Struktura w indexie rozm�w - 56 bajt�w, ka�da wiadomo�� w rozmowie - 24,
wiadomo�ci pojedyncze - 56, sms - 40.

co do sms�w - w�a�nie sprawdzi�em, s� w archiwum, natomiast PowerArchiwe
pokazuje je wszystkie jako wys�ane - oryginalne archiwum rozr�nia
wys��ne i odebrane
Widocznie wykorzystali kt�ry� z nieu�ywanych bajt�w, b�dziesz musia� to
ju� rozgry�� sam.

W .idx wiadomo�ci [pojedynczych] i sms'�w masz wszystkie o� informacje.
Pliki .dat to tylko tre�ci + /0

Natomiast .idx rozm�w zawiera og�lne informacje o rozmowie - dat�, z
kim, ile wypowiedzi, offset pierwszej wiadomo�ci, etc. Dlatego Tlen
kiedy otwiera archiwum nie dotyka na pocz�tek .dat tylko wy�wietla list�
na podstawie samej zawarto�ci .idx