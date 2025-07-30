//GEnera la implementación de la clase base Personaje

#include <cstdlib> //random,  en función del tiempo actual
#include <ctime> // para el tiempo actual
#include "Combatiente.hpp"


//Public
//Constructor 
Combatiente::Combatiente(){
    vida = 100;
    salud = 100; //inicializa los valores
    ataque = 10;
    nivel = 1; 
}

//Constructor con Parametros
Combatiente::Combatiente (int v, int a, int n){
    vida= v; 
    salud = v; 
    ataque = a;
    nivel = n; // valores que pondrá el usuario
}

//
Combatiente::~Combatiente(){ //destructor
}

//setters y getters (Metodos)   

//getters para acceder a los valores
int Combatiente::getVida() const{
    return vida;   
}

int Combatiente::getSalud() const {
    return salud;
}

int Combatiente::getAtaque() const {
    return ataque;
}

int Combatiente::getNivel() const {
    return nivel;
}

//Setters para modificar los valores
void Combatiente::setVida(int v) {
    vida = v;
    if (salud > vida) {
        salud = vida;
    }
}

void Combatiente::setSalud(int s) {
    if (s < 0) {
        salud = 0;
    } else if (s > vida) {
        salud = vida;
    } else {
        salud = s;
    }
}

void Combatiente::setAtaque(int a) {
    ataque = a;
}

void Combatiente::setNivel(int n) {
    nivel = n;
}

//metodos
//metodo para calcular el porcentaje de salud
int Combatiente::calcularPorcentajeSalud() const {
    if (vida <= 0) return 0;
    return static_cast<int>(static_cast<float>(salud) / vida * 100);
}

// Sobrecarga del operador de flujo de salida
std::ostream& operator<<(std::ostream& os, const Combatiente& combatiente) {
    combatiente.imprimir();
    return os;
    }
//metodo para imprimir la barra de vida
void Combatiente::imprimirBarraVida() const {
    int porcentajeSalud = calcularPorcentajeSalud();
    //asegurar rango
    if (porcentajeSalud < 0) porcentajeSalud = 0;
    if (porcentajeSalud > 100) porcentajeSalud = 100;

    int barrasLlenas = porcentajeSalud / 5;
    int barrasVacias = 20 - barrasLlenas;
    std::string barraVida(barrasLlenas, '%');
    barraVida += std::string(barrasVacias, '=');
    std::cout << "Barra de vida: " << barraVida << std::endl;
}

//metodo para recibir ataque
void Combatiente::recibeAtaque(int ptosAtaque) {
    setSalud(salud - ptosAtaque);
}

//metodo para atacar a otro combatiente
/*void Combatiente::atacar(Combatiente &objetivo) {
    std::srand(std::time(0)); // Inicializa la semilla para números aleatorios
    int ptosAtaque;
    if (objetivo.getNivel() > nivel) {
        //si el objetivo tiene un nivel más alto, se ataca con un número aleatorio entre 1 y la mitad de los puntos de ataque
        ptosAtaque = std::rand() % (ataque / 2) + 1;
    } else {
        //si el objetivo tiene un nivel más bajo o igual, se ataca con un número aleatorio entre la mitad y el total de los puntos de ataque
        ptosAtaque = std::rand() % (ataque / 2) + (ataque / 2);
    }
    //el objetivo recibe el ataque
    objetivo.recibeAtaque(ptosAtaque);
}*/

//metodo para imprimir características del combatiente y su barra de vida
void Combatiente::imprimir() const {
    std::cout << "Combatiente - Vida Máxima: " << vida
              << ", Salud Actual: " << salud
              << ", Ataque: " << ataque
              << ", Nivel: " << nivel << std::endl;
    imprimirBarraVida();
}
