#pragma once

class Player;
/// Klasa abstrakcyjna polecenia steruj¹cego graczem
/// Udostêpnia interfejs do wykonania dowolnej akcji na obiekcie gracza
class Command {
public:
    /// Wirtualny destruktor
    virtual ~Command() = default;

    /// Wykonuje polecenie na przekazanym obiekcie gracza
    /// Musi byæ zaimplementowane w klasach pochodnych
    virtual void Execute(Player& player) = 0;
};