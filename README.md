# Zamek-elektromagnetyczny-Arduino-NodeMCU-Firebase-Part1
Projekt przedstawia kontynuacje wyróżnionej pracy inżynierskiej studiów informatycznych. Zamysłem pracy było stworzenie zdalnego (aplikacja mobilna) oraz zbliżeniowego(karty RFID) sterowania do zamka elektromagnetycznego. Wszystko obywa się poprzez komunikację pomiędzy platformą Arduino oraz NodeMCU. Arduino w wersji Uno odpowiada za kontrolowanie większości podzespołów (Czytnik kart RFID, Wyświetlacz LCD, Zamek Elektromagnetyczny itd...) zaś NodeMCU za komunikacje z bazą danych czasu rzeczywistego Firebase Realtime Database. Z kolei baza danych modyfikowana jest przy użyciu aplikacji mobilnej (Android) oraz okienkowej aplikacji napisanej przy użyciu JavaFX. Projekt zostanie podzielony na 3 części, pierwszą z nich jest obecne repo, w którym opiszę wszystkie połączenia w Arduino oraz NodeMCU, następne zawierać będą kody programów do aplikacji Android oraz JavaFX. Obecnie projekt zawiera funkcje takie jak:

Aplikacja Android:
* Zdalne otwieranie drzwi
* Blokowanie dostępu wszystkim kartą RFID
* Sterowanie kolorami diody RBG

Aplikacja Okienkowa:
* Sterowanie tak jak w przypadku aplikacji mobilnej
* Możliwość zbindowania klawiszy do każdej z operacji, gdzie aplikacja działa w tle a dzięki bibliotece JNativeHook nasłuchuje zapisanych klawiszy gdziekolwiek znajduje się aktualny SCREEN FOCUS użytkownika.
