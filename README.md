# rFactor udp
---

![][ref-schemat-rpi-lcd]

### Informacje
Próba stworzenia pluginu dla symulatora wyścigowego rFactor.
Zadaniem pluginu jest przekazywanie danych telemetrycznych przez UDP. Z drugiej strony mamy RPi, które wyłapuje te dane i wyświetla na LCD. Kilka screenów poniżej.

To co miałem jeszcze na dysku to wrzucam, powinno działać. Jakby ktoś miał jakieś problemu to służę pomocą.

###### Obroty, biegi, prędkość
![][ref-img-3]

###### Gaz, hamulec, położenie kierownicy, pedał sprzęgła
![][ref-img-4]

###### Nazwa samochodu i trasy
![][ref-img-5]

###### Temperatura oleju i wody
![][ref-img-6]

###### Numer sesji i ilość pojazdów
![][ref-img-7]

###### CT, ET
(prawdopodobnie w trybie "testing" nie mają one większego znaczenia)
![][ref-img-8]

### Instalacja i uruchomienie
###### Lista niezbędnych rzeczy:
* Raspberry Pi (w moim przyadku B+),
* Karta μSD lub SD,
* Wyświetlacz LCD zgodny z HD44780,
* Tact Switch,
* Rezystory (220Ω, 3x 1k Ω, 10k Ω),
* Płytka stykowa,
* 10 przewodów męsko-żeńskich. 

###### Przygotowanie systemu:
* Wkładamy kartę do komputera... :)

Windows:
* ściągamy narzędzie typu Rufus czy LinuxLiveUSB, wybieramy interesującą nas dystrybucję (archARM),
klikamy dalej i czekamy. Po dłuższej chwili nasza karta jest już gotowa.

Linux:
* sprawdzamy gdzie znajduje się nasza karta, 
```
# fdisk -l
```
* usuwamy stare partycje i tworzymy nowe,
```
# fdisk /dev/sdX
# o (usuwa partycje)
# n (tworzy nową) -> p (primary) -> 1 (pierwsza partycja) -> ENTER
(pierwszy sektor) -> +100M (ostatni sektor)
# t -> c (ustawiamy typ partycji na W95 FAT32)
# n -> p -> 2 (druga partycja) -> ENTER -> ENTER
# w (zapisujemy i wychodzimy)
```
* tworzymy systemy plików FAT dla boot i ext4 dla /,
```
# mkfs.vfat /dev/sdX1
# mkfs.ext4 /dev/sdX2
```
* montujemy partycje,
```
# mkdir boot
# mount /dev/sdX1 boot
# mkdir root
# mount /dev/sdX2 root
```
* ściągamy, rozpakowywujemy,
```
# wget http://archlinuxarm.org/os/ArchLinuxARM-rpi-latest.tar.gz
# bsdtar –xpf ArchLinuxARM-rpi-latest.tar.gz –C root
# sync
```
* przenosimy folder boot,
```
# mv root/boot/* boot
```
* teraz należy odmontować nasze partycje,
```
# umount boot root
```

* teraz możemy włożyć kartę do Raspberry, podpiąć kabel sieciowy i zasilanie.
RPi korzystając z DHCP uzyska adres IP. Jeśli podpięliśmy RPi do routera to prawdopodobnie na nim
możemy sprawdzić jaki adres został przydzielony. W moim wypadku adres to 192.168.0.24.
* logujemy się do naszego RPi. (Windows: putty) (user: alarm/alarm, root/root),
* aktualizujemy nasz system,
```
# pacman -Syuu
```
* następnie instalujemy niezbędne paczki,
```
# pacman -S python python-pip git
# pip install RPi.GPIO
```
* teraz zostało nam jeszcze ustawić tylko adres statyczny dla naszego RPi (od tego momentu zakładam,
że RPi będzie podłączone kablem sieciowym do komputera, a nie do routera).
```
# cd /etc/netctl
# cp examples/ethernet-static eth
```
* edytujemy plik eth, np. przy pomocy vima,
```
# vim eth
```

```
Description=’ethernet’
Interface=eth0
Connection=Ethernet
IP=static
Address=(‘192.168.3.14/24’)
11Gateway=(‘192.168.1.1’)
Auto_wired=yes
```
* zapisujemy, wychodzimy (vim: ESCAPE -> :wq -> ENTER), wywołujemy,
```
# netctl start eth
# netctl enable eth
```
* odłączamy RPi od zasilania.

##### Podłączanie wyświetlacza do RPi

Podpinamy wszystko jak na poniższym obrazku.

![][ref-schemat-rpi-lcd]

Pomocny może okazać się schemat z opisem pinów RPi B+

![][ref-rpi-pin]

##### Uruchamiamy naszego klienta

* Podłączamy RPi, logujemy się przy pomocy wcześniej ustalonego adresu (192.168.3.14). Następnie
ściągamy repozytorium z kodem przy pomocy:
``` 
git clone https://github.com/sz-m/rfactor-udp/
```
* przechodzimy do katalogu `pyfactor` i odpalamy `run.py` (aby skrypt miał dostęp do GPIO musi zostać odpalony z odpowiednimi uprawnieniami)
```
su -c "python pyfactor/run.py"
```
* jeśli wszystko przebiegło pomyślnie powinniśmy ujrzeć na naszym wyświetlaczu aktualną datę.

* Nasze RPi zostało w pełni skonfigurowane do pracy z pluginem. Teraz przystępujemy do konfiguracji na naszym komputerze,
* ściągamy repozytorium z kodem (możemy to zrobić przy pomocy git’a jak powyżej lub klikając „download as zip” powyżej),
* w repozytorium znajduje się skompilowana już biblioteka, nic nie stoi jednak na przeszkodzie abyśmy sami ją utworzyli,
* skompilowaną bibliotekę (Release/rfudp.dll) kopiujemy do naszego katalogu z grą (rFactor/Plugins lub odpowiednio Steam/steamapps/common/rFactor/Plugins),
* następnie w katalogu głównym gry tworzymy pusty folder o nazwie logs, który będzie przechowywał logi z gry.
* Uruchamiamy grę i odpalamy wyścig.
* Przy pomocy przycisku na płytce stykowej zmieniamy wyświetlane informacje.

[ref-schemat-rpi-lcd]: img/img1.png
[ref-rpi-pin]: img/img2.png
[ref-img-3]: img/img3.png
[ref-img-4]: img/img4.png
[ref-img-5]: img/img5.png
[ref-img-6]: img/img6.png
[ref-img-7]: img/img7.png
[ref-img-8]: img/img8.png

