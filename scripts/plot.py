import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

def calc_rmse(df, truth):
    error = np.sqrt(
        (df["x"] - truth["x"])**2 +
        (df["y"] - truth["y"])**2
    )
    return np.sqrt(np.mean(error**2))

def main():
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    raw_path = os.path.join(BASE_DIR, "data/raw.csv")
    filtered_path = os.path.join(BASE_DIR, "data/filtered.csv")
    truth_path = os.path.join(BASE_DIR, "data/truth.csv")

    # =========================
    # ファイルチェック
    # =========================
    for path, name in [
        (raw_path, "raw.csv"),
        (filtered_path, "filtered.csv"),
        (truth_path, "truth.csv")
    ]:
        if not os.path.exists(path):
            print(f"{name} not found")
            return

    # =========================
    # 読み込み & ソート
    # =========================
    df_raw = pd.read_csv(raw_path).sort_values("timestamp").reset_index(drop=True)
    df_filtered = pd.read_csv(filtered_path).sort_values("timestamp").reset_index(drop=True)
    df_truth = pd.read_csv(truth_path).sort_values("timestamp").reset_index(drop=True)

    # 長さ揃え
    min_len = min(len(df_raw), len(df_filtered), len(df_truth))
    df_raw = df_raw.iloc[:min_len]
    df_filtered = df_filtered.iloc[:min_len]
    df_truth = df_truth.iloc[:min_len]

    # =========================
    # 時間（相対秒）
    # =========================
    t0 = df_truth["timestamp"].iloc[0]
    time = (df_truth["timestamp"] - t0) / 1e9

    # =========================
    # RMSE計算
    # =========================
    rmse_raw = calc_rmse(df_raw, df_truth)
    rmse_filtered = calc_rmse(df_filtered, df_truth)
    improve_rate = (rmse_raw - rmse_filtered) / rmse_raw * 100

    # =========================
    # グラフ①：位置比較（x）
    # =========================
    plt.figure(figsize=(8, 4))

    plt.plot(time, df_truth["x"], label="truth")
    plt.plot(time, df_raw["x"], label="raw", linestyle="--", alpha=0.8)
    plt.plot(time, df_filtered["x"], label="filtered")

    plt.xlabel("time (s)")
    plt.ylabel("position x")
    plt.title(f"Position Comparison (RMSE improved {improve_rate:.1f}%)")
    plt.legend()
    plt.grid()
    plt.tight_layout()

    output_plot = os.path.join(BASE_DIR, "data/plot.png")
    plt.savefig(output_plot)

    print(f"plot saved to {output_plot}")

    # =========================
    # グラフ②：誤差（truthとの差）
    # =========================
    raw_error = np.sqrt(
        (df_raw["x"] - df_truth["x"])**2 +
        (df_raw["y"] - df_truth["y"])**2
    )

    filtered_error = np.sqrt(
        (df_filtered["x"] - df_truth["x"])**2 +
        (df_filtered["y"] - df_truth["y"])**2
    )

    plt.figure(figsize=(8, 4))

    plt.plot(time, raw_error, label="raw error", linestyle="--", alpha=0.8)
    plt.plot(time, filtered_error, label="filtered error")

    plt.xlabel("time (s)")
    plt.ylabel("error (distance)")
    plt.title(f"Error Comparison (RMSE raw={rmse_raw:.2f}, filtered={rmse_filtered:.2f})")
    plt.legend()
    plt.grid()
    plt.tight_layout()

    output_diff = os.path.join(BASE_DIR, "data/diff.png")
    plt.savefig(output_diff)

    print(f"diff saved to {output_diff}")

if __name__ == "__main__":
    main()