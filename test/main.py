import sys
import random
import subprocess
from datetime import datetime


def create_input_files(string_lens):
    alphabet = "abcdefghijklmnopqrstuvwxyz"

    for m, n in string_lens:
        rand_num = random.randint(0, n // 2)
        first = [random.choice(alphabet) for _ in range(int(m))]
        second = first[0 : (min(m, n) - rand_num)] + [
            random.choice(alphabet) for _ in range(1, rand_num)
        ]
        with open(f"{m}X{n}.txt", "w") as f:
            f.write(f"{str(''.join(first))} {str(''.join(second))}")


def run():
    string_lens = [
        (10, 10),
        (20, 20),
        (50, 50),
        (100, 100),
        (999, 999),
        (9999, 9999),
        (49999, 49999),
        (99999, 99999),
    ]
    create_input_files(string_lens)
    for m, n in string_lens:
        for num_threads in [2, 4, 8, 16]:
            outputs = []
            subprocess.run(["gcc", "-fopenmp", "main.c", "-o", "a.out"], check=True)
            print(f"Running matrix {m}X{n} with {num_threads} threads...")
            outputs.append(
                subprocess.run(
                    [
                        "./a.out",
                        f"{m}",
                        f"{n}",
                        f"{m}X{n}.txt",
                        f"{num_threads}",
                    ],
                    capture_output=True,
                    text=True,
                    check=True,
                ).stdout
            )
            with open("results.csv", "a") as f:
                now = datetime.now()
                f.write(f"{now},{num_threads},{m},{n},{outputs}\n")


if __name__ == "__main__":
    run()
