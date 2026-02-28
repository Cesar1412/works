#include "Calibrador.cpp"
#include <fstream>

int main() {
    // Simulando la carga de tu base de datos (Setpoint 15)
    double setpoint = 15.0;
    double subida = 15.1;
    double bajada = 14.9;
    std::vector<double> mis_reps = {14.9, 15.0, 15.1, 15.2}; // Datos de tu tabla

    // Ejecutar lógica
    procesarPuntoCalibracion("TERM-01", subida, bajada, mis_reps);

    // --- PERSISTENCIA ---
    std::ofstream archivo("reporte_calibracion.csv", std::ios::app);
    if (archivo.is_open()) {
        archivo << "ID,Setpoint,Histeresis\n";
        archivo << "TERM-01," << setpoint << "," << std::abs(subida - bajada) << "\n";
        archivo.close();
        std::cout << "\nDatos guardados exitosamente en 'reporte_calibracion.csv'" << std::endl;
    }

    return 0;
}