if [ ! -f Tests/catch.hpp ]; then
    cd Tests
    curl -o catch.hpp -L https://github.com/catchorg/Catch2/releases/download/v2.4.1/catch.hpp
    cd ..
fi

rm -rf Build
mkdir Build
cd Build
cmake ..
