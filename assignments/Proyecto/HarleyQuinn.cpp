#include "HarleyQuinn.hpp"

HarleyQuinn::HarleyQuinn() : Combatiente(100, 10, 1), fuerza(10), inmunidadToxinas(true) {} //constructor pot default

HarleyQuinn::HarleyQuinn(int v, int a, int n, int f, bool it) : Combatiente(v, a, n), fuerza(f), inmunidadToxinas(it) {} //constructor con parametros

//getters
int HarleyQuinn::getFuerza() const {
    return fuerza;
}

bool HarleyQuinn::getInmunidadToxinas() const {
    return inmunidadToxinas;
}

//setters
void HarleyQuinn::setFuerza(int f) {
    fuerza = f;
}

void HarleyQuinn::setInmunidadToxinas(bool it) {
    inmunidadToxinas = it;
}

//metodos
bool HarleyQuinn::estaVivo() {
    return getSalud() > 0;
}

//inmunidad a toxinas contra hiedra, recibe ataque
void HarleyQuinn::recibeAtaque(int ptosAtaque) {
    if (inmunidadToxinas) {
        ptosAtaque /= 2;
    }
    Combatiente::recibeAtaque(ptosAtaque); //recibe ataque con el esta vivo
    if (!estaVivo()) {
        if (fuerza > 20) {
            setSalud(4); //recupera 4 puntos de salud
            fuerza = 0; //consume toda la fuerza
            std::cout << "Harley ha utilizado toda la fuerza para una última oportunidad de vida!" << std::endl;
            } else {
                std::cout << "Harley Quinn ha sido derrotada" << std::endl;
                }
            }
        }

//ataque

// particularidades del ataque de harley: Particularidades:
//1 Usa el atributo fuerza para incrementar el daño del ataque, es decir añade su fuerza al daño calculado
void HarleyQuinn::atacar(Combatiente &objetivo) {
    int ptosAtaque;
    if (objetivo.getNivel() > getNivel()) {
        ptosAtaque = std::rand() % (getAtaque() / 2) + 1;
    } else {
        ptosAtaque = std::rand() % (getAtaque() / 2) + (getAtaque() / 2);
    }
    ptosAtaque += fuerza;
    objetivo.recibeAtaque(ptosAtaque);
}

//imprimir
void HarleyQuinn::imprimir() const {
    std::cout << "Harley Quinn - Vida Máxima: " << getVida()
              << ", Salud Actual: " << getSalud()
              << ", Ataque: " << getAtaque()
              << ", Nivel: " << getNivel()
              << ", Fuerza: " << fuerza
              << ", Inmunidad a Toxinas: " << (inmunidadToxinas ? "Sí" : "No") << std::endl;
    imprimirBarraVida();
}
