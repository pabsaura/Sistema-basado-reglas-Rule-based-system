programa:
	g++ -O3 Main.cpp LectorConfiguracion.cpp Atributo.cpp Regla.cpp Hecho.cpp -o motor

clean:
	rm -rf motor .DS_Store motor.D*

run1: programa
	./motor Ficheros/Config-F.txt Ficheros/BC-F.txt Ficheros/BH-F1.txt
run2: programa
	./motor Ficheros/Config-F.txt Ficheros/BC-F.txt Ficheros/BH-F2.txt
run3: programa
	./motor Ficheros/Config-I.txt Ficheros/BC-I.txt Ficheros/BH-I1.txt
run4: programa
	./motor Ficheros/Config-I.txt Ficheros/BC-I.txt Ficheros/BH-I2.txt
