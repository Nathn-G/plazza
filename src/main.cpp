/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** main of Plazza
*/

#include "main.hpp"

int main(int ac, char *av[])
{
    Plazza::Reception reception;

    if (ac != 4)
        return (84);
    try {
        reception.init(av[1], av[2], av[3]);
        reception.run();
    } catch (Plazza::Error::Convert &err) {
        err.printError();
        return (84);
    } catch (Plazza::Error::Fork &err) {
        err.printError();
        return (84);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    return (0);
}