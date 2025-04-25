#!/usr/bin/env python3
import os, sys, subprocess, random, string

exe = "./megaphone"
for n in range(10000):
    length = random.randint(1, 64)
    payload = bytes(random.randint(1, 255) for _ in range(length))  # 0を除外
    try:
        subprocess.check_output([exe, payload], stderr=subprocess.STDOUT)
        # print("No crash with:", payload.hex())
    except subprocess.CalledProcessError:
        print("Crash with:", payload.hex())
        sys.exit(0)
print("No crash (safe implementation?)")
