#include "Medicion.hh"
#include <iostream>

template <typename T>
class CalibradorTermico : public Instrumento<T> {
public:
    using Instrumento<T>::Instrumento; // Heredar constructor

    // Lógica específica de Histéresis
    T calcularHisteresis(T subida, T bajada) {
        return std::abs(subida - bajada);
    }
};

// Función global que usa Smart Pointers para procesar instrumentos
template <typename T>
void procesarPuntoCalibracion(std::string id, T sub, T baj, const std::vector<T>& reps) {
    // Uso de std::unique_ptr (Smart Pointer)
    auto equipo = std::make_unique<CalibradorTermico<T>>(id);
    equipo->setRepetibilidad(reps);

    std::cout << "--- Resultados para Equipo: " << id << " ---" << std::endl;
    std::cout << "Histeresis: " << equipo->calcularHisteresis(sub, baj) << std::endl;
    std::cout << "Incertidumbre (Repetibilidad): " << equipo->obtenerDesviacion() << std::endl;
}