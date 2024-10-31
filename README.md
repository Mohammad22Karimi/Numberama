# Numberama Game

Numberama Game is a simple C++ game project that uses several files, including `players.txt`, which stores player information.

## Files

- **numberama.cpp**: The main program file containing the C++ code for the game.
- **players.txt**: A text file that stores player information, such as name, score, and level. This file is read by the game to display player details.

## Sample Data in `players.txt`

The content of the `players.txt` file follows this format:


## How to Run

1. First, compile the program:

    ```bash
    g++ numberama.cpp -o numberama
    ```

2. Then, run the program:

    ```bash
    ./numberama
    ```

## Dependencies

This project requires only a C++ compiler (such as g++) to compile and run and has no additional external dependencies.

## Important Notes

- If you encounter the error `time not declared`, ensure that `#include <ctime>` is added at the top of `numberama.cpp`.
- The `players.txt` file should be in the same directory as the program to ensure player information is correctly loaded.

## Contributing

If you'd like to contribute to this project, please feel free to submit a Pull Request or open an Issue.

## License

This project is licensed under the MIT License.
