CC = g++
BIN = bin
ODIR = obj
CXXFLAGS = -std=c++11 -lnfc

OBJS = $(ODIR)/apdu.o $(ODIR)/nfcManager.o $(ODIR)/nfcUtils.o $(ODIR)/apdu_cli.o

.PHONY : examples
examples : $(ODIR) $(OBJS)
	$(CC) -o $(BIN)/apdu_cli $(OBJS) $(CXXFLAGS)
	$(CC) -o $(BIN)/select $(OBJS) $(CXXFLAGS)

$(ODIR)/apdu.o : ./nfc/src/apdu.cpp ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c ./nfc/src/apdu.cpp -o $@ $(CXXFLAGS)

$(ODIR)/nfcManager.o : ./nfc/src/nfcManager.cpp ./nfc/include/nfcManager.h ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c ./nfc/src/nfcManager.cpp -o $@ $(CXXFLAGS)

$(ODIR)/nfcUtils.o : ./nfc/src/nfcUtils.cpp ./nfc/include/nfcUtils.h
	$(CC) -c ./nfc/src/nfcUtils.cpp -o $@ $(CXXFLAGS)

$(ODIR)/apdu_cli.o : ./examples/apdu_cli.cpp ./nfc/include/nfcManager.h ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c ./examples/apdu_cli.cpp -o $@ $(CXXFLAGS)

$(ODIR)/select.o : ./examples/select.cpp ./nfc/include/nfcManager.h ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c ./examples/select.cpp -o $@ $(CXXFLAGS)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -d $(BIN) ]; then rm $(BIN) -r; fi
