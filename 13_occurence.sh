echo enter string
read s

echo enter substring
read t
count=0
l=${#s}
m=${#t}
for (( i=0;i<$l;i++ ))
do
                c=${s:$i:m}
                if [ $c = $t ]
                then

                        let count++

                fi
        c=""
done

echo $count