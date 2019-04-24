# Zamek-elektromagnetyczny-Arduino-NodeMCU-Firebase-Part1
Projekt przedstawia kontynuacje wyróżnionej pracy inżynierskiej studiów informatycznych. Zamysłem pracy było stworzenie zdalnego (aplikacja mobilna) oraz zbliżeniowego(karty RFID) sterowania do zamka elektromagnetycznego. Wszystko obywa się poprzez komunikację pomiędzy platformą Arduino oraz NodeMCU. Arduino w wersji Uno odpowiada za kontrolowanie większości podzespołów (Czytnik kart RFID, Wyświetlacz LCD, Zamek Elektromagnetyczny itd...) zaś NodeMCU za komunikacje z bazą danych czasu rzeczywistego Firebase Realtime Database. Z kolei baza danych modyfikowana jest przy użyciu aplikacji mobilnej (Android) oraz okienkowej aplikacji napisanej przy użyciu JavaFX. Projekt zostanie podzielony na 3 części, pierwszą z nich jest obecne repo, w którym opiszę wszystkie połączenia w Arduino oraz NodeMCU, następne zawierać będą kody programów do aplikacji Android oraz JavaFX. Obecnie projekt zawiera funkcje takie jak:

Aplikacja Android:
* Zdalne otwieranie drzwi
* Blokowanie dostępu wszystkim kartą RFID
* Sterowanie kolorami diody RBG

Aplikacja Okienkowa:
* Sterowanie tak jak w przypadku aplikacji mobilnej
* Możliwość zbindowania klawiszy do każdej z operacji, gdzie aplikacja działa w tle a dzięki bibliotece JNativeHook nasłuchuje zapisanych klawiszy gdziekolwiek znajduje się aktualny SCREEN FOCUS użytkownika.

# Schemat projektu

![schematProjektu](https://user-images.githubusercontent.com/35427912/56656084-d9fde980-6694-11e9-8caa-d5aa2b1bfdf9.jpg)

Schemat stworzony w Firtzing, link: https://www.dropbox.com/s/58otll1cdw05g23/SchematZamkeElektromagnetycznego.fzz?dl=0

Program Fritzing : http://fritzing.org/home/

# Połączenia

### Arduino / NodeMCU 
![image](https://user-images.githubusercontent.com/35427912/56657484-6d84e980-6698-11e9-83d5-58bee5591ee5.png)

### Arduino / Moduł czytnika kart RFID RC522
![image](https://user-images.githubusercontent.com/35427912/56657389-27c82100-6698-11e9-9a4a-e846842eae43.png)


### Arduino / Moduł przekaźnika SRD-5VDC-SL-C
![image](https://user-images.githubusercontent.com/35427912/56657833-4aa70500-6699-11e9-91f3-41470ad03f36.png)

### NodeMCU / Dioda RGB Anoda
![image](https://user-images.githubusercontent.com/35427912/56660031-da02e700-669e-11e9-83dd-7412a5a948fa.png)

### Zamek elektromagnetyczny / Przekaźnik

Przekaźnik steruje 9V baterią, która wykorzystywana jest do otwierania zamka elektromagnetycznego. Plus(+) Baterii należy podłączyć do przekaźnika do wyprowadzenia COM.
" Wyprowadzenia wyjściowe oznaczone są jako NO - domyślnie odłączone, NC - domyślnie podłączone z COM. Podanie stanu wysokiego na pin IN (3V-5,5V) przełącza styki przekaźnika i tworzy połączenie pomiędzy COM i NO rozłączając COM z NC. "  

W tym wypadku interesuje mnie wyjście NO, które normalnie jest otwarte. Po otrzymaniu sygnału z Arduino zostanie tu puszczony prąd z baterii do zamka. UWAGA, nie można bezpośrednio zasilić zamka przy pomocy baterii ponieważ Arduino zwariuje i przestanie działać ( na szczęscie tylko do jego restartu :) ). Należy prąd przepuścić przez kondensator, który go przefiltruje i powstrzyma zakłócenia nim spowodowane (nie znam do końca tego tematu, jeżeli chodzi o elektronike jestem początkujący, ale bez kondensatora Arduino przy otwarciu zamka przestawało reagować). W projekcie używany jest kondensator 70uF o maksymalnym napięciu pracy 16V.

### Uproszczony schemat połączenia Arduino -> Przekaźnik -> Kondensator -> Zamek
![polaczenieprzekaznik](https://user-images.githubusercontent.com/35427912/56661812-d1acab00-66a2-11e9-808d-011362f8ac1f.jpg)


# Zasilanie

NIESTETY przedstawiany projekt zasilany jest poprzez dwie ładowarki ( Adaptery z OUTPUTem 5V - standardowe ładowarki do telefonów ). Na pewno istnieje możliwość zasilenia NodeMCU oraz Arduino z jednej ( ogarniczenie ilości kabli, adapterów itd ), ale w przypadku gdy chciałem zasilić przykładowo NodeMCU używając VCC z Arduino to nie było to wystarczające do stabilnej pracy ). Zasilanie zostanie tu poprawione, lecz na dzień dzisiejszy cały projekt jest już zamontowany do sciany, gdzie czytnik RFID znajduje się po jej drugiej stronie. Wynikiem czego jakakolwiek próba konfiguracji zamontowanego projektu jest zbyt pracochłonna i niewygodna. Mam w planach kupić dodatkowy zestaw Arduino by ulepszać projekt nie ingerując w już działające sterowanie do drzwi. 
Oczywiście istnieje również kwestia zasilania Zamka elektromagnetycznego, ten działa w przedziale 8 do 12 V, dlatego normalnie Arduino sobie z nim nie poradzi, rozwiązanie tego również będzie poprawione, narazie musze zadowolić się baterią 9V.

# Opis kodu

### Soon
