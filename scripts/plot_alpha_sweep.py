import pandas as pd
import matplotlib.pyplot as plt
import glob
import os

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
data_dir = os.path.join(BASE_DIR, "data")

files = sorted(glob.glob(os.path.join(data_dir, "analysis_alpha_*.csv")))

alphas = []
rmses = []

for f in files:
    df = pd.read_csv(f)

    # ファイル名からalpha抽出
    alpha = float(os.path.basename(f).split("_")[-1].replace(".csv", ""))

    rmse = df["rmse_filtered"].iloc[0]

    alphas.append(alpha)
    rmses.append(rmse)

# =========================
# 最適alpha算出
# =========================
best_idx = rmses.index(min(rmses))
best_alpha = alphas[best_idx]
best_rmse = rmses[best_idx]

# =========================
# プロット
# =========================
plt.figure()

# best以外
other_alphas = []
other_rmses = []

for a, r in zip(alphas, rmses):
    if a != best_alpha:
        other_alphas.append(a)
        other_rmses.append(r)

# 線（全部）
plt.plot(alphas, rmses)

# 通常点
plt.scatter(other_alphas, other_rmses, label="others")

# best点
plt.scatter(best_alpha, best_rmse, s=150, label="best", zorder=3)

plt.xlabel("alpha")
plt.ylabel("RMSE")
plt.title(f"Alpha vs RMSE (best={best_alpha})")
plt.legend()
plt.grid()

output = os.path.join(data_dir, "alpha_vs_rmse.png")
plt.savefig(output)
plt.close()

print(f"saved to {output}")