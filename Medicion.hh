#ifndef MEDICION_HH
#define MEDICION_HH

#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <algorithm>

// Interfaz 
template <typename T>
class IProcesadorCalibracion {
public:
    virtual ~IProcesadorCalibracion() = default;
    virtual T calcularError(T lectura, T patron) = 0;
};

// ORDEN DE CREACION DE ADENTRO HACIA AFUERA
// ORDEN DE DESTRUCCION ( DE AFUERA HACIA ADENTRO)
// IProcesadorCalibracion -> Instrumento -> CalibradorTermico

template <typename T>

class Instrumento : public IProcesadorCalibracion<T> { // HERENCIA IProcesadorCalibracion -> Instrumento 
protected:
    std::string id;
    std::vector<T> repetibilidad; // Datos de repeticiones 

public:
    Instrumento(std::string _id) : id(_id) {} // Cnstructor - id(_id) lista de inicializacion 
    
    void setRepetibilidad(const std::vector<T>& datos) {
        repetibilidad = datos;
    }

    // Implementacion de la Interfaz
    T calcularError(T lectura, T patron) override {
        return lectura - patron;
    }

    //Desviación Estandar
    T obtenerDesviacion() {
        if (repetibilidad.empty()) return 0;
        T suma = 0;
        for(T v : repetibilidad) suma += v;
        T media = suma / repetibilidad.size();
        
        T var = 0;
        for(T v : repetibilidad) var += std::pow(v - media, 2);
        return std::sqrt(var / repetibilidad.size());
    }
};

#endif