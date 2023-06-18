#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Clase abstracta que representa la abstracción "Dispositivo"
class Dispositivo {
public:
	class Implementador {
	public:
		virtual void cambiarCanal(int canal) = 0;
	};

	Implementador* implementador;

public:
	Dispositivo(Implementador* imp) : implementador(imp) {}

	virtual void cambiarCanal(int canal) {
		implementador->cambiarCanal(canal);
	}
};

// Clase abstracta que representa la abstracción "TV"
class TV : public Dispositivo {
protected:
	int numeroCanal;
	string nombreCanal;
	int volumen;
	bool estado;
	int* canalActual;

public:
	TV(Implementador* imp, int numCanal, string nomCanal, int vol, bool est)
		: Dispositivo(imp), numeroCanal(numCanal), nombreCanal(nomCanal), volumen(vol), estado(est) {
		canalActual = &numeroCanal;
	}

	void cambiarCanal(int canal) override {
		*canalActual = canal;
		cout << "TV: Cambiando al canal " << *canalActual << endl;
	}

	void mostrarInformacion() {
		cout << "TV: Canal actual: " << *canalActual << ", Volumen: " << volumen << ", Estado: " << (estado ? "Encendido" : "Apagado") << endl;
	}
};

// Clase abstracta que representa la abstracción "Radio"
class Radio : public Dispositivo {
protected:
	int volumen;
	float frecuencia;
	bool estado;

public:
	Radio(Implementador* imp, int vol, float freq, bool est)
		: Dispositivo(imp), volumen(vol), frecuencia(freq), estado(est) {}

	void cambiarCanal(int canal) override {
		frecuencia = canal;
		cout << "Radio: Cambiando a la frecuencia " << frecuencia << endl;
	}

	void mostrarInformacion() {
		cout << "Radio: Frecuencia actual: " << frecuencia << ", Volumen: " << volumen << ", Estado: " << (estado ? "Encendido" : "Apagado") << endl;
	}
};

// Clase abstracta que representa la abstracción "TVBox"
class TVBox : public Dispositivo {
protected:
	int volumen;
	vector<string> servicios;
	bool estado;

public:
	TVBox(Implementador* imp, int vol, vector<string> serv, bool est)
		: Dispositivo(imp), volumen(vol), servicios(serv), estado(est) {}

	void cambiarCanal(int canal) override {
		cout << "TVBox: Cambiando al servicio " << canal << endl;
	}

	void mostrarInformacion() {
		cout << "TVBox: Servicios: ";
		for (const auto& servicio : servicios) {
			cout << servicio << " ";
		}
		cout << ", Volumen: " << volumen << ", Estado: " << (estado ? "Encendido" : "Apagado") << endl;
	}
};

// Implementación de la clase "Canales" que actúa como la implementación para TV, Radio y TVBox
class Canales : public Dispositivo::Implementador {
public:
	void cambiarCanal(int canal) override {
		cout << "Sintonizando el canal " << canal << endl;
	}
};

// Implementación de la clase "Servicios" que actúa como la implementación para TVBox
class Servicios : public Dispositivo::Implementador {
protected:
	vector<string> peliculas;

public:
	Servicios(vector<string> pelis) : peliculas(pelis) {}

	void cambiarCanal(int canal) override {
		cout << "Mostrando el servicio " << canal << endl;
	}

	void mostrarInformacion() {
		cout << "Servicios: Películas disponibles: ";
		for (const auto& pelicula : peliculas) {
			cout << pelicula << ", ";
		}
		cout << endl;
	}
};

int main() {
	// Crear una instancia de TV y usar Canales como implementador
	TV tv(new Canales(), 5, "Canal 5", 50, true);
	tv.mostrarInformacion();
	tv.cambiarCanal(7);
	tv.mostrarInformacion();

	// Crear una instancia de Radio y usar Canales como implementador
	Radio radio(new Canales(), 30, 95.5, true);
	radio.mostrarInformacion();
	radio.cambiarCanal(103.7);
	radio.mostrarInformacion();

	// Crear una instancia de TVBox y usar Servicios como implementador
	vector<string> peliculas = { "Pelicula 1", "Pelicula 2", "Pelicula 3" };
	Servicios servicios(peliculas);
	TVBox tvBox(&servicios, 60, {}, true);
	tvBox.mostrarInformacion();
	tvBox.cambiarCanal(2);
	servicios.mostrarInformacion();
	tvBox.mostrarInformacion();

	return 0;
}