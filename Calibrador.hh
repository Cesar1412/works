#ifndef CALIBRADOR_HH
#define CALIBRADOR_HH

#include "Medicion.hh"
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

template <typename T>
class CalibradorTermico : public Instrumento<T> {
public:
    using Instrumento<T>::Instrumento; 

    // Histeresis diferencias subida y bajada
    T calcularHisteresis(T subida, T bajada) {
        return std::abs(subida - bajada);
    }
};


template <typename T>
void procesarPuntoCalibracion(std::string id, T sub, T baj, const std::vector<T>& reps) {
    //  Memoria 
    auto equipo = std::make_unique<CalibradorTermico<T>>(id);
    equipo->setRepetibilidad(reps);

    T hist = equipo->calcularHisteresis(sub, baj);
    T desv = equipo->obtenerDesviacion();

    std::cout << "--- Resultados para Equipo: " << id << " ---" << std::endl;
    std::cout << "Histeresis: " << hist << std::endl;
    std::cout << "Incertidumbre (Repetibilidad): " << desv << std::endl;
}

#endif