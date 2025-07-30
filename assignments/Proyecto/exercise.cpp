#include "Combatiente.hpp"
#include <iostream>
#include "HarleyQuinn.hpp"
#include "Gatubela.hpp"
#include "HiedraVenenosa.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

//IMPLEMENTACIÓN FINAL Y MAIN 
//Cargr archivos de txt 
//Crear funcion cargarEjercito
void cargarEjercito(const std::string& nombreArchivo, std::vector<Combatiente*>& ejercito) {
    //abre el archivo con el nombre 
    std::ifstream archivo(nombreArchivo);//verifica si se abrie correctamente
    if (!archivo) { //si no 
        throw std::runtime_error("No se pudo abrir el archivo: " + nombreArchivo); //error falla de lectura de archivo
    } //continua con la lectura

    std::string tipo; //variable para almacenar el tipo de combatiente del archivo
//crear objetos de manera dinamica     
    while (archivo >> tipo) {//Lee el archivo extrayendo el tipo de combatiente en la variable tipo
        if (tipo == "HarleyQuinn") {
            ejercito.push_back(new HarleyQuinn()); //añade al vector ejercito
        } else if (tipo == "Gatubela") {
            ejercito.push_back(new Gatubela()); //añade al vector ejercito
        } else if (tipo == "HiedraVenenosa") {
            ejercito.push_back(new HiedraVenenosa());//añade al vector ejercito
        } else {
            throw std::runtime_error("Tipo de combatiente desconocido en el archivo: " + tipo); //combatiente desconocido (no implementado)
        }
    }
}

//FUncion para imprimir los datos del combatiente
void imprimirEjercito(const std::vector<Combatiente*>& ejercito) {
    std::cout << "\n･☆･﹋﹋﹋﹋𝐂𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐢𝐬𝐭𝐢𝐜𝐚𝐬 𝐝𝐞𝐥 𝐜𝐨𝐦𝐛𝐚𝐭𝐢𝐞𝐧𝐭𝐞﹋﹋﹋﹋･☆･\n";
    for (const auto* combatiente : ejercito) {
        combatiente->imprimir();
        std::cout << std::endl;
    }
}

//FUNCION de la batalla 
void batalla(std::vector<Combatiente*>& ejercito1, std::vector<Combatiente*>& ejercito2) {
    //srand(static_cast<unsigned int>(time(0))); //generar numero aleatorios
    size_t ronda = 1;

    while (!ejercito1.empty() && !ejercito2.empty()) { //mientras no esten vacios
        std::cout << "\n══════》♡》♡》♡》♡》♡》𝐏𝐄𝐋𝐄𝐀《♡《♡《♡《♡《♡《══════" << std::endl;
        std::cout << "Ronda " << ronda++ << ":" << std::endl; //imprime numero de ronda actual 
        //seleccion de combatientes aleatoria con rand
        //la validacion asegura que el programa no intente acceder a elementos de vectores vacios
        if (ejercito1.empty() || ejercito2.empty()) break;
        size_t idx1 = std::rand() % ejercito1.size(); //calcula el residuo de dividir el no aleatorio generado entre el tamaño del vector ej1 o ej2 
        size_t idx2 = std::rand() % ejercito2.size();

        Combatiente* combatiente1 = ejercito1[idx1];    
        Combatiente* combatiente2 = ejercito2[idx2];
        
        //asegurar que los punteros no sean nulos
        if (!combatiente1 || !combatiente2) {
            std::cerr << "Error: Combatiente nulo detectado." << std::endl;
            continue; 
        }

        //sobrecarga del operador <<
        std::cout << "Ataque de " << *combatiente1 << " a " << *combatiente2 << ":" << std::endl;
        combatiente1->atacar(*combatiente2);
        combatiente2->imprimir();

        if (!combatiente2->estaVivo()) {
            delete combatiente2; //liberar memoria
            ejercito2.erase(ejercito2.begin() + idx2);
        }
        if (ejercito2.empty()) break;

        std::cout << "Ataque de " << *combatiente2 << " a " << *combatiente1 << ":" << std::endl;
        combatiente2->atacar(*combatiente1);
        combatiente1->imprimir(); //imprime su estado

        if (!combatiente1->estaVivo()) {
            delete combatiente1; //liberar memoria
            ejercito1.erase(ejercito1.begin() + idx1);
        }
    }

    std::cout << "\n┊┊┊┊💥┊*𝐑𝐄𝐒𝐔𝐋𝐓𝐀𝐃𝐎𝐒 𝐃𝐄𝐋 𝐂𝐎𝐌𝐁𝐀𝐓𝐄*┊💥┊┊┊┊" << std::endl;
    if (ejercito1.empty()) {
        std::cout << "¡El ejército 2 ha ganado!" << std::endl;
        imprimirEjercito(ejercito2);
    } else {
        std::cout << "¡El ejército 1 ha ganado!" << std::endl;
        imprimirEjercito(ejercito1);
    }
}

//MAIN PRINCIPAL 

int main() {
    //Crear los vectores 
    std::vector<Combatiente*> ejercito1;
    std::vector<Combatiente*> ejercito2;

    try { 
        //cargar los combatientes 
        cargarEjercito("ejercito1.txt", ejercito1);
        cargarEjercito("ejercito2.txt", ejercito2);
    } catch (const std::exception &e) { //si es que ocurre una excepcion (runtime_error)
        std::cerr << e.what() << std::endl;
        return 1; //el programa no sigue y termian en error
    }
    //inicializar la semilla para los números aleatorios
    std::srand(static_cast<unsigned int>(std::time(0))); 

    std::cout << "\n･☆･﹋EJERCITO 1﹋･☆･\n"<< std::endl;
    imprimirEjercito(ejercito1);

    std::cout << "\n･☆･﹋EJERCITO 2﹋･☆･\n"<< std::endl;
    imprimirEjercito(ejercito2);

    batalla(ejercito1, ejercito2); //BATALLA

    // Liberar memoria
    for (auto* combatiente : ejercito1) {
        delete combatiente;
    }
    for (auto* combatiente : ejercito2) {
        delete combatiente;
    }

    return 0; //fin del programa
}

//PRUEBAS POSTERIORES (3)
//primera prueba sin herencia
/*int main() {
    Combatiente harley(100, 20, 5); // Crear una instancia de Combatiente en este caso harley quinn
    harley.imprimir();

    // Crear otro combatiente para probar el ataque
    Combatiente enemigo(80, 15, 3);
    harley.atacar(enemigo);
    enemigo.imprimir();

    return 0;
}
*/

//segunda prueba con herencia 

/*int main() {
    // Crear instancias de cada clase derivada
    HarleyQuinn harley(120, 15, 5, 20, true);
    Gatubela gatubela(100, 12, 4, 0.25, 10);
    HiedraVenenosa hiedra(110, 14, 6, 30);

    // Imprimir características de cada combatiente
    std::cout << "\n･☆･﹋﹋﹋﹋𝐂𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐢𝐬𝐭𝐢𝐜𝐚𝐬 𝐝𝐞𝐥 𝐜𝐨𝐦𝐛𝐚𝐭𝐢𝐞𝐧𝐭𝐞﹋﹋﹋﹋･☆･\n";
    harley.imprimir();
    gatubela.imprimir();
    hiedra.imprimir();

    // Simulación de ataques
    std::cout << "\n══════》♡》♡》♡》♡》♡》𝐏𝐄𝐋𝐄𝐀《♡《♡《♡《♡《♡《══════\n";
    harley.atacar(gatubela);
    gatubela.atacar(harley);
    hiedra.atacar(gatubela);
    hiedra.atacar(harley);
    harley.atacar(hiedra);
    
    std::cout << "\n┊┊┊┊💥┊*𝐑𝐄𝐒𝐔𝐋𝐓𝐀𝐃𝐎𝐒 𝐃𝐄𝐋 𝐂𝐎𝐌𝐁𝐀𝐓𝐄*┊💥┊┊┊┊\n";
    harley.imprimir();
    gatubela.imprimir();
    hiedra.imprimir();

    return 0;
}*/

//tercera implementación

//Crea un vector de apuntadores a Combatiente/Unidad
/*int main () {
    std::vector<Combatiente*> combatientes; //vector 
// Manejo de excepciones al crear objetos dinámicamente
    try {
//crear objetos de manera dinamica (3) usando push back
    combatientes.push_back(new HarleyQuinn()); 
    combatientes.push_back(new Gatubela());
    combatientes.push_back(new HiedraVenenosa());

//manejo de excepcion     
    } catch (const std::bad_alloc &e) { //capturar std::bad_alloc si falla la asignacion de memoria, predetermiando de c++
        std::cerr << "Error al asignar memoria para un nuevo objeto: " << e.what() << std::endl; //mensaje
       //continua el programa
    }
//si no se puede continuar terminar el programa
    if (combatientes.empty()) {
        std::cerr << "No se pudieron crear los combatientes. Terminando el programa." << std::endl;
        return 1;
    }

//modificar niveles 
    combatientes[0]->setNivel(10); // Modificar el nivel del primer combatiente
    combatientes[1]->setNivel(1); // Modificar el nivel del segundo combatiente
    combatientes[2]->setNivel(4); // Modificar el nivel del tercer combatiente

//pruebas con un for 
//imprimir los personajes primero 
std::cout << "\n･☆･﹋﹋﹋﹋𝐂𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐢𝐬𝐭𝐢𝐜𝐚𝐬 𝐝𝐞𝐥 𝐜𝐨𝐦𝐛𝐚𝐭𝐢𝐞𝐧𝐭𝐞﹋﹋﹋﹋･☆･\n" << std::endl;
for (auto* combatiente : combatientes) {//iterar sobre cada combatiente en el vector
    std::cout << *combatiente << std::endl;
    }*/

/*Ataques I
std::cout << "\nAtaques:" << std::endl;
    for (size_t i = 1; i < combatientes.size(); ++i) {
        combatientes[0]->atacar(*combatientes[i]);
        combatientes[i]->imprimir();
    }
*/

//ataques multiples a los personajes II
/*const size_t numRondas = 3; //determinar un nmero de rondas de ataques
std::cout << "\n══════》♡》♡》♡》♡》♡》𝐏𝐄𝐋𝐄𝐀《♡《♡《♡《♡《♡《══════\n" << std::endl;
//Bucle para realizar multiples rondas de ataques
for (size_t ronda = 0; ronda < numRondas; ++ronda) { //iterar dependiendo el numero de rondas establecido
    std::cout << "\nRonda " << (ronda + 1) << ":" << std::endl; //imprimir -1 indx
    for (size_t i = 0; i < combatientes.size(); ++i) {//iterar sobre cada combatiente dentro del vector
        //el combatiente en la posición i ataca a los otros
        for (size_t j = 0; j < combatientes.size(); ++j) {//iterar nuevamente sobre cada combatiente (2)para los ataques
            if (i != j) {// Asegurarse de que el combatiente no se ataque a si mismo
                //imprimir informacin sobre el ataque
                std::cout << "Ataque de " << *combatientes[i] << " a " << *combatientes[j] << ":" << std::endl;
                combatientes[i]->atacar(*combatientes[j]); //el combatiente en i ataca al combatiente en j
                combatientes[j]->imprimir(); // Imprimir estado después del ataque
            } //se repite hasta que terminen las rondas
        }
    }
}
// Imprimir estado después de todos los ataques
std::cout << "\n┊┊┊┊💥┊*𝐑𝐄𝐒𝐔𝐋𝐓𝐀𝐃𝐎𝐒 𝐃𝐄𝐋 𝐂𝐎𝐌𝐁𝐀𝐓𝐄*┊💥┊┊┊┊\n"<< std::endl;
for (auto* combatiente : combatientes) {
    combatiente->imprimir();
}

//prueba de la sobrecarga
std::cout << "\nPrueba de sobrecarga de operadores:" << std::endl;
std::cout << *combatientes[0] << std::endl;

//LIBERAR MEMORIA
  for (auto* combatiente : combatientes) {
        delete combatiente;
    }

    return 0;

//sin sobrecarga std::cout << "Combatiente - Vida Máxima: " << combatientes[0]->getVida()
          //<< ", Salud Actual: " << combatientes[0]->getSalud()
          //<< ", Ataque: " << combatientes[0]->getAtaque()
          //<< ", Nivel: " << combatientes[0]->getNivel() << std::endl;


}*/

