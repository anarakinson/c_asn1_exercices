rm -rf src_asn1
rm -rf build
mkdir src_asn1
mkdir build
asn1c s1ap.asn1 -D src_asn1 -pdu=UEContextReleaseRequest -no-gen-OER -fcompound-names -no-gen-example -fno-include-deps
gcc -g -Isrc_asn1 -Iinclude -o build/uecontextreleaserequest src/*.c src_asn1/*.c -lsctp -DPDU=UEContextReleaseRequest -DASN_DISABLE_OER_SUPPORT

echo ------------
echo --- TEST ---
echo ------------

./build/uecontextreleaserequest
