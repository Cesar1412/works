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

// Clase Base 
template <typename T>
class Instrumento : public IProcesadorCalibracion<T> {
protected:
    std::string id;
    std::vector<T> repetibilidad; // Datos de Rep_15, Rep_18, etc.

public:
    Instrumento(std::string _id) : id(_id) {}
    
    void setRepetibilidad(const std::vector<T>& datos) {
        repetibilidad = datos;
    }

    // Implementación de la Interfaz
    T calcularError(T lectura, T patron) override {
        return lectura - patron;
    }

    // Método para calcular Desviación Estándar (Repetibilidad)
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