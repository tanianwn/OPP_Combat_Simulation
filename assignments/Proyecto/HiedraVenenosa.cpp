#include "HiedraVenenosa.hpp"


HiedraVenenosa::HiedraVenenosa() : Combatiente(), toxikinesis(50) {}

HiedraVenenosa::HiedraVenenosa(int v, int a, int n, int t) : Combatiente(v, a, n), toxikinesis(t) {}

//getter
int HiedraVenenosa::getToxikinesis() const {
    return toxikinesis;
}

//setters
void HiedraVenenosa::setToxikinesis(int t) {
    toxikinesis = t;
}

//metodos
bool HiedraVenenosa::estaVivo() {
    return getSalud() > 0;
}

//recibe ataque
void HiedraVenenosa::recibeAtaque(int ptosAtaque) {
Combatiente::recibeAtaque(ptosAtaque);
if (!estaVivo()) { //recibe ataque con el esta vivo
    if (toxikinesis > 20) {
        setSalud(4); //recupera 4 puntos de salud
        toxikinesis = 0; //consume toda la toxikinesis
        std::cout << "Hiedra Venenosa ha usado su toxikinesis para una última oportunidad de vida!" << std::endl;
        } else {
            std::cout << "Hiedra Venenosa ha sido derrotada" << std::endl;
        }
    }
}


//atacar
//incorpora toxikinesis para ajustar el daño
//toxikinesis se basa en el porcentaje de salud del atacante

void HiedraVenenosa::atacar(Combatiente &objetivo) {
    int ptosAtaque;
    if (objetivo.getNivel() > getNivel()) {
        ptosAtaque = std::rand() % (getAtaque() / 2) + 1;
    } else {
        ptosAtaque = std::rand() % (getAtaque() / 2) + (getAtaque() / 2);
    }
    //toxikinesis
    ptosAtaque += toxikinesis;
    objetivo.recibeAtaque(ptosAtaque);
    toxikinesis -= 10;
    if (toxikinesis < 0) toxikinesis = 0;

    if (getSalud() < getVida() * 0.5) { //vida al usar toxikinesis
        toxikinesis *= 0.9;
    }
}

//imprimir
void HiedraVenenosa::imprimir() const {
    std::cout << "Hiedra Venenosa - Vida Máxima: " << getVida()
              << ", Salud Actual: " << getSalud()
              << ", Ataque: " << getAtaque()
              << ", Nivel: " << getNivel()
              << ", Toxikinesis: " << toxikinesis << std::endl;
    imprimirBarraVida();
}
