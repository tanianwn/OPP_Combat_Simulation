#include "Gatubela.hpp"
#include <cstdlib>
#include <ctime> // para el tiempo actual

Gatubela::Gatubela() : Combatiente(), bloqueo(0.2f), garras(10), contadorAtaques(0) {}

Gatubela::Gatubela(int v, int a, int n, float b, int g) : Combatiente(v, a, n), bloqueo(b), garras(g), contadorAtaques(0) {}

//getters
float Gatubela::getBloqueo() const {
    return bloqueo;
}

int Gatubela::getGarras() const {
    return garras;
}

//setters
void Gatubela::setBloqueo(float b) {
    bloqueo = b;
}

void Gatubela::setGarras(int g) {
    garras = g;
}

//metodos
//esta vivo
bool Gatubela::estaVivo(){
    return getSalud() > 0; 
}

//bloqueo
void Gatubela::recibeAtaque(int ptosAtaque) {
    float probabilidadBloqueo = static_cast<float>(std::rand()) / RAND_MAX;
    if (probabilidadBloqueo < bloqueo) {
        std::cout << "Gatubela ha bloqueado el ataque ❌" << std::endl;
        return;
    }
    Combatiente::recibeAtaque(ptosAtaque); //recibe ataque con el esta vivo
    if (!estaVivo()) {
        if (garras > 9) {
            setSalud(4); //recupera 4 puntos de salud
            garras = 0; //consume toda la fuerza
            std::cout << "Gatubela ha utilizado las garras que le quedaba para una última oportunidad de vida!" << std::endl;
            } else {
                std::cout << "Gatubela ha sido derrotada" << std::endl;
                }
            }
        }

//ataque
//particularidades 
//Incluye un incremento del daño cada dos ataques
//aumenta el daño de manera progresiva en funcion del número de ataques realizados

void Gatubela::atacar(Combatiente &objetivo) { 
    std::srand(std::time(0)); //semilla
    contadorAtaques++; //incrementar contador de ataques
    int ptosAtaque;
    if (objetivo.getNivel() > getNivel()) {
        ptosAtaque = std::rand() % (getAtaque() / 2) + 1;
    } else {
        ptosAtaque = std::rand() % (getAtaque() / 2) + (getAtaque() / 2);
    }
    if (contadorAtaques % 2 == 0) {
        ptosAtaque += ptosAtaque * 0.10; //aumenta 10% el daño
    }
    objetivo.recibeAtaque(ptosAtaque);
}


//imprimir
void Gatubela::imprimir() const {
    std::cout << "Gatubela - Vida Máxima: " << getVida()
              << ", Salud Actual: " << getSalud()
              << ", Ataque: " << getAtaque()
              << ", Nivel: " << getNivel()
              << ", Bloqueo: " << bloqueo * 100 << "%"
              << ", Garras: " << garras << std::endl;
    imprimirBarraVida();
}
