
# 在项目根目录执行
rm -rf build
mkdir build && cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..  # 生成 compile_commands.json

# ln -s $(pwd)/compile_commands.json ../      # 软链接到项目根目录
cd  ..
echo "$(pwd)"
ln -s build/compile_commands.json .     # 软链接到项目根目录

# 在项目根目录执行
# run-clang-tidy -p build/ -checks='*' -j4  # 使用4个线程
# run-clang-tidy -p build/ > clang-tidy-report.txt
run-clang-tidy -p build/
