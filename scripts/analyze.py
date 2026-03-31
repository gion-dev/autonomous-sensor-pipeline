import pandas as pd
import argparse
import os

def calc_stats(df):
    return {
        "x_std": df["x"].std(),
        "y_std": df["y"].std()
    }

def main():
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    parser = argparse.ArgumentParser()
    parser.add_argument("--raw", default=os.path.join(BASE_DIR, "data/raw.csv"))
    parser.add_argument("--filtered", default=os.path.join(BASE_DIR, "data/filtered.csv"))
    parser.add_argument("--output", default=os.path.join(BASE_DIR, "data/analysis.csv"))

    args = parser.parse_args()

    # ファイル存在チェック
    if not os.path.exists(args.raw):
        print("raw.csv not found")
        return

    if not os.path.exists(args.filtered):
        print("filtered.csv not found")
        return

    df_raw = pd.read_csv(args.raw)
    df_raw = df_raw.sort_values("timestamp").reset_index(drop=True)
    df_filtered = pd.read_csv(args.filtered)
    df_filtered = df_filtered.sort_values("timestamp").reset_index(drop=True)

    raw_stats = calc_stats(df_raw)
    filtered_stats = calc_stats(df_filtered)

    # 改善量
    improve_x = raw_stats["x_std"] - filtered_stats["x_std"]
    improve_y = raw_stats["y_std"] - filtered_stats["y_std"]

    print("=== Standard Deviation ===")
    print("[RAW]", raw_stats)
    print("[FILTERED]", filtered_stats)

    print("=== Improvement ===")
    print("x:", improve_x)
    print("y:", improve_y)
    print("===================")

    result = pd.DataFrame({
        "raw_x_std": [raw_stats["x_std"]],
        "raw_y_std": [raw_stats["y_std"]],
        "filtered_x_std": [filtered_stats["x_std"]],
        "filtered_y_std": [filtered_stats["y_std"]],
        "improve_x": [improve_x],
        "improve_y": [improve_y]
    })

    os.makedirs(os.path.dirname(args.output), exist_ok=True)
    result.to_csv(args.output, index=False)

if __name__ == "__main__":
    main()