setup

nix-shell -p arduino-cli 

arduino-cli config add board_manager.additional_urls https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
arduino-cli core update-index
arduino-cli core install Seeeduino:esp32

arduino-cli lib install "MSC"

arduino-cli compile --fqbn esp32:esp32:esp32s3 key_storage.ino 
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 key_storage.ino 
