#!/bin/zsh
# tester.sh — Ford–Johnson (merge-insertion) テスター（Vector/Deque 両対応・色付き）
# n=1..21 を各20回:
#   1) Vector / Deque の出力が昇順か
#   2) 比較回数 ≤ 画像表の理論値 F(n)
# を確認し、各 n ごとに横一列で色付き表示します。

set -u

script_dir="$(cd "$(dirname "$0")" && pwd)"
cd "$script_dir" || exit 1

echo "[build] make ..."
make -s || { echo "build failed"; exit 1; }

bin="./PmergeMe"
if [ ! -x "$bin" ]; then
  echo "binary not found: $bin" >&2
  exit 1
fi

# 画像表の F(n): n=1..21
typeset -A F
F[1]=0   F[2]=1   F[3]=3   F[4]=5   F[5]=7
F[6]=10  F[7]=13  F[8]=16  F[9]=19  F[10]=22  F[11]=26
F[12]=30 F[13]=34 F[14]=38 F[15]=42 F[16]=46 F[17]=50
F[18]=54 F[19]=58 F[20]=62 F[21]=66

# ANSI colors (printfで使える通常のエスケープに修正)
GREEN=$'\e[32m'
RED=$'\e[31m'
YELLOW=$'\e[33m'
GRAY=$'\e[90m'
BOLD=$'\e[1m'
RESET=$'\e[0m'

# 指定セクション（"Vector" または "Deque"）の After 行を取得
extract_after_line() {
  awk -v sec="$1" '
    BEGIN{show=0}
    $0 ~ "=== "sec" ===" {show=1}
    show && /^After:/ {print; exit}
  '
}

# 指定セクションの「比較回数 : X」を取得
extract_cmp() {
  awk -v sec="$1" '
    BEGIN{show=0}
    $0 ~ "=== "sec" ===" {show=1}
    show && /比較回数/ {print $NF; exit}
  '
}

is_sorted_non_decreasing() {
  local prev=""
  for v in "$@"; do
    if [ -n "$prev" ] && [ "$prev" -gt "$v" ]; then
      return 1
    fi
    prev="$v"
  done
  return 0
}

# 1ケース実行（section="Vector"|"Deque"）→ "status cmp" を返す
# status: 0=OK, 1=sorted NG, 2=cmp 超過, 3=cmp 取れず
run_one() {
  local n="$1" section="$2"
  # 一意な乱数 n 個（BSD系）
  local nums
  nums=( $(jot 100000 1 | sort -R | head -n "$n") )

  local out
  out=$(PMERGE_DEBUG= "$bin" ${nums[@]} 2>&1)

  local after_line arr
  after_line=$(print -r -- "$out" | extract_after_line "$section")
  arr=( ${(z)after_line} )
  if [[ ${#arr[@]} -gt 0 && ${arr[1]} == "After:" ]]; then
    arr=( ${arr[@]:1} )
  fi
  if [[ ${#arr[@]} -gt 0 && ${arr[-1]} == "[...]" ]]; then
    arr=( ${arr[@]:0:-1} )
  fi

  if ! is_sorted_non_decreasing ${arr[@]}; then
    echo "1 0"
    return
  fi

  local cmp
  cmp=$(print -r -- "$out" | extract_cmp "$section")
  if [[ -z "$cmp" ]]; then
    echo "3 0"
    return
  fi

  local cap="${F[$n]}"
  if (( cmp > cap )); then
    echo "2 $cmp"
  else
    echo "0 $cmp"
  fi
}

# 1セクション（Vector/Deque）分を横並び表示
run_block() {
  local n="$1" section="$2"
  local cap="${F[$n]}"

  # 見出し（例: n=7 [Vector] F(n)=13:）
  printf "${BOLD}n=%d${RESET} [%s] cmp vs F(n)=${BOLD}%d${RESET}: " "$n" "$section" "$cap"

  typeset -a cmps; cmps=()
  local per_fail=0

  for trial in {1..20}; do
    read stat cmp < <(run_one "$n" "$section")
    if [[ "$stat" == "0" ]]; then
      printf "${GREEN}%2d${RESET} " "$cmp"
      cmps+="$cmp"
    elif [[ "$stat" == "1" ]]; then
      printf "${RED}S!${RESET} "
      (( per_fail++ ))
    elif [[ "$stat" == "2" ]]; then
      printf "${RED}C!%s${RESET} " "$cmp"
      cmps+="$cmp"
      (( per_fail++ ))
    else
      printf "${YELLOW}??${RESET} "
      (( per_fail++ ))
    fi
  done

  if (( ${#cmps[@]} > 0 )); then
    local sum=0 min=${cmps[1]} max=${cmps[1]}
    for v in "${cmps[@]}"; do
      (( sum += v ))
      (( v < min )) && min="$v"
      (( v > max )) && max="$v"
    done
    local avg
    avg=$(print -l -- $sum $#{cmps} | awk 'NR==1{s=$1} NR==2{n=$1} END{printf("%.2f", s/n)}')
    printf "${GRAY}[min=%d avg=%s max=%d fails=%d]${RESET}\n" "$min" "$avg" "$max" "$per_fail"
  else
    printf "${GRAY}[no-cmp fails=%d]${RESET}\n" "$per_fail"
  fi
}

# 本体: n=1..21 各20回（Vector → Deque の順に 2 行表示）
for n in {1..21}; do
  run_block "$n" "Vector"
  run_block "$n" "Deque"
  print "＊＊＊＊＊＊"
done
