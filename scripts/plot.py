import pandas as pd
import matplotlib.pyplot as plt
import argparse
import os

def main():
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    raw_path = os.path.join(BASE_DIR, "data/raw.csv")
    filtered_path = os.path.join(BASE_DIR, "data/filtered.csv")

    if not os.path.exists(raw_path):
        print("raw.csv not found")
        return

    if not os.path.exists(filtered_path):
        print("filtered.csv not found")
        return

    df_raw = pd.read_csv(raw_path)
    df_raw = df_raw.sort_values("timestamp").reset_index(drop=True)
    df_filtered = pd.read_csv(filtered_path)
    df_filtered = df_filtered.sort_values("timestamp").reset_index(drop=True)

    t0 = df_raw["timestamp"].iloc[0]
    time_raw = (df_raw["timestamp"] - t0) / 1e9
    time_filtered = (df_filtered["timestamp"] - t0) / 1e9

    # === 比較 ===
    plt.figure(figsize=(8, 4))

    plt.plot(time_raw, df_raw["x"], label="raw_x", alpha=0.5)   # メモ：ここのalphaは見た目の透明度の指定なので処理には関係なし
    plt.plot(time_filtered, df_filtered["x"], label="filtered_x")

    plt.xlabel("time (relative)")
    plt.ylabel("x")
    plt.title("Raw vs Filtered")
    plt.legend()
    plt.title("Raw vs Filtered")
    plt.tight_layout()

    output_plot = os.path.join(BASE_DIR, "data/plot.png")
    plt.savefig(output_plot)

    print(f"plot saved to {output_plot}")

    # === 差分 ===
    plt.figure(figsize=(8, 4))

    diff = (df_raw["x"] - df_filtered["x"]).abs()

    plt.plot(time_raw, diff, label="difference")

    plt.xlabel("time (relative)")
    plt.ylabel("difference")
    plt.title("Difference")
    plt.legend()
    plt.title("Difference")
    plt.tight_layout()

    output_diff = os.path.join(BASE_DIR, "data/diff.png")
    plt.savefig(output_diff)

    print(f"diff saved to {output_diff}")

if __name__ == "__main__":
    main()