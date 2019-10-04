# cpg

Central pattern generator(CPG)のモデルとしてMatsuoka neural oscillatorは広く用いられている。
このリポジトリではMatsuoka neural oscillatorによる単振り子の角度制御シミュレーションをおこなう。

## Usage

- Build 

```sh
git clone https://github.com/dofuman/cpg.git
mkdir build && cd build
cmake ..
make
```

- Run

```sh
. build/src/matsuoka
plot.py out_pendulum_matsu.dat
```


