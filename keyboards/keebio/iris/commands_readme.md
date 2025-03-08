# Prerequisites

1. [Prepare build environment](https://docs.qmk.fm/newbs_getting_started#set-up-your-environment)

```sh
# macOS
brew install qmk/qmk/qmk
```

2. [Run QMK setup](https://docs.qmk.fm/newbs_getting_started#set-up-qmk)

```sh
qmk setup
```

# Compile

Compile to UF2 format:

```sh
qmk compile -kb keebio/iris/rev8 -km stijnklomp -e CONVERT_TO_UF2=yes
cp .build/keebio_iris_rev8_stijnklomp.uf2 ~/Desktop/ # Optional - copy to desktop
```
