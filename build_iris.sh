#!/bin/bash

set -e

echo "Select an option:"
echo "1) Compile to 'compiledLayouts' & 'Desktop'"
echo "2) Compile to 'compiledLayouts'"
echo "3) Copy 'compiledLayouts' to 'Desktop'"
read -p "Enter your choice (1-3): " choice

function compile {
    rm -rf .build/*
    if [ -f "compiledLayouts/keebio_iris_rev8_stijnklomp.uf2" ]; then
        rm "compiledLayouts/keebio_iris_rev8_stijnklomp.uf2"
    fi
    qmk compile -kb keebio/iris/rev8 -km stijnklomp -e CONVERT_TO_UF2=yes
}

function moveToCompiledLayoutsDirectory {
    mkdir "compiledLayouts"
    cp ".build/keebio_iris_rev8_stijnklomp.uf2" "compiledLayouts/keebio_iris_rev8_stijnklomp.uf2"
}

function moveToDesktop {
    cp "compiledLayouts/keebio_iris_rev8_stijnklomp.uf2" ~/Desktop/
}


case $choice in
  1)
    echo "Copying compiled file to compiledLayouts/ & Desktop/..."
    compile
    moveToCompiledLayoutsDirectory
    moveToDesktop
    ;;
  2)
    echo "Copying compiled file to compiledLayouts/..."
    compile
    moveToCompiledLayoutsDirectory
    ;;
  3)
    echo "Copying existing compiled file to Desktop/..."
    moveToDesktop
    ;;
  *)
    echo "Invalid choice. Please select a valid option (1-3)."
    ;;
esac

