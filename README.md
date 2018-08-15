# DiagnosticK7 1.0 par OlivierP.
___________________________________________________________________________________

# LICENCE D'UTILISATION
Ce logiciel est fourni en l'état. L'utilisateur l'utilise à ses risques et périls, sans garantie d'aucune sorte de la part de l'auteur.
L'auteur n'est responsable d'aucun dommage subi par l'utilisateur pouvant résulter de l'utilisation ou de la distribution de ce logiciel.
L'utilisateur a le droit d'utiliser ce logiciel et d'en faire autant de copies qu'il le souhaite.
L'utilisation de ce logiciel vaut acceptation par l'utilisateur des termes de la licence ci-dessus.
___________________________________________________________________________________

Attention, les formats protégés ne sont pas gérés, ils sont souvent considérés par cet utilitaire comme ayant des erreurs cheksum ou des parasites.
Cet utilitaire analyse les fichiers K7 pour MO/TO et affiche plusieurs informations :
- le MD5 brut, de l'ensemble des octets.
- le MD5 propre, tel qu'il serait si les synchronisations entre blocs étaient correctes.
- le type d'ordinateur : MO ou TO.
- le nombre d'octets en trop (parasites ou octets superflus en fin de fichier).
- le diagnostic : OK / DC / DCMO5 / DCMO6 / DCMOTO / Pb. Synchro / Parasites / Err. Checksum.
 
Pour voir le détail d'un fichier, double-cliquer sur sa ligne.
Pour trier les colonnes et afficher les doublons en couleur, cliquer sur le nom de la colonne.
___________________________________________________________________________________

Le calcul des MD5 est effectué par la librairie RFC1321-based (RSA-free) disponible à http://libmd5-rfc.sourceforge.net/
___________________________________________________________________________________

Merci à Daniel pour les informations sur la structure des fichiers K7. 
___________________________________________________________________________________

# COMPILATION

## Installer mingw-w64-x86_64

### sous Linux
```
$ sudo apt install mingw-w64
```
### si pas de Linux, utiliser MSYS2 64bit
```
$ pacman -S mingw-w64-x86_64-toolchain
```

## Installer wxWidgets3
```
$ tar xjvf wxWidgets-3.0.4.tar.bz2
$ cd wxWidgets-3.0.4/
$ mkdir build64b
$ cd build64b
$ ../configure --disable-debug --disable-shared --disable-threads --with-zlib=builtin --disable-fsvolume --disable-sockets --build=x86_64-w64-mingw32 --host=x86_64-w64-mingw32 --target=x86_64-w64-mingw32

[...]
Configured wxWidgets 3.0.4 for `x86_64-w64-mingw32'

  Which GUI toolkit should wxWidgets use?                 msw
  Should wxWidgets be compiled into single library?       no
  Should wxWidgets be linked as a shared library?         no
  Should wxWidgets support Unicode?                       yes (using wchar_t)
  What level of wxWidgets compatibility should be enabled?
                                       wxWidgets 2.6      no
                                       wxWidgets 2.8      yes
  Which libraries should wxWidgets use?
                                       STL                no
                                       jpeg               builtin
                                       png                builtin
                                       regex              builtin
                                       tiff               builtin
                                       zlib               builtin
                                       expat              builtin
                                       libmspack          no
                                       sdl                no


$ make
```
## Compiler DiagnosticK7 en 64bit
```
$ cd ../../DiagnosticK7/
$ make
```
