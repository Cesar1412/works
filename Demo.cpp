#include <iostream>
#include <fstream>
#include <vector>
#include "types.hh"
#include "Calibrador.hh" 

int main() {
    // Datos de entrada
    Real setpoint = 15.0;
    Real subida = 15.1;
    Real bajada = 14.9;
    std::vector<Real> mis_reps = {14.9, 15.0, 15.1, 15.2};

    //
    procesarPuntoCalibracion<Real>("TERM-01", subida, bajada, mis_reps);

    // Guardar resultados en CSV
    std::ofstream archivo("reporte_calibracion.csv", std::ios::app);
    
    if (archivo.is_open()) {
        Real histeresis = std::abs(subida - bajada);
        
        // Escribimos los datos fila por fila
     
        archivo << "TERM-01," << setpoint << "," << histeresis << "\n";
        
        archivo.close();
        std::cout << "\n[Sistema] Datos guardados en 'reporte_calibracion.csv'" << std::endl;
    } else {
        std::cerr << "Error al abrir el archivo de persistencia." << std::endl;
    }

    return 0;
}