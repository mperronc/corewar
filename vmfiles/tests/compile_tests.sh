for f in src/*.s
do
	echo "Compiling $f"
	../../asm/asm $f
done

mv src/*.cor bin/
