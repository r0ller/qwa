em++ -std=c++11 ../qwa_pure_backend/receiver.cpp -o libqwa_pure_backend.js -s EXPORTED_FUNCTIONS="['_execute']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall']" -I../qwa_pure_backend
