for f in src/*.s
do
	echo "Compiling $f"
	../asm $f
done

mv src/*.cor bin/
