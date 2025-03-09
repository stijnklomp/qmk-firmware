#!/bin/bash

set -e

echo "Select an option:"
echo "1) Run all commands"
echo "2) Run only the compile command"
echo "3) Run only the copy-to-keyboard command"
echo "4) Run only the copy-to-desktop command"
echo "5) Run only the copy-to-keyboard & copy-to-desktop command"
read -p "Enter your choice (1-4): " choice

function moveToCompiledFilesDirectory {
    if [ -f "compiledLayouts/keebio_iris_rev8_stijnklomp_old.uf2" ]; then
        rm "compiledLayouts/keebio_iris_rev8_stijnklomp_old.uf2"
    fi

    if [ -f "compiledLayouts/keebio_iris_rev8_stijnklomp_new.uf2" ]; then
        mv "compiledLayouts/keebio_iris_rev8_stijnklomp_new.uf2" "compiledLayouts/keebio_iris_rev8_stijnklomp_old.uf2"
    fi

    cp ".build/keebio_iris_rev8_stijnklomp.uf2" "compiledLayouts/keebio_iris_rev8_stijnklomp_new.uf2"
}


case $choice in
  1)
    echo "Copying compiled file to compiledLayouts/ & Desktop..."
    echo "Running all commands..."
    rm -rf .build/*
    qmk compile -kb keebio/iris/rev8 -km stijnklomp -e CONVERT_TO_UF2=yes

    moveToCompiledFilesDirectory
    cp ".build/keebio_iris_rev8_stijnklomp.uf2" ~/Desktop/
    ;;
  2)
    echo "Running compile command..."
    rm -rf .build/*
    qmk compile -kb keebio/iris/rev8 -km stijnklomp -e CONVERT_TO_UF2=yes
    ;;
  3)
    echo "Copying compiled file to keyboards/keebio/iris..."
    moveToCompiledFilesDirectory
    ;;
  4)
    echo "Copying compiled file to Desktop..."
    cp .build/keebio_iris_rev8_stijnklomp.uf2 ~/Desktop/
    ;;
  5)
    echo "Copying compiled file to compiledLayouts/ & Desktop..."
    moveToCompiledFilesDirectory
    cp .build/keebio_iris_rev8_stijnklomp.uf2 ~/Desktop/
    ;;
  *)
    echo "Invalid choice. Please select a valid option (1-4)."
    ;;
esac

