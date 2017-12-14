# cpg

Central pattern generator(CPG)のモデルとして広く用いられている
Matsuoka neural oscillatorを用いて各種シミュレーションをおこなう.

このリポジトリでは Matsuoka neural oscillatorによる単振り子の
角度制御シミュレーションが実装済みである.

## Usage

以下を実行

"""sh
git clone https://github.com/dofuman/cpg.git
mkdir build && cd build
cmake ..
make
"""

"matsuoka"というファイルが"build/src/"に生成されるので実行するとdat
ファイルが生成されるので"plot.py"で開くとシミュレーション結果が表示される.


