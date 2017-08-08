# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compile_tests.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfontain <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/08 19:56:27 by tfontain          #+#    #+#              #
#    Updated: 2017/08/08 19:57:44 by tfontain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

for f in src/*.s
do
	echo "Compiling $f"
	../../asm/asm $f
done

if [ ! -d "bin" ]; then
	mkdir bin
fi
mv src/*.cor bin/
