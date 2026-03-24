import pandas as pd
import argparse
import os

def main():
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    parser = argparse.ArgumentParser()
    parser.add_argument("--input", default=os.path.join(BASE_DIR, "data/output.csv"))
    parser.add_argument("--output", default=os.path.join(BASE_DIR, "data/analysis.csv"))

    args = parser.parse_args()

    df = pd.read_csv(args.input)

    x_std = df["x"].std()
    y_std = df["y"].std()

    print("=== Standard Deviation ===")
    print("x std:", x_std)
    print("y std:", y_std)
    print("==========================")

    # DataFrameにまとめる
    result = pd.DataFrame({
        "x_std": [x_std],
        "y_std": [y_std]
    })

    # 出力
    os.makedirs(os.path.dirname(args.output), exist_ok=True)
    result.to_csv(args.output, index=False)

if __name__ == "__main__":
    main()