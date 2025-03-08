#!/bin/bash

set -e

echo "Select an option:"
echo "1) Run all commands"
echo "2) Run only the compile command"
echo "3) Run only the copy-to-keyboard command"
echo "4) Run only the copy-to-desktop command"
echo "5) Run only the copy-to-keyboard & copy-to-desktop command"
read -p "Enter your choice (1-4): " choice

case $choice in
  1)
    echo "Running all commands..."
    qmk compile -kb keebio/iris/rev8 -km stijnklomp -e CONVERT_TO_UF2=yes
    cp .build/keebio_iris_rev8_stijnklomp.uf2 compiledLayouts/
    cp .build/keebio_iris_rev8_stijnklomp.uf2 ~/Desktop/
    ;;
  2)
    echo "Running compile command..."
    qmk compile -kb keebio/iris/rev8 -km stijnklomp -e CONVERT_TO_UF2=yes
    ;;
  3)
    echo "Copying compiled file to keyboards/keebio/iris..."
    cp .build/keebio_iris_rev8_stijnklomp.uf2 keyboards/keebio/iris
    ;;
  4)
    echo "Copying compiled file to Desktop..."
    cp .build/keebio_iris_rev8_stijnklomp.uf2 ~/Desktop/
    ;;
  5)
    echo "Copying compiled file to keyboards/keebio/iris & Desktop..."
    cp .build/keebio_iris_rev8_stijnklomp.uf2 compiledLayouts/
    cp .build/keebio_iris_rev8_stijnklomp.uf2 ~/Desktop/
    ;;
  *)
    echo "Invalid choice. Please select a valid option (1-4)."
    ;;
esac

