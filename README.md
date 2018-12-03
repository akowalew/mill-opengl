# ZW1 - Młyn

Celem projektu jest zaprojektowanie aplikacji rysującej trójwymiarowy młyn z wykorzystaniem technologii OpenGL.

## Schemat poglądowy

![mlyn-zw1.jpg](https://preview.ibb.co/h6sm4f/mlyn-zw1.jpg "Schemat poglądowy")

## Jak uruchamiać

Projekt (mimo braku takich wymagań) z założenia ma być uruchamiany przynajmniej na dwóch systemach: Windows oraz Linuksowych. Z tego względu skrypty budujące tworzone są przy użyciu programu *CMake*, dzięki czemu program może być z łatwością budowany przy pomocy kompilatorów GNU/LLVM, a także przy użyciu środowiska Visual Studio.

### Uruchamianie w Visual Studio 2017

1. Pobierz projekt oraz jego submoduły. W wierszu polecenia wpisać:
```cmd
	git clone git@galeranew.ii.pw.edu.pl:GKOM.18z/ZW1-Mlyn.git --recurse-submodules
```
2. Uruchomić pobrany folder w Visual Studio 2017. Środowisko powinno automatycznie wykryć, iż projekt konfigurowany jest poprzez CMake.
3. Wybrać domyślny Target jako *ZW1-Mlyn*
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
	cd src
	./ZW1-Mlyn
```

## Kontrybucja

Stworzyłem dla projektu stosowną grupę Slack: `zw1-mlyn.slack.com`
Do niej też podpięte są nityfikacje z serwera Gitlab.

## Autorzy

- Anna Kamińska
- Adam Kowalewski
- Paweł Krysztofik

## Literatura

- http://learnopengl.com/
- http://www.opengl.org/
- https://www.youtube.com/channel/UC1Gx4dn-QcSpJtZNdiqxy0A - VRLab ZGK

