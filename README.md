# ZW1 - Młyn

Celem projektu było zaprojektowanie aplikacji rysującej trójwymiarowy młyn z wykorzystaniem technologii OpenGL.

![ZW1-Mlyn-linux.jpg](https://i.ibb.co/qpVnyXc/ZW1-Mlyn-linux.png "Zrzut aplikacji w systemie Linux")

## Jak uruchamiać

Projekt (mimo braku takich wymagań) z założenia ma być uruchamiany przynajmniej na dwóch systemach: Windows oraz Linuksowych. Z tego względu skrypty budujące tworzone są przy użyciu programu *CMake*, dzięki czemu program może być z łatwością budowany przy pomocy kompilatorów GNU/LLVM, a także przy użyciu środowiska Visual Studio.

### Uruchamianie w Visual Studio 2017

1. Pobierz projekt oraz jego submoduły. Można to zrobić z poziomu konsoli (poprzez SSH) lub z poziomu samego Visual Studio.
- W przypadku wiersza poleceń, należy wpisać:
```
	git clone git@galeranew.ii.pw.edu.pl:GKOM.18z/ZW1-Mlyn.git --recurse-submodules
```
- W przypadku Visual Studio należy wybrać "Otwórz"->"Otwórz z kontroli źródła". Następnie w wyświetlonym panelu "Team Explorer" wybierz "Klonuj" oraz zaznacz "Klonuj rekursywnie submoduły". Następnie w polu "URL" podaj adres `http://galeranew.ii.pw.edu.pl:8100/GKOM.18z/ZW1-Mlyn.git`.

2. Uruchomić pobrany folder w Visual Studio 2017. Środowisko powinno automatycznie wykryć, iż projekt konfigurowany jest poprzez CMake.
3. Wybrać domyślny cel budowania jako *ZW1-Mlyn*
4. Skompilować i uruchomić.

### Uruchamianie pod Linux

1. Pobierz projekt oraz jego submoduły. W terminalu wpisać:
```sh
	git clone git@galeranew.ii.pw.edu.pl:GKOM.18z/ZW1-Mlyn.git --recurse-submodules
```
2. Skompiluj projekt:
```sh
	mkdir build
	cd build
	cmake ..
	make -j5
```
3. Uruchom projekt:
```sh
	./ZW1-Mlyn
```

## Obsługa aplikacji

Przewidziano możliwość sterowania trzema elementami w aplikacji:
-	Kamerą: Zoom realizuje się klawiszami `+`, `-`, natomiast klawiszami strzałek przesuwa się kamerę po świecie.
-	Pozycją źródła światła: Klawiszami `W`, `A`, `S`, `D`.
-	Prędkością obrotową śmigieł: zwiększanie `Y`, zmniejszanie `Z`.

## Kontrybucja

Stworzyłem dla projektu stosowną grupę Slack: `zw1-mlyn.slack.com`
Do niej też podpięte są notyfikacje z serwera Gitlab.

## Autorzy

- ~~Anna Kamińska~~
- Adam Kowalewski
- Paweł Krysztofik

## Literatura

- https://www.youtube.com/playlist?list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP - OpenGL 3D Game Tutorials
- http://gamedev.net
- http://learnopengl.com/
- http://www.opengl.org/
- https://www.youtube.com/channel/UC1Gx4dn-QcSpJtZNdiqxy0A - VRLab ZGK

