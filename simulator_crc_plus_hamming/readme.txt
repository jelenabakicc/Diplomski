Program za testiranje komunikacionog protokola koji sadrži sledeće komunikacione elemente:
1) Izvor
2) Blok za paketizaciju informacionog niza (uključujući dodavanje CRC dodatka)
3) Hemingov koder
4) Binarni simetrični kanal
5) Hemingov dekoder
6) Blok za de-paketizaciju informacionog niza uz vođenje statistike o broju paketa koji su oštećeni prilikom prenosa
7) Korisnik koji vodi statistiku o broju pogrešno primljenih paketa

Program je organizovan tako da sadrži sledeće blokove:
1) "SourceSink" blok (klasa) koji sadrži funkcionalnosti izvora i korisnika informacija
2) "Frame" blok (klasa) koji sadrži funkcionalnosti za paketizaciju i de-paketizaciju; sadrži objekat tipa CRC čije funkcije obavljalju generisanje CRC dodatka i proveru ispravnosti primljenog paketa 
3) "Hammnig" blok (klasa) koji sadrži koder i dekoder
4) "Channel" blok (klasa) koji sadrži funkcionalnosti komunikacionog kanala
5) "CommBlock" predstavlja nadblok (nadklasu) koja sadrži članove tipa "Frame" i "Hamming" i konfiguriše se da radi kao predajnik ili prijemnik
6) "Config" blok (struktura) predstavlja konfiguracionu strukturu u koju se upisuju parametri sistema za prenos (veličina paketa, CRC polinom, verovatnoća greške...). 
Parametri ove strukture se prosleđuju ostalim blokovima prilikom njihove konstrukcije.

Komunikacioni blokovi razmenjuju informacione nizove preko generičkih funkcija koje sadrže svi blokovi (osim SourceSink bloka): 
-------------------------------------------------------
void fillAndProcess(int*) -> kada se pozove u objekat se upisuje niz koji je potrebno da obradi i
int* getOutput() -> kada se pozove vraća obađeni niz na izlaz bloka
-------------------------------------------------------
Pored ovih funkcija svi blokovi sadrže i konstruktore (za inicijalizaciju parametara prilikom bloka), destruktor (jer sadrže dinamički dodeljenu memoriju), funkcije za podešavanje parametara 
bloka nakon nastanka bloka (setNestoFunkcija(.)), funkcije koje vraćaju određene parametre bloka (getNestoFunkcija(.)). Sve ove funkcije su definisane za javni pristup. Pored navedenih funkicja
 pojedini blokovi sadrže i specijalne funkcije koje su najčešće privatne i služe za internu upotrebu unutar bloka. Na primer blok "Hamming" sadrži funkcije encode(.) i decode(.) kojima se koduju odnosno
 dekoduju pojedine kodne reči, ali pozivanje ovih funkcija van objekta (bloka) nije dozvoljeno. Slično, objakat tipa Frame sadrži funkcije za rad sa CRC kodom, koje nisu potrebne ostalim blokovima, 
pa su takođe privatne. 

Program ima za cilj da ilustruje objetno-orijentisano pisanje koda (bez upotrebe nasleđivanja i polimorizma). Posebnu pažnju treba obratiti na funkcije konstruktra/destruktora u svakoj od klasa,
 organizaciju simulatora po blokovima, izgled main.cpp fajla kao i na rad sa dinamičkom memorijom. Analiza i razumevanje samih funkcija (posebno privatnih funkcije kojima se obavlja rad sa CRC i 
Hemingovim kodom) je od manjeg značaja.    


