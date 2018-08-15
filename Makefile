# created by OlivierP

# chemin vers wx-config, qui retourne les parametres de compilation
WX_PATH = ../wxWidgets-3.0.4/build64b
WX_CONFIG = $(WX_PATH)/wx-config

# nom de l'executable a produire
PROGRAM = DiagnosticK7
WPATH = tmp

# liste des fichiers composant l'executable
OBJECTS = $(WPATH)/md5.o $(WPATH)/analyseK7.o $(WPATH)/Resultat.o $(WPATH)/About.o $(WPATH)/DiagnosticK7Main.o $(WPATH)/DiagnosticK7App.o

# compilation
CXX = $(shell $(WX_CONFIG) --cxx)
CPPFLAGS = `$(WX_CONFIG) --cxxflags` -s -O2
LDFLAGS = `$(WX_CONFIG) --libs std` -mwindows -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread

all: $(PROGRAM)

tmp:
	mkdir -p $(WPATH)

# creation de l'executable
$(PROGRAM): tmp $(OBJECTS)
	$(CXX) -s -o $(PROGRAM).exe $(OBJECTS) $(LDFLAGS) 

clean:
	rm -fr $(WPATH)

# sources
$(WPATH)/md5.o:	md5.h md5.c
	$(CXX) -c $(CPPFLAGS) -o $@ md5.c

$(WPATH)/analyseK7.o:	analyseK7.h analyseK7.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ analyseK7.cpp

$(WPATH)/Resultat.o:	Resultat.h Resultat.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ Resultat.cpp

$(WPATH)/About.o:	About.h About.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ About.cpp

$(WPATH)/DiagnosticK7Main.o:	DiagnosticK7Main.h DiagnosticK7Main.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ DiagnosticK7Main.cpp

$(WPATH)/DiagnosticK7App.o:	DiagnosticK7App.h DiagnosticK7App.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ DiagnosticK7App.cpp
