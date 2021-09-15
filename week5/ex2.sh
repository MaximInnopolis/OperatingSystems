for i in {1..500}
do
	last_number = $(tail -n 1 numbers.txt) #displays last 1 number of numbers.txt
	echo $((last_number + 1)) >> numbers.txt
done