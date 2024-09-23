Fibonacci() {
    num=$1
    n1=0
    n2=1
    sum=0
    echo "$n1"
    echo "$n2"
    
    for (( i=0 ; $i<$num-2 ; i++ ))
    do 
        sum=$((n1+n2))
        echo "$sum"
        n1=$n2
        n2=$sum
    done
    
    
}
# echo -n "Enter Number : "
# read number
# Fibonacci $number

Pallindrom() {
    num=$1
    temp=$num
    rev=0
    
    while [ $temp -gt 0 ]
    do 
        digit=$((temp%10))
        rev=$((rev * 10 + digit))
        temp=$((temp/10))
    done
    
    if [ $rev -eq $num ]; then
        echo "pallindrom"
    else
        echo "Not pallindrom"
    fi
    
}

# echo -n "Enter Number : "
# read number
# Pallindrom $number


triangular() {
    num=$1
    sum=0
    i=0
    while [ $sum -lt $num ]
    do 
        sum=$((sum+i))
        i=$((i+1))
    done
    
    if [ $sum == $num ]; then
        echo "traingular number"
    else
        echo "NOt triangular Number"
    fi
}

echo -n "Enter Number : "
read number
triangular $number











