import pandas as pd
import numpy as np
import argparse
import os

def calc_stats(df):
    return {
        "x_std": df["x"].std(),
        "y_std": df["y"].std()
    }

def calc_rmse(df, truth):
    error = np.sqrt(
        (df["x"] - truth["x"])**2 +
        (df["y"] - truth["y"])**2
    )
    return np.sqrt(np.mean(error**2))

def main():
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    parser = argparse.ArgumentParser()
    parser.add_argument("--raw", default=os.path.join(BASE_DIR, "data/raw.csv"))
    parser.add_argument("--filtered", default=os.path.join(BASE_DIR, "data/filtered.csv"))
    parser.add_argument("--truth", default=os.path.join(BASE_DIR, "data/truth.csv"))
    parser.add_argument("--output", default=os.path.join(BASE_DIR, "data/analysis.csv"))

    args = parser.parse_args()

    # =========================
    # ファイル存在チェック
    # =========================
    for path, name in [
        (args.raw, "raw.csv"),
        (args.filtered, "filtered.csv"),
        (args.truth, "truth.csv")
    ]:
        if not os.path.exists(path):
            print(f"{name} not found")
            return

    # =========================
    # CSV読み込み
    # =========================
    df_raw = pd.read_csv(args.raw).sort_values("timestamp").reset_index(drop=True)
    df_filtered = pd.read_csv(args.filtered).sort_values("timestamp").reset_index(drop=True)
    df_truth = pd.read_csv(args.truth).sort_values("timestamp").reset_index(drop=True)

    # =========================
    # 長さ揃え（安全対策）
    # =========================
    min_len = min(len(df_raw), len(df_filtered), len(df_truth))
    df_raw = df_raw.iloc[:min_len]
    df_filtered = df_filtered.iloc[:min_len]
    df_truth = df_truth.iloc[:min_len]

    # =========================
    # 標準偏差（ノイズ指標）
    # =========================
    raw_stats = calc_stats(df_raw)
    filtered_stats = calc_stats(df_filtered)

    improve_x = raw_stats["x_std"] - filtered_stats["x_std"]
    improve_y = raw_stats["y_std"] - filtered_stats["y_std"]

    # =========================
    # RMSE（精度評価）
    # =========================
    rmse_raw = calc_rmse(df_raw, df_truth)
    rmse_filtered = calc_rmse(df_filtered, df_truth)
    rmse_improve = rmse_raw - rmse_filtered

    # =========================
    # 出力
    # =========================
    print("=== Standard Deviation ===")
    print("[RAW]", raw_stats)
    print("[FILTERED]", filtered_stats)

    print("=== Improvement (STD) ===")
    print("x:", improve_x)
    print("y:", improve_y)

    improve_rate = (rmse_raw - rmse_filtered) / rmse_raw * 100

    print("=== RMSE Evaluation ===")
    print(f"Raw        : {rmse_raw:.3f}")
    print(f"Filtered   : {rmse_filtered:.3f}")
    print(f"Improvement: {improve_rate:.1f}%")
    print(f"\nEMAフィルタによりRMSEが{improve_rate:.1f}%改善\n")

    # =========================
    # CSV保存
    # =========================
    result = pd.DataFrame({
        "raw_x_std": [raw_stats["x_std"]],
        "raw_y_std": [raw_stats["y_std"]],
        "filtered_x_std": [filtered_stats["x_std"]],
        "filtered_y_std": [filtered_stats["y_std"]],
        "improve_x": [improve_x],
        "improve_y": [improve_y],
        "rmse_raw": [rmse_raw],
        "rmse_filtered": [rmse_filtered],
        "rmse_improve": [rmse_improve]
    })

    os.makedirs(os.path.dirname(args.output), exist_ok=True)
    result.to_csv(args.output, index=False)

if __name__ == "__main__":
    main()