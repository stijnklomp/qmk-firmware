# Prerequisites

1. [Prepare build environment](https://docs.qmk.fm/newbs_getting_started#set-up-your-environment)

```sh
# macOS
brew install qmk/qmk/qmk

# Linux
python3 -m pip install --user qmk --break-system-packages
```

2. [Run QMK setup](https://docs.qmk.fm/newbs_getting_started#set-up-qmk)

```sh
qmk setup
```

3. Set Unicode input

```sh
qmk config user.unicode_enabled=true
```

# Compile script

Run the compile script: (This will present a few options on what to do with the compiled file)

```sh
sudo chmod +x build_iris.sh # Make the script executable
./build_iris.sh
```
