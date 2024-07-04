#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
struct campos {
    float sueldoA;
    float porcI;
};
struct Empleado {
    char nombre[20];
    char apellido1[20];
    char apellido2[20];
    char numeroSegu[20];
    int edad;
    char departamento[20];
    int antiguedad;
    struct campos adic;
} empleados[50], temp;

// Función para ordenar empleados por apellido1, apellido2 y nombre
void ordenarEmpleados(Empleado empleados[], int numE) {
    for (int i = 0; i < numE - 1; i++) {
        for (int j = 0; j < numE - i - 1; j++) {
            if (strcmp(empleados[j].apellido1, empleados[j + 1].apellido1) > 0 ||
                (strcmp(empleados[j].apellido1, empleados[j + 1].apellido1) == 0 &&
                strcmp(empleados[j].apellido2, empleados[j + 1].apellido2) > 0) ||
                (strcmp(empleados[j].apellido1, empleados[j + 1].apellido1) == 0 &&
                strcmp(empleados[j].apellido2, empleados[j + 1].apellido2) == 0 &&
                strcmp(empleados[j].nombre, empleados[j + 1].nombre) > 0)) {
                temp = empleados[j];
                empleados[j] = empleados[j + 1];
                empleados[j + 1] = temp;
            }
        }
    }
}

// Función para registrar empleados en archivos por departamento
void registroE(Empleado empleados[], int numE) {
    ofstream archivo;
    for (int i = 0; i < numE; i++) {
        string dep = string(empleados[i].departamento) + ".txt";
        archivo.open(dep.c_str(), std::ofstream::app);
        if (archivo.fail()) {
            cout << "No se pudo abrir el archivo";
            exit(1);
        }
        if (archivo.is_open()) {
            archivo << "Nombre: " << empleados[i].nombre << endl;
            archivo << "Primer Apellido: " << empleados[i].apellido1 << endl;
            archivo << "Segundo Apellido: " << empleados[i].apellido2 << endl;
            archivo << "Numero de Seguridad Social: " << empleados[i].numeroSegu << endl;
            archivo << "Edad: " << empleados[i].edad << endl;
            archivo << "Departamento: " << empleados[i].departamento << endl;
            archivo << "Antiguedad: " << empleados[i].antiguedad << " años" << endl;
            archivo << "Sueldo Mensual: " << empleados[i].adic.sueldoA << endl;
			archivo << "Porcentaje de Retenciones: " << empleados[i].adic.porcI << "%" << endl;
            archivo << endl;

            archivo.close();
            cout << "Se guardaron los datos ingresados en el archivo " << dep << endl;
        }
    }
}

// Función para calcular sueldo total entre rangos de apellidos o por departamento
void calcularSueldoTotal(Empleado empleados[], int numE) {
    int opc;
    cout << "Seleccione una opcion para calcular el sueldo total:" << endl;
    cout << "1. Por rango de apellidos" << endl;
    cout << "2. Por departamento" << endl;
    cout << "Elija una opcion: ";
    cin >> opc;
    cin.ignore();

    switch (opc) {
        case 1: {
            char apellidoI[20], apellidoF[20];
            cout << "Ingrese el apellido inicial: ";
            cin.getline(apellidoI, 20);
            cout << "Ingrese el apellido final: ";
            cin.getline(apellidoF, 20);
            cout << endl;

            float totalSueldos = 0;
            float totalRetenciones = 0;
            for (int i = 0; i < numE; i++) {
                if (strcmp(empleados[i].apellido1, apellidoI) >= 0 && strcmp(empleados[i].apellido1, apellidoF) <= 0) {
                    totalSueldos += empleados[i].adic.sueldoA;
                    totalRetenciones += empleados[i].adic.sueldoA * (empleados[i].adic.porcI / 100.0);
                }
            }
            float sueldoTotalNeto = totalSueldos - totalRetenciones;
            cout << "La suma total de los sueldos de los empleados seleccionados es: " << totalSueldos << endl;
			cout << "La suma total de los porcentajes de retenciones de impuestos es: " << totalRetenciones << endl;
			cout << "El sueldo total neto después de las retenciones es: " << sueldoTotalNeto << endl;
            break;
        }
        case 2: {
            char departamento[20];
            cout << "Ingrese el departamento a buscar: ";
            cin.getline(departamento, 20);
            float totalSueldos = 0;
            float totalRetenciones = 0;
            for (int i = 0; i < numE; i++) {
                if (strcmp(empleados[i].departamento, departamento) == 0) {
                    totalSueldos += empleados[i].adic.sueldoA;
                    totalRetenciones += empleados[i].adic.sueldoA * (empleados[i].adic.porcI / 100.0);
                }
            }
            float sueldoTotalNeto = totalSueldos - totalRetenciones;
            cout << "La suma total de los sueldos de los empleados seleccionados es: " << totalSueldos << endl;
			cout << "La suma total de los porcentajes de retenciones de impuestos es: " << totalRetenciones << endl;
			cout << "El sueldo total neto después de las retenciones es: " << sueldoTotalNeto << endl;
            break;
        }
        default:
            cout << "Opcion no valida." << endl;
    }
}

// Función para generar informe por departamento
void generarInformePorDepartamento(Empleado empleados[], int numE) {
    ofstream informe;
    string departamentoActual = "";

    for (int i = 0; i < numE; i++) {
        if (strcmp(empleados[i].departamento, departamentoActual.c_str()) != 0) {
            if (informe.is_open()) {
                informe.close();
            }
            departamentoActual = empleados[i].departamento;
            string nombreArchivo = departamentoActual + "_informe.txt";
            informe.open(nombreArchivo.c_str(), ofstream::out);
            if (!informe.is_open()) {
                cerr << "Error al abrir el archivo " << nombreArchivo << endl;
                return;
            }

            informe << "Informe de empleados del departamento: " << departamentoActual << endl << endl;
            informe << "------------------------------------------------------------------------------------------------" << endl;
            informe.width(20);
			informe << right <<"Nombre";
			informe.width(20);
			informe << right <<"Apellido 1";
			informe.width(20);
			informe << right <<"Apellido 2";
			informe.width(15);
			informe << right <<"Edad";
			informe.width(20);
			informe << right <<"Sueldo Mensual"<<endl;
            informe << "-----------------------------------------------------------------------------------------------" << endl;
        }

        // Imprimir datos del empleado
        informe.width(20);
        informe << right << empleados[i].nombre;
        informe.width(20);
        informe << right << empleados[i].apellido1;
        informe.width(20);
        informe << right << empleados[i].apellido2;
        informe.width(15);
        informe << right << empleados[i].edad;
        informe.width(20);
        informe << right << empleados[i].adic.sueldoA << endl;
    }
    informe.close();
    cout << "Se generaron los informes por departamento correctamente." << endl;
}


int main() {
    int numE, opc;
    cout << "Ingrese el numero de empleados: ";
    cin >> numE;
    cin.ignore();

    // Ingreso de los datos de los empleados
    for (int i = 0; i < numE; i++) {
        cout << "Ingrese los datos del empleado :"<< endl;

        cout << "Su primer apellido es: ";
        cin.getline(empleados[i].apellido1, 20);

        cout << "Su segundo apellido es: ";
        cin.getline(empleados[i].apellido2, 20);
        
        cout << "Su nombre es: ";
        cin.getline(empleados[i].nombre, 20);

        cout << "Su numero de Seguridad Social es: ";
        cin.getline(empleados[i].numeroSegu, 20);

        cout << "Su edad es: ";
        cin >> empleados[i].edad;
        cin.ignore();

        cout << "Pertenece al departamento de: ";
        cin.getline(empleados[i].departamento, 20);
        
        cout << "Su antiguedad dentro de la empresa es: ";
        cin >> empleados[i].antiguedad;
        cin.ignore();

        cout << endl;
    }

    // Funcion que ordena a los empleados por apellidos y nombre
    ordenarEmpleados(empleados, numE);
    // los empleados ordenados por apellido y nombre
    cout << "\n\t\tEmpleados ordenados por apellido y nombre:" << endl;
	for (int i = 0; i < numE; i++) {
    cout << "Empleado " << i + 1 << ":" << endl;
    cout << "Primer Apellido: " << empleados[i].apellido1 << endl;
    cout << "Segundo Apellido: " << empleados[i].apellido2 << endl;
    cout << "Nombre: " << empleados[i].nombre << endl;
    cout << "Numero de Seguridad Social: " << empleados[i].numeroSegu << endl;
    cout << "Edad: " << empleados[i].edad << endl;
    cout << "Departamento: " << empleados[i].departamento << endl;
    cout << "Antiguedad: " << empleados[i].antiguedad << " anos" << endl;
    cout << "Sueldo Mensual: " << empleados[i].adic.sueldoA << endl;
    cout << "Porcentaje de Retenciones: " << empleados[i].adic.porcI << "%" << endl;
    cout << endl;
}

    // Función para registrar empleados en archivos
    registroE(empleados, numE);

    do {
        cout << "\n\t\t\tMenu de opciones:" << endl;
        cout << "1. Buscar por nombre" << endl;
        cout << "2. Buscar por primer apellido" << endl;
        cout << "3. Buscar por segundo apellido" << endl;
        cout << "4. Buscar por numero de Seguridad Social" << endl;
        cout << "5. Buscar por edad" << endl;
        cout << "6. Buscar por departamento" << endl;
        cout << "7. Buscar por antiguedad" << endl;
        cout << "8. Agregar campos" << endl;
        cout << "9. Calcular el sueldo total" << endl;
        cout << "10. Generar informe por departamento" << endl;
        cout << "11. Salir del programa" << endl;
        cout << "Elija una opcion: ";
        cin >> opc;
        cin.ignore();

        switch (opc) {
            case 1: {
                char nombreBuscar[20];
                cout << "Ingrese el nombre a buscar: ";
                cin.getline(nombreBuscar, 20);
                for (int i = 0; i < numE; i++) {
                    if (strcmp(empleados[i].nombre, nombreBuscar) == 0) {
                        cout << "\nEmpleado encontrado:" << endl;
                        cout << "Nombre: " << empleados[i].nombre << endl;
                        cout << "Apellidos: " << empleados[i].apellido1 << " " << empleados[i].apellido2 << endl;
                        cout << "Departamento: " << empleados[i].departamento << endl;
                        
                    }
                }
                break;
            }
            case 2: {
                char apellidoBuscar[20];
                cout << "Ingrese el primer apellido a buscar: ";
                cin.getline(apellidoBuscar, 20);
                for (int i = 0; i < numE; i++) {
                    if (strcmp(empleados[i].apellido1, apellidoBuscar) == 0) {
                        cout << "\nEmpleado encontrado:" << endl;
                        cout << "Nombre: " << empleados[i].nombre << endl;
                        cout << "Apellidos: " << empleados[i].apellido1 << " " << empleados[i].apellido2 << endl;
                        cout << "Departamento: " << empleados[i].departamento << endl;
                    }
                }
                break;
            }
            case 3: {
                char apellidoBuscar[20];
                cout << "Ingrese el segundo apellido a buscar: ";
                cin.getline(apellidoBuscar, 20);
                for (int i = 0; i < numE; i++) {
                    if (strcmp(empleados[i].apellido2, apellidoBuscar) == 0) {
                        cout << "\nEmpleado encontrado:" << endl;
                        cout << "Nombre: " << empleados[i].nombre << endl;
                        cout << "Apellidos: " << empleados[i].apellido1 << " " << empleados[i].apellido2 << endl;
                        cout << "Departamento: " << empleados[i].departamento << endl;
                    }
                }
                break;
            }
            case 4: {
                char numSeguroBuscar[20];
                cout << "Ingrese el numero de Seguridad Social a buscar: ";
                cin.getline(numSeguroBuscar, 20);
                for (int i = 0; i < numE; i++) {
                    if (strcmp(empleados[i].numeroSegu, numSeguroBuscar) == 0) {
                        cout << "\nEmpleado encontrado:" << endl;
                        cout << "Nombre: " << empleados[i].nombre << endl;
                        cout << "Apellidos: " << empleados[i].apellido1 << " " << empleados[i].apellido2 << endl;
                        cout << "Departamento: " << empleados[i].departamento << endl;
                    }
                }
                break;
            }
            case 5: {
                int edadBuscar;
                cout << "Ingrese la edad a buscar: ";
                cin >> edadBuscar;
                cin.ignore();
                for (int i = 0; i < numE; i++) {
                    if (empleados[i].edad == edadBuscar) {
                        cout << "\nEmpleado encontrado:" << endl;
                        cout << "Nombre: " << empleados[i].nombre << endl;
                        cout << "Apellidos: " << empleados[i].apellido1 << " " << empleados[i].apellido2 << endl;
                        cout << "Departamento: " << empleados[i].departamento << endl;
                    }
                }
                break;
            }
            case 6: {
                char departamentoBuscar[20];
                cout << "Ingrese el departamento a buscar: ";
                cin.getline(departamentoBuscar, 20);
                for (int i = 0; i < numE; i++) {
                    if (strcmp(empleados[i].departamento, departamentoBuscar) == 0) {
                        cout << "\nEmpleado encontrado:" << endl;
                        cout << "Nombre: " << empleados[i].nombre << endl;
                        cout << "Apellidos: " << empleados[i].apellido1 << " " << empleados[i].apellido2 << endl;
                        cout << "Departamento: " << empleados[i].departamento << endl;
                    }
                }
                break;
            }
            case 7: {
                int antiguedadBuscar;
                cout << "Ingrese la antiguedad a buscar: ";
                cin >> antiguedadBuscar;
                cin.ignore();
                for (int i = 0; i < numE; i++) {
                    if (empleados[i].antiguedad == antiguedadBuscar) {
                        cout << "\nEmpleado encontrado:" << endl;
                        cout << "Nombre: " << empleados[i].nombre << endl;
                        cout << "Apellidos: " << empleados[i].apellido1 << " " << empleados[i].apellido2 << endl;
                        cout << "Departamento: " << empleados[i].departamento << endl;
                    }
                }
                break;
            }
            case 8: {
                cout << "Se han agregado nuevos campos a la tabla de empleados" << endl;
                for (int i = 0; i < numE; i++) {
                    cout << "Ingrese los datos adicionales del empleado " << i + 1 << ":" << endl;
                    cout << "Ingrese el sueldo mensual del empleado: ";
                    cin >> empleados[i].adic.sueldoA;

                    cout << "Ingrese el porcentaje de retenciones de impuestos del empleado: ";
                    cin >> empleados[i].adic.porcI;
                    cin.ignore();
                }
                // Función para registrar los saldos y retencion de los empleados en  los archivos
                ofstream archivo;
				for (int i = 0; i < numE; i++) {
				string dep = string(empleados[i].departamento) + ".txt";
				archivo.open(dep.c_str(), std::ofstream::app);
				if (archivo.fail()) {
				cout << "No se pudo abrir el archivo";
				exit(1);
				}
				if (archivo.is_open()) {
					archivo <<"\t\tDatos del empleado actualizado"<<endl;
					archivo << "Nombre: " << empleados[i].nombre << endl;
					archivo << "Primer Apellido: " << empleados[i].apellido1 << endl;
					archivo << "Segundo Apellido: " << empleados[i].apellido2 << endl;
					archivo << "Numero de Seguridad Social: " << empleados[i].numeroSegu << endl;
					archivo << "Edad: " << empleados[i].edad << endl;
					archivo << "Departamento: " << empleados[i].departamento << endl;
					archivo << "Antiguedad: " << empleados[i].antiguedad << " años" << endl;
					archivo << "Sueldo Mensual: " << empleados[i].adic.sueldoA << endl;
					archivo << "Porcentaje de Retenciones: " << empleados[i].adic.porcI << "%" << endl;
					archivo << endl;
					
					archivo.close();
					cout << "Se guardaron los datos ingresados en el archivo " << dep << endl;
					}
				}
                break;
            }
            case 9: {
                calcularSueldoTotal(empleados, numE);
                break;
            }
            case 10: {
                generarInformePorDepartamento(empleados, numE);
                break;
            }
            case 11: {
                cout << "Fin del programa." << endl;
                break;
            }
            default:
                cout << "Opcion incorrecta" << endl;
        }

    } while (opc != 11);

    return 0;
}

