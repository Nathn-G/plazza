# Plazza

The Plazza is an introduction project to concurrent programming.
It allowed me to develop skills in  :
- thread and mutexs
- The IPC (semaphores, message queues etc.)


## Subject

You have to take pizza ordering from user input and manage processes (kitchens) to efficiently cook pizzas.

## Usage

You'll need [make](https://www.gnu.org/software/make/) to compile the project.

```sh
$ git clone https://github.com/Nathn-G/plazza.git
$ cd plazza
$ make
$ ./plazza 2 5 2000
```

| Argument   | Explanation                 |
|:----------:|-----------------------------|
| first      | Cooking time multiplier.    |
| second     | Number of cook per kitchen. |
| third      | Ingredient restock couldown.|


## Documentation

### How to order a pizza ?

While the plazza is running you can order a pizza thanks to the shell

The order format is `[PIZZA NAME] [SIZE] x[QUANTITY]`, for example : `americana XXL x15`

`[PIZZA NAME]` can be regina, margarita, americana or fantasia

`[SIZE]` can be S, M, L, XL, XXL

You can do multiple order at the same time with `;` : `americana XXL x15 ; fantasia L x10`
In multiple order, if there is an invalid pizza in the line, it will be **ignored**.

You can follow the progress of the kitchen by typing `status`

If a kitchen doesn't receive an order, it will close after **5 seconds**.

## Credits

**Nathan Guiu**  https://github.com/Nathn-G</br>
**Mathis Lorenzo**  https://github.com/mathis-lorenzo</br>
**Hugo Marrassé**  https://github.com/pulk66-s