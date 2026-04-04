import os
import subprocess
import shutil

alphas = [0.1, 0.3, 0.5, 0.7]

for alpha in alphas:
    print(f"alpha={alpha}")

    subprocess.run([
        "./build/main",
        "--duration", "5",
        "--interval", "300",
        "--noise", "0.7",
        "--alpha", str(alpha)
    ])

    subprocess.run(["python3", "scripts/analyze.py"])

    shutil.copy("data/analysis.csv", f"data/analysis_alpha_{alpha}.csv")
    shutil.copy("data/filtered.csv", f"data/filtered_alpha_{alpha}.csv")