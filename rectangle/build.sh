rm -rf src
rm -rf buil
mkdir src
mkdir build
asn1c rect.asn1 -D src -no-gen-OER -no-gen-example
gcc -Isrc -o build/coder rectangle_coder.c src/*.c -DPDU=Rectangle -DASN_DISABLE_OER_SUPPORT
gcc -Isrc -o build/decoder rectangle_decoder.c src/*.c -DPDU=Rectangle -DASN_DISABLE_OER_SUPPORT

./build/coder ./build/rectangle_ber_out
./build/decoder ./build/rectangle_ber_out
