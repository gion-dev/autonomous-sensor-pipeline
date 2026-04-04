import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
data_path = os.path.join(BASE_DIR, "data/alpha_sweep_avg.csv")

# =========================
# CSV読み込み
# =========================
if not os.path.exists(data_path):
    print("alpha_sweep_avg.csv not found")
    exit()

df = pd.read_csv(data_path)

# alpha順にソート
df = df.sort_values("alpha").reset_index(drop=True)

alphas = df["alpha"].tolist()
rmses = df["avg_rmse"].tolist()

# =========================
# 最適alpha
# =========================
best_idx = int(np.argmin(rmses))
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

# 線
plt.plot(alphas, rmses)

# 通常点
plt.scatter(other_alphas, other_rmses, label="others")

# best点
plt.scatter(best_alpha, best_rmse, s=150, label="best", zorder=3)

plt.xlabel("alpha")
plt.ylabel("Average RMSE")
plt.title(f"Alpha vs Average RMSE (best={best_alpha})")
plt.legend()
plt.grid()
plt.tight_layout()

# 保存
output = os.path.join(BASE_DIR, "data/alpha_vs_avg_rmse.png")
plt.savefig(output)
plt.close()

print(f"saved to {output}")