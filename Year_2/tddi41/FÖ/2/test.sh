#!/bin/bash

name="Hugo"
echo "The name is $name"

if [[ $name == "Hugo" ]]; then
    echo "The name is Hugo"
else
    echo "The name is not Hugo, but $name"
fi

result=$( (cat ./test.sh | grep -i hugo) )

echo $result

function rune(){
    echo "This is func Rune with arg $1"
}

rune "Nisse"