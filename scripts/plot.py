import pandas as pd
import matplotlib.pyplot as plt
import argparse
import os

def main():
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    parser = argparse.ArgumentParser()
    parser.add_argument("--input", default=os.path.join(BASE_DIR, "data/output.csv"))
    parser.add_argument("--output", default=os.path.join(BASE_DIR, "data/plot.png"))

    args = parser.parse_args()

    df = pd.read_csv(args.input)

    plt.figure()
    plt.plot(df["x"], df["y"])
    plt.title("Trajectory")
    plt.xlabel("x")
    plt.ylabel("y")

    os.makedirs(os.path.dirname(args.output), exist_ok=True)
    plt.savefig(args.output)
    print(f"Saved: {args.output}")

if __name__ == "__main__":
    main()