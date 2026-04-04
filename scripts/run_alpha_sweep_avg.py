import os
import subprocess
import pandas as pd

alphas = [0.1, 0.3, 0.5, 0.7]
runs = 5

results = []

for alpha in alphas:
    rmses = []

    for i in range(runs):
        print(f"alpha={alpha}, {i+1}回目")

        subprocess.run([
            "./build/main",
            "--duration", "5",
            "--interval", "300",
            "--noise", "0.7",
            "--alpha", str(alpha)
        ])

        subprocess.run(["python3", "scripts/analyze.py"])

        df = pd.read_csv("data/analysis.csv")
        rmses.append(df["rmse_filtered"].iloc[0])

    avg_rmse = sum(rmses) / len(rmses)

    results.append({
        "alpha": alpha,
        "avg_rmse": avg_rmse
    })

df_out = pd.DataFrame(results)
df_out.to_csv("data/alpha_sweep_avg.csv", index=False)

print(df_out)